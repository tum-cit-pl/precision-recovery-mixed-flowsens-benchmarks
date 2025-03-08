#!/usr/bin/ruby
require 'fileutils'
require 'optparse'

$do_apron_cmp = false
$idead = false
$iwiden = false
$jobs = 1
$clean = false
$ulimit = 3145728 # ulimit is scaled by 1 KiB, so this corresponds to 3 GiB
$gobroot = "../analyzer/"
$globfilter = ""
$print_diff = ""
$pin = false
OptionParser.new do |opt|
  opt.on('--apron') { || $do_apron_cmp = true }
  opt.on('--idead') { || $idead = true }
  opt.on('--iwiden') { || $iwiden = true }
  opt.on('-j=JOBS', 'Number of jobs') { |x| $jobs = x.to_i}
  opt.on('--clean', 'Remove result files after comparison') { || $clean = true }
  opt.on('-m=MEMORY', 'Memory limit for each benchmark case in KiB') { |x| $ulimit = x.to_i }
  opt.on('--gobroot=PATH', 'Path to the goblint repository') {|x| $gobroot = x }
  opt.on('--priv-only', 'Filter globals for privatization') {|| $globfilter = "--set dbg.compare_runs.varfilter[+] privatization" }
  opt.on('--pin', 'Pin each thread to a cpu') {|| $pin = true }
  opt.on('--emit-diff', 'Emit diff in compare files') {|| $print_diff = "--enable dbg.compare_runs.diff"}
end.parse!

#Dir.chdir(File.dirname(__FILE__))
$goblint = File.expand_path(File.join($gobroot, "goblint"))
$goblint_conf = File.expand_path(File.join($gobroot, "conf/traces.json"))
$apron_cmp = File.expand_path(File.join($gobroot, "apronPrecCompare"))
fail "Goblint not found at #{$goblint}" unless File.exist?($goblint)
$common = ""
$vrsn = `#{$goblint} --version`
results = "bench_result"
Dir.mkdir(results) unless Dir.exist?(results)
$testresults = File.expand_path("bench_result") + "/"
bench = "./"
linux = bench + "linux/"

if $do_apron_cmp then puts "Comparing Octagon Precision" end

cmds = {"code2html" => lambda {|f,o| "code2html -l c -n #{f} 2> /dev/null 1> #{o}"},
        "source-highlight" => lambda {|f,o| "source-highlight -n -i #{f} -o #{o}"},
        "pygmentize" => lambda {|f,o| "pygmentize -O full,linenos=1 -o #{o} #{f}"}
       }
highlighter = nil
cmds.each do |name, cmd|
  # if `which #{cmd} 2> /dev/null`.empty? then
  if ENV['PATH'].split(':').map {|f| File.executable? "#{f}/#{name}"}.include?(true) then
    highlighter = cmd
    break
  end
end
if highlighter.nil? then
  puts "Warning: No syntax highlighter installed (code2html, source-highlight, pygmentize)."
  highlighter = lambda {|f,o| "cp #{f} #{o}"}
end

class Project
  attr_reader :id, :name, :path
  attr_accessor :url, :params
  def initialize(id, name, size, url, path, params)
    @id       = id
    @name     = name
    @size     = size
    @url      = url
    @path     = path
    @params   = params
  end
  def to_html
    "<td>#{@id}</td><td><a href=\"#{@url}\">#{@name}</a></td>\n" + "<td>#{@size}</td>\n"
  end
  def to_s
    "#{@name}"
  end
end

$projects = []

class Group
  attr_reader :name
  attr_accessor :projects
  attr_accessor :mutex
  attr_accessor :completed_count
  attr_accessor :output
  def initialize(name)
    @name     = name
    @projects = []
    @mutex = Thread::Mutex.new
    @completed_count = 0
    @output = name + "\n"
  end
  def to_s
    "#{@name}"
  end
end
$groups = []

class Task
  attr_reader :group
  attr_reader :project
  def initialize(group, project)
    @group   = group
    @project = project
  end
  def to_s
    "#{@group}-#{@project}"
  end
end
$groups = []

$header = <<END
<head>
  <title>Benchmarks on #{`uname -n`.chomp}</title>
  <style type="text/css">
    A:link {text-decoration: none}
    A:visited {text-decoration: none}
    A:active {text-decoration: none}
    A:hover {text-decoration: underline}
</style>
</head>
END

#Command line parameters

$timeout = 900
$timeout = ARGV[0].to_i unless ARGV[0].nil?
only = ARGV[1] unless ARGV[1].nil?
if only == "group" then
  only = nil
  thegroup = ARGV[2]
end
# Sometimes, the Goblint processes run for over an hour somehow. Perhaps extremely slowly saving the run? Or perhaps they are stuck. Either way, a hard timeout eases the pain.
$hard_timeout = $timeout + 600

#processing the input file

skipgrp = []
file = "bench.txt"
$linuxroot = "https://elixir.bootlin.com/linux/v4.0/source/"
File.symlink("index/traces.txt",file) unless FileTest.exist? file

FileUtils.cp(file,File.join($testresults, "bench.txt"))

$analyses = []
current_group = nil
$project_count = 0
$project_completed_count = 0
File.open(file, "r") do |f|
  id = 0
  while line = f.gets
    next if line =~ /^\s*$/
    if line =~ /Group: (.*)/
      gname = $1.chomp
      current_group = Group.new(gname)
      $groups << current_group
      skipgrp << gname if line =~ /SKIP/
    elsif line =~ /common: ?(.*)/
      $common << $1
    elsif line =~ /(.*): ?(.*)/
      $analyses << [$1,$2]
    else
      name = line.chomp
      url = f.gets.chomp
      path = f.gets.chomp
      params = f.gets.chomp
      params = "" if params == "-"
      if url == "linux!" then
        params = "--enable kernel " + params
        url = $linuxroot + path
        path = File.expand_path(path, linux)
      else
        path = File.expand_path(path, bench)
      end
      size = `wc -l #{path}`.split[0] + " lines"
      id += 1
      p = Project.new(id,name,size,url,path,params)
      current_group.projects << p
      $project_count = $project_count + 1
    end
  end
end

STDERR.puts ("Found %d tasks" % [$project_count])

#Process linux results!

$fileheader = <<END
<html>
  <head>
    <title>Benchmarks on #{`uname -n`.chomp}</title>
    <style type="text/css">
      body { white-space: pre; font-family: monospace }
      a { color: inherit }
    </style>
  </head>
  <body>
END


def proc_linux_res(resultfile, url, filename)
  File.open(resultfile, "r") do |f|
    File.open(resultfile + ".html", "w") do |o|
      o.puts $fileheader
      while line = f.gets
        line.sub!(/\@(#{filename}:(\d+))/, "@<a href=\" #{url}#L\\2\">\\1</a>")
        if line =~ /race with/
          o.puts '<font color="red">' + line.chop + "</font>"
        else
          o.puts line
        end
      end
      o.puts "</body>"
      o.puts "</html>"
    end
  end
end

def analyze_cmp_line(grep_result)
  better = 0
  worse = 0
  incomparable = 0
  grep_result.scan(/equal: ([0-9]+), more precise: ([0-9]+), less precise: ([0-9]+), incomparable: ([0-9]+), total: ([0-9]+)/) { if $1 != $5 then
    do_print = true
    betterI = Float($2)
    worseI = Float($3)
    incomparableI = Float($4)
    totalI = Float($5)
    #totalII = Integer($5)
    #puts ("total: %d" % [totalII])
    better = betterI / totalI
    worse = worseI / totalI
    incomparable = incomparableI / totalI
  end }
  return better,worse,incomparable
end

#analysing the files
gname = ""
$maxlen = $analyses.map { |x| x[0].length }.max + 1

#$groups = $groups.filter { |g| !(skipgrp.member? g.name) && (thegroup.nil? or g.name == thegroup) }

#!(only.nil? or p.name == only)
def threadjob(task,taskid,cpu)
  if cpu != -1 then
    taskset = "taskset --cpu-list #{cpu}"
  else
    taskset = ""
  end
  group = task.group
  p = task.project
  threadoutput = ""
  #if $jobs != 1 then
    output = ->(str) { threadoutput = threadoutput + str }
  #else
  #  output = ->(str) { print(str) }
  #end
  id = 0
  intermediatedir = ".goblint-#{taskid}"
  
  id = id + 1
  filepath = p.path
  dirname = File.dirname(filepath)
  filename = File.basename(filepath)
  #Dir.chdir(dirname)
  outfiles = $testresults + File.basename(filename,".c") + ".*"

  output.call("Analysing #{filename} ()\n")

  `rm #{outfiles} 2> /dev/null`
  if p.url == "generate!" then
    system(highlighter.call(p.path, $testresults + p.name + ".html"))
    p.url = p.name + ".html"
  end
  precfiles = []
  $analyses.each do |a|
    aname = a[0]
    aparam = a[1]
    output.call("  #{format("%*s", -$maxlen, aname)}")
    outfile = $testresults + taskid.to_s + "." + File.basename(filename,".c") + ".#{aname}.txt"
    precfile = $testresults + taskid.to_s + "." + File.basename(filename,".c") + ".#{aname}.prec"
    precfilecontent = $testresults + taskid.to_s + "." + File.basename(filename,".c") + ".#{aname}.prec/*"
    precfiles << precfile
    `rm #{precfilecontent} 2> /dev/null`
    `rmdir #{precfile} 2> /dev/null`

    starttime = Time.now

    if $do_apron_cmp then
      dump_flag = "--set exp.relation.prec-dump"
    else
      dump_flag = "--save_run"
    end
    #Add --set cilout /dev/null to ignore CIL output.
    cmd = "cd #{dirname} && ulimit -m #{$ulimit} && #{taskset} timeout #{$hard_timeout} #{$goblint} --goblint-dir #{intermediatedir} --conf #{$goblint_conf} --set dbg.timeout #{$timeout} #{aparam} #{$common} #{filename} #{p.params} --enable allglobs --enable dbg.timing.enabled --enable warn.debug -v #{dump_flag} #{precfile} 1>#{outfile} 2>&1"

    system(cmd)
    status = $?.exitstatus
    endtime = Time.now
    File.open(outfile, "a") do |f|
      f.puts "\n=== APPENDED BY BENCHMARKING SCRIPT ==="
      f.puts "Analysis began: #{starttime}"
      f.puts "Analysis ended: #{endtime}"
      f.puts "Duration: #{format("%.02f", endtime-starttime)} s"
      f.puts "Goblint params: #{cmd}"
      f.puts $vrsn
    end

    if status != 0 then
      if status == 124 then
        output.call("-- Timeout!\n")
        `echo "TIMEOUT                    #{$timeout} s" >> #{outfile}`
      else
        output.call("-- Failed!\n")
        `echo "EXITCODE                   #{status}" >> #{outfile}`
      end
    else
      output.call("-- Done! #{format("%.06f", endtime-starttime)} s\n")
    end

    File.open(outfile, "r") do |g|
      lines = g.readlines
      # safely = lines.grep(/[^n]safe:[ ]*([0-9]*)/) { |x| $1.to_i } .first
      # vulner = lines.grep(/vulnerable:[ ]*([0-9]*)/) { |x| $1.to_i } .first
      # unsafe = lines.grep(/unsafe:[ ]*([0-9]*)/) { |x| $1.to_i } .first
      if $iwiden then
        widened = lines.grep(/Globals: ([0-9]+) widened of ([0-9]+) total/) { |x| [$1.to_i,$2.to_i] }
        if widened != [] then
          widened = widened.first
          output.call("\033[31;1;4mGlobals (widened,total): #{widened[0]}/#{widened[1]}\033[0m\n")
        end
      end
      if $idead then
        bottomized = lines.grep(/Botified contextualized functions: ([0-9]+) botified of ([0-9]+) dead of ([0-9]+) total/) { |x| [$1.to_i,$2.to_i,$3.to_i] }
        if bottomized != [] then
          bottomized = bottomized.first
          output.call("\033[31;1;4mBotified contextualized functions (botified,dead,total): #{bottomized[0]}/#{bottomized[1]}/#{bottomized[2]}\033[0m\n")
        end
        omitted = lines.grep(/Omitted contributions: ([0-9]+) still bot of ([0-9]+) omitted of ([0-9]+); ([0-9]+) to dead; ([0-9]+) from dead/) { |x| [$1.to_i,$2.to_i,$3.to_i,$4.to_i,$5.to_i] }
        if omitted != [] then
          #om_sb_count,om_count,cs_count = omitted.first
          #puts "\033[31;1;4mOmitted (bot,revived,total): #{om_sb_count}/#{om_count}/#{cs_count}\033[0m"
          omitted = omitted.first
          output.call("\033[31;1;4mOmitted (bot,revived,total): #{omitted[0]}/#{omitted[1]}/#{omitted[2]}; #{omitted[3]} to dead; #{omitted[4]} from dead\033[0m\n")
        end
      end
    end
    proc_linux_res(outfile, p.url, filename)
  end

  output.call("Comparing...\n")
  comparefile = $testresults + taskid.to_s + "." + File.basename(filename,".c") + ".compare.txt"
  system("rm #{comparefile} 2> /dev/null")
  $analyses.each_with_index {|a,i|
    aname1 = a[0]
    aparam = a[1]
    run1 = precfiles[i]
    precfiles.each_with_index do |run2,j|
      aname2 = $analyses[j][0]
      if i < j then
        subcomparefile = $testresults + taskid.to_s + "." + File.basename(filename,".c") + "." + aname1 + ".vs." + aname2 + ".compare.txt"

        if $do_apron_cmp then
          # Note that run2 is the first argument, apronPrecCompare outputs in the
          # form "run2 more precise than/.../equal to than run1"
          # TODO: confirm this properly
          `#{apron_cmp} #{run2} #{run1} 2>&1 1> #{subcomparefile}`

          glob_compare_result = `grep \"Apron Octagon\" #{subcomparefile} | tee -a #{comparefile}`
          better,worse,incomparable = analyze_cmp_line(glob_compare_result)

          if better != 0.0 || worse != 0.0 || incomparable != 0.0 then
            output.call("\033[31;1;4m%s vs. %s; more precise, less precise, incomparable: apron (%.4f,%.4f,%.4f)\033[0m\n" % [aname1, aname2, better, worse, incomparable])
          end
        else
          system("cd #{dirname} && #{taskset} #{$goblint} --goblint-dir #{intermediatedir} --conf #{$goblint_conf} #{aparam} #{$common} #{filename} #{p.params} --set dbg.level debug --enable dbg.compare_runs.eqsys --enable dbg.compare_runs.global #{$print_diff} #{$globfilter} --compare_runs #{run1} #{run2} > \"#{subcomparefile}\" 2>&1")
          status = $?.exitstatus
          if status != 0 then
            # This can happen, e.g. when the run itself failed. Or when the comparison runs out of memory
            STDERR.puts ("[WARNING] Comparison failed!")
            output.call("\033[31;1;4m%s vs. %s; COMPARISON FAILED!\033[0m\n" % [aname1, aname2])
          else
            glob_compare_result = `grep \"Globals comparison summary:\" \"#{subcomparefile}\" | tee -a \"#{comparefile}\"`
            gbetter,gworse,gincomparable = analyze_cmp_line(glob_compare_result)
            eq_compare_result = `grep \"EqConstrSys comparison summary:\" \"#{subcomparefile}\" | tee -a \"#{comparefile}\"`
            abetter,aworse,aincomparable = analyze_cmp_line(eq_compare_result)
            if gbetter != 0.0 || gworse != 0.0 || gincomparable != 0.0 || abetter != 0.0 || aworse != 0.0 || aincomparable != 0.0 then
              output.call("\033[31;1;4m%s vs. %s; more precise, less precise, incomparable: globals (%.4f,%.4f,%.4f); total (%.4f,%.4f,%.4f)\033[0m\n" % [aname1, aname2, gbetter, gworse, gincomparable, abetter, aworse, aincomparable])
            end
          end
        end
      end
    end
    if $clean then
      precfile = $testresults + File.basename(filename,".c") + ".#{aname1}.prec"
      precfilecontent = $testresults + File.basename(filename,".c") + ".#{aname1}.prec/*"
      `rm #{precfilecontent} 2> /dev/null`
      `rmdir #{precfile} 2> /dev/null`
      `rm #{comparefile} 2> /dev/null`
    end
  }
  if $clean then
    `rm #{outfiles} 2> /dev/null`
  end
  return threadoutput
end

mutex = Thread::Mutex.new
cv = Thread::ConditionVariable.new

threadcount = 0
finishedthreads = []
taskid = 0
$tasks = []
$groups.each do |g|
  g.projects.each do |p|
    $tasks << Task.new(g, p)
  end
end

cpus = []
if $pin then
  cpus = (0..($jobs-1)).to_a
end

while threadcount != 0 || $tasks != [] do
  while $tasks != [] && threadcount < $jobs do
    task = $tasks.pop
    threadcount = threadcount + 1
    if $pin then
      cpu = cpus.pop
    else
      cpu = -1
    end
    Thread.new(task,taskid,cpu) { |task,taskid,cpu|
      begin
        output = threadjob(task,taskid,cpu)
        group = task.group
        mutex.synchronize {
          finishedthreads << [Thread.current, cpu]
          cv.signal
          $project_completed_count = $project_completed_count + 1
          STDERR.puts ("[INFO] Completed tasks: %d/%d" % [$project_completed_count, $project_count])
          group.mutex.synchronize {
            group.completed_count = group.completed_count + 1
            group.output = group.output + output
            if group.completed_count >= group.projects.length() then
              puts group.output
              STDERR.puts ("[INFO] Group %s completed!" % [group.name])
              STDERR.flush
            end
          }
        }
      rescue => x
        mutex.synchronize {
          STDERR.puts ("[ERROR] Group %s failed!" % [g.name])
          STDERR.puts x.message
          STDERR.flush
        }
      end
    }
    taskid = taskid + 1
  end
  mutex.synchronize {
    while finishedthreads != [] do
      (t,cpu) = finishedthreads.pop
      t.join
      threadcount = threadcount - 1
      if $pin then
        cpus << cpu
      end
    end
    if threadcount >= $jobs
      cv.wait(mutex)
    end
  }
end
