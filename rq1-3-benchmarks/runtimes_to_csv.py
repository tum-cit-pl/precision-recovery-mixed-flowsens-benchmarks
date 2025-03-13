#!/usr/bin/python3
import sys
import re
import math
from functools import cmp_to_key
import argparse
import itertools

parser = argparse.ArgumentParser(description='Extract precision data from benchmark output')
parser.add_argument('file', type=str, help='Benchmark output file', nargs='+')
parser.add_argument('--mode', type=str, nargs='?',
                    help='timing, dead, omitted, memory')
parser.add_argument('--split', type=float, nargs='?',
                    help='Print every row that has an element exceeding this limit to stderr')
parser.add_argument('--splitProp', type=str, nargs='?',
                    help='[time],mem')

args = parser.parse_args()

if args.mode == None:
    mode = "timing"
else:
    mode = args.mode

splitMode = 'time'

split = float('inf')
if args.split:
    split = args.split
    if args.splitProp:
        splitMode = args.splitProp

suite = None

cases = []
class Case:
    suite = None
    name = None
    times = None
    dead = None
    omitted = None
    memory = None
case = Case()

analyses = set()

def pushcase():
    if case.name != None:
        if suite == None:
            print(f"No active suite!", file=sys.stderr)
            exit(1)
        for existingcase in cases:
            if existingcase.name == case.name and existingcase.suite == case.suite:
                existingcase.times.update(case.times)
                existingcase.dead.update(case.dead)
                existingcase.omitted.update(case.omitted)
                existingcase.memory.update(case.memory)
                return
        cases.append(case)

analysis_name = ""
for file in args.file:
    with open(file, 'r') as f:
        lines = f.readlines()
        for line in lines:
            x = re.search('^Analysing (.*) \(.*\)$', line)
            if x != None:
                pushcase()
                case = Case()
                case.times = dict()
                case.memory = dict()
                case.dead = dict()
                case.omitted = dict()
                case.suite = suite
                case.name = x.group(1)
                continue
            x = re.search(f' *([-a-zA-Z0-9_]+) *-- Done! ([0-9.]+) s', line)
            if x != None:
                analysis_name = x.group(1)
                analyses.add(analysis_name)
                case.times[analysis_name] = float(x.group(2))
                x = re.search(f'([0-9.]+) MB', line)
                if x != None:
                    case.memory[analysis_name] = float(x.group(1))
                continue
            x = re.search(f' *([-a-zA-Z0-9_]+) *-- Timeout!', line)
            if x != None:
                analysis_name = x.group(1)
                analyses.add(analysis_name)
                case.times[analysis_name] = 'Timeout'
                x = re.search(f'([0-9.]+) MB', line)
                if x != None:
                    case.memory[analysis_name] = float(x.group(1))
                continue
            x = re.search(f' *([-a-zA-Z0-9_]+) *-- Failed!', line)
            if x != None:
                analysis_name = x.group(1)
                analyses.add(analysis_name)
                case.times[analysis_name] = 'Failed'
                continue
            x = re.search(f'Botified contextualized functions \(still bot,botified,dead,total\): ([0-9]+)\/([0-9]+)\/([0-9]+)\/([0-9]+)', line)
            if x != None:
                case.dead[analysis_name] = (int(x.group(1)), int(x.group(2)), int(x.group(3)), int(x.group(4)))
                continue
            x = re.search(f'Omitted \\(bot,revived,total\\): ([0-9.]+)/([0-9.]+)/([0-9.]+); ([0-9.]+) to dead; ([0-9.]+) from dead', line)
            if x != None:
                case.omitted[analysis_name] = (int(x.group(1)), int(x.group(2)), int(x.group(3)), int(x.group(4)), int(x.group(5)))
                continue
            x = re.search('^[-a-zA-Z0-9_ ()]+$', line)
            if x != None:
                suite = x.group()
        pushcase()

analyses_ = []
for analysis in analyses:
    analyses_.append(analysis)

def remap_number(x):
    if x == '0': return 'z'
    if x == '1': return 'o'
    if x == '2': return 'tw'
    if x == '3': return 'th'
    if x == '4': return 'fo'
    if x == '5': return 'fi'
    if x == '6': return 'si'
    if x == '7': return 'se'
    if x == '8': return 'e'
    if x == '9': return 'n'
    return x

def to_command_identifier(x):
    result = ""
    for c in filter(lambda x: x.isalpha(), map(remap_number, x)):
        result += c
    return result

if mode == "count":
    print(f'\\newcommand\\casecount{{{len(cases)}}}')
    timeouts = {}
    failed = {}
    for analysis in analyses:
        timeouts[analysis] = 0
        failed[analysis] = 0
    discounted_cases = set()
    for case in cases:
        for analysis in analyses:
            time = case.times[analysis]
            if time == 'Timeout':
                timeouts[analysis] += 1
                discounted_cases.add(case)
            elif time == 'Failed':
                failed[analysis] += 1
                discounted_cases.add(case)
    print(f'\\newcommand\\incomplete{{{len(discounted_cases)}}}')
    for analysis in analyses:
        # cannot really separate failures and timeouts, because some of the failures may just be due to the hard timeout
        # enforced by the timeout command. Sometimes (very rarely), the serialization of precision data takes excessively long,
        # specifically more than 10 minutes.
        print(f"\\newcommand\\incomplete{to_command_identifier(analysis)}{{{timeouts[analysis] + failed[analysis]}}}")

if mode == "count-rec":
    timeouts = {}
    failed = {}
    for analysis in analyses:
        timeouts[analysis] = 0
        failed[analysis] = 0
    relevant_case_count = 0
    discounted_cases = set()
    for case in cases:
        if case.suite in ["recursive", "recursive-simple","recursive-with-pointer","verifythis","recursified_loop-crafted","recursified_loop-invariants","recursified_loop-simple","recursified_nla-digbench"]:
            relevant_case_count += 1
            for analysis in analyses:
                time = case.times[analysis]
                if time == 'Timeout':
                    timeouts[analysis] += 1
                    discounted_cases.add(case)
                elif time == 'Failed':
                    failed[analysis] += 1
                    discounted_cases.add(case)
    print(f'\\newcommand\\casecountrec{{{relevant_case_count}}}')
    print(f'\\newcommand\\incompleterec{{{len(discounted_cases)}}}')
    for analysis in analyses:
        # cannot really separate failures and timeouts, because some of the failures may just be due to the hard timeout
        # enforced by the timeout command. Sometimes (very rarely), the serialization of precision data takes excessively long,
        # specifically more than 10 minutes.
        print(f"\\newcommand\\incompleterec{to_command_identifier(analysis)}{{{timeouts[analysis] + failed[analysis]}}}")

if mode == "timing":
    outstring = ""
    errstring = ""
    for index, case in enumerate(cases):
        columns = list()
        toerr = False
        for analysis in analyses_:
            time = case.times[analysis]
            if time == None:
                columns.append('')
            else:
                if time == 'Timeout' or time == 'Failed'  or (time > split and splitMode == 'time'):
                    toerr = True
                columns.append(str(time))
            try:
                memory = case.memory[analysis]
                if(splitMode == 'mem' and memory > split):
                    toerr = True
            except:
                memory = None
                toerr = True
            if memory == None:
                columns.append('')
            else:
                columns.append(str(memory))
        string = f'{case.suite},{case.name},{index+1},' + ','.join(columns) + '\n'
        if toerr:
            errstring += string
        else:
            outstring += string
    column_headers = []
    for analysis in analyses_:
        column_headers = column_headers + [analysis, analysis + "-memory"]
    for (string, file) in [(outstring, sys.stdout), (errstring, sys.stderr)]:
        if string != "":
            print('suite,file,coordindex,' + ','.join(column_headers), file=file)
            print(string.strip(), file=file)

if mode == "memory":
    print('suite,file,coordindex,' + ','.join(analyses_))
    for index, case in enumerate(cases):
        memusages = list()
        for analysis in analyses_:
            memusage = case.memory[analysis]
            if memusage == None:
                memusages.append('')
            else:
                memusages.append(str(memusage))
        print(f'{case.suite},{case.name},{index+1},' + ','.join(memusages))

if mode == "dead":
    print('suite,file,coordindex,stillbot,botified,dead,total')
    for index, case in enumerate(cases):
        dead = list()
        analysis = "ours-bot"
        if not analysis in case.dead:
            continue
        adead = case.dead[analysis]
        astillbot,abotified,adead,atotal = adead
        dead.append(f"{astillbot},{abotified},{adead},{atotal}")
        print(f'{case.suite},{case.name},{index+1},' + ','.join(dead))

if mode == "omitted":
    print('suite,file,coordindex,' + ','.join(map(lambda a: f"{a}-bot,{a}-revived,{a}-total", analyses_)))
    for index, case in enumerate(cases):
        omitted = list()
        for analysis in analyses_:
            if not analysis in case.omitted:
                omitted.append('0,0,0')
            else:
                aomitted = case.omitted[analysis]
                abot,arevived,atotal,atodead,afromdead = aomitted
                omitted.append(f"{abot},{arevived},{atotal}")
        print(f'{case.suite},{case.name},{index+1},' + ','.join(omitted))
