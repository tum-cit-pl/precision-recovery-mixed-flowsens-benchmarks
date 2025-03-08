#!/usr/bin/ruby
require 'fileutils'
require 'optparse'
#Dir.chdir(File.dirname(__FILE__))
goblint = File.expand_path("../analyzer/goblint")
goblint_conf = File.expand_path("../analyzer/conf/traces.json")
fail "Please run script from goblint dir!" unless File.exist?(goblint)
$common = ""
$vrsn = `#{goblint} --version`
results = "bench_result"
Dir.mkdir(results) unless Dir.exist?(results)
$testresults = File.expand_path("bench_result") + "/"
bench = "./"
linux = bench + "linux/"

$iterations = 15
OptionParser.new do |opt|
  opt.on('--iterations N') { |o| $iterations = o.to_i }
  opt.on('-i N') { |o| $iterations = o.to_i }
end.parse!

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
  attr_reader :id, :name, :group, :path
  attr_accessor :url, :params
  def initialize(id, name, size, url, group, path, params)
    @id       = id
    @name     = name
    @size     = size
    @url      = url
    @group    = group
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
$theresultfile = File.join($testresults, "index.html")

#Command line parameters

timeout = 900
timeout = ARGV[0].to_i unless ARGV[0].nil?
only = ARGV[1] unless ARGV[1].nil?
if only == "group" then
  only = nil
  thegroup = ARGV[2]
end

#processing the input file

skipgrp = []
file = "bench.txt"
$linuxroot = "https://elixir.bootlin.com/linux/v4.0/source/"
File.symlink("index/traces.txt",file) unless FileTest.exist? file

FileUtils.cp(file,File.join($testresults, "bench.txt"))

$analyses = []
File.open(file, "r") do |f|
  id = 0
  while line = f.gets
    next if line =~ /^\s*$/
    if line =~ /Group: (.*)/
      gname = $1.chomp
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
      p = Project.new(id,name,size,url,gname,path,params)
      $projects << p
    end
  end
end

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

#analysing the files
gname = ""
maxlen = $analyses.map { |x| x[0].length }.max + 1
$projects.each do |p|
  next if skipgrp.member? p.group
  next unless thegroup.nil? or p.group == thegroup
  next unless only.nil? or p.name == only
  if p.group != gname then
    gname = p.group
    puts gname
  end
  filepath = p.path
  dirname = File.dirname(filepath)
  filename = File.basename(filepath)
  Dir.chdir(dirname)
  if p.url == "generate!" then
    system(highlighter.call(p.path, $testresults + p.name + ".html"))
    p.url = p.name + ".html"
  end
  puts "Analysing #{filename} (#{p.id}/#{$projects.length})"
  timings = Hash.new(0)
  memusages = Hash.new(0)
  $analyses.each do |a|
    timings[a] = Array.new
    memusages[a] = Array.new
  end
  shuffledanalyses = $analyses.clone
  for i in 1..$iterations do
    shuffledanalyses.shuffle
    shuffledanalyses.each do |a|
      aname = a[0]
      aparam = a[1]
      starttime = Time.now
      outfile = $testresults + File.basename(p.path,".c") + ".#{aname}.txt"
      #Add --sets cilout /dev/null to ignore CIL output.
      cmd = "#{goblint} --conf #{goblint_conf} --set dbg.timeout #{timeout} #{aparam} #{$common} #{filename} #{p.params} --enable allglobs --enable dbg.timing.enabled --enable warn.debug -v 1> #{outfile} 2>&1"
      system(cmd)
      status = $?.exitstatus
      endtime   = Time.now
      if status == 0 then
        timings[a] << endtime-starttime
      end

      if File.exist?(outfile) then
        File.open(outfile, "r") do |g|
          lines = g.readlines
          memusage = lines.grep(/Memory statistics:.*max=([0-9.]+)MB/) { |x| $1.to_f }.last
          if memusage != nil then
            memusages[a] << memusage
          end
        end
      end
    end
  end
  $analyses.each do |a|
    aname = a[0]
    print "  #{format("%*s", -maxlen, aname)}"
    STDOUT.flush
    if timings[a] == [] then
      puts "-- Failed!"
    else
      n = timings[a].size.to_f
      tmean = timings[a].reduce(:+) / n
      sum_sqr = timings[a].map {|x| x * x}.reduce(&:+)
      tstd_dev = Math.sqrt((sum_sqr - n * tmean * tmean)/(n-1))
      print "-- Done! #{format("%.06f", tmean)} s (#{format("%.06f", tstd_dev)})"
      if memusages[a] != [] then
        n = memusages[a].size.to_f
        mmean = memusages[a].reduce(:+) / n
        puts " #{format("%.06f", mmean)} MB"
      else
        puts ""
      end
    end
  end
end
