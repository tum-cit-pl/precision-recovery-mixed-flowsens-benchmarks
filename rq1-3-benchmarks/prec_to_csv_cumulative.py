#!/usr/bin/python3
import sys
import re
import math
from functools import cmp_to_key
import argparse

parser = argparse.ArgumentParser(description='Extract precision data from benchmark output')
parser.add_argument('file', type=str, help='Benchmark output file')
parser.add_argument('analysis1', type=str, help='First analysis to be compared')
parser.add_argument('analysis2', type=str, nargs='?', help='Second analysis to be compared')
parser.add_argument('--mode', type=str,
                    help='one of all, cumulative-diff')
parser.add_argument('--compare', type=str,
                    help='one of eq, glob, apron')
parser.add_argument('--filter-unambiguous', action='store_true',
                    help='Do not include cases that are not strictly better/worse')
parser.add_argument('--filter-ambiguous', action='store_true',
                    help='Include only cases that are not strictly better/worse')
parser.add_argument('--filter-incomparable', action='store_true',
                    help='Include only cases that have incomparable unknowns')
parser.add_argument('--zero-ambiguous', action='store_true',
                    help='Zero out cases that are not strictly better/worse; applies only in cumulative mode')
parser.add_argument('--allow-invalid', action='store_true',
                    help='Include timeout and failed cases')
args = parser.parse_args()

mode = args.mode
if mode == None:
    mode = "cumulative-diff"
compare = None
if args.compare == None or args.compare == "eq":
    compare = "total"
elif args.compare == "glob":
    compare = "globals"
elif args.compare == "apron":
    compare = "apron"
else:
    print(f"Invalid compare target '{args.compare}'", file=sys.stderr)
    exit(1)

comparison_regex = f'{compare} \\(([0-9.]+),([0-9.]+),([0-9.]+)\\)'

suite = None

class Comparison:
    better = 0.0
    worse = 0.0
    incomparable = 0.0

analyses = set()
cases = []
class Case:
    suite = None
    name = None
    analyses = {}
case = Case()

def pushcase():
    if case.name != None and (args.allow_invalid or case.valid):
        if suite == None:
            print(f"No active suite!", file=sys.stderr)
            exit(1)
        cases.append(case)

def do_comparison(line, invert):
    x = re.search(comparison_regex, line)
    comp = Comparison()
    if invert:
        comp.better = float(x.group(2))
        comp.worse = float(x.group(1))
    else:
        comp.better = float(x.group(1))
        comp.worse = float(x.group(2))
    comp.incomparable = float(x.group(3))
    return comp

with open(args.file, 'r') as f:
    lines = f.readlines()
    for line in lines:
        x = re.search(r'^Analysing (.*) \(.*\)$', line)
        if x != None:
            pushcase()
            case = Case()
            case.suite = suite
            case.name = x.group(1)
            case.analyses = {}
            case.valid = True
        x = re.search('-- (Timeout!)|(Failed!)$', line)
        if x != None:
            case.valid = False
        x = re.search('COMPARISON FAILED!', line)
        if x != None:
            case.valid = False
        else:
            x = re.search(r'(?:\[31;1;4m)?([^;]+) vs. ([^;]+);', line)
            if x != None:
                ac1 = x.group(1)
                ac2 = x.group(2)
                if args.analysis1 in [ac1, ac2] and (not args.analysis2 or args.analysis2 in [ac1, ac2]):
                    other = [ac1, ac2]
                    other.remove(args.analysis1)
                    assert(len(other) == 1)
                    other = other[0]
                    analyses.add(other)
                    comp = do_comparison(line, ac1 == other)
                    if other in case.analyses:
                        print(f"Multiple changes found for analysis {other} in {case.name}", file=sys.stderr)
                        exit(1)
                    case.analyses[other] = comp

        x = re.search(r'^[-a-zA-Z0-9_ ()]+$', line)
        if x != None:
            suite = x.group()
pushcase()

def ambiguous(x):
    for analysis in x.analyses:
        comp = x.analyses[analysis]
        if (comp.better != 0.0 and comp.worse != 0.0) or comp.incomparable != 0.0:
            return True
    return False

def incomparable(x):
    for analysis in x.analyses:
        comp = x.analyses[analysis]
        if comp.incomparable != 0.0:
            return True
    return False

if args.filter_unambiguous:
    cases = filter(lambda x: not ambiguous(x), cases)
if args.filter_ambiguous:
    cases = filter(lambda x: ambiguous(x), cases)
if args.filter_incomparable:
    cases = filter(lambda x: incomparable(x), cases)
analyses = list(analyses)

def cmp(x1,x2):
    if x1.better != x2.better:
        return x2.better - x1.better
    return x1.worse - x2.worse

if mode == "all":
    print("suite,file",end="")
    if len(analyses) == 1:
        print(",better,worse,incomparable")
    else:
        for analysis in analyses:
            print(f",better-{analysis},worse-{analysis},incomparable-{analysis}",end="")
        print("")
    for case in cases:
        suite = case.suite
        file = case.name
        print(f"{suite},{file}",end="")
        for analysis in analyses:
            if analysis in case.analyses:
                comp = case.analyses[analysis]
                better = float(comp.better)
                worse = float(comp.worse)
                incomparable = float(comp.incomparable)
            else:
                better = 0
                worse = 0
                incomparable = 0
            print(f",{better},{worse},{incomparable}",end="")
        print("")

class FlatCase:
    suite = None
    name = None
    better = 0.0
    worse = 0.0
    incomparable = 0.0

def flatten_case(c):
    flat = FlatCase()
    flat.suite = c.suite
    flat.name = c.name
    if args.analysis2 in c.analyses:
        comp = c.analyses[args.analysis2]
        if args.zero_ambiguous and ambiguous(c):
            flat.better = 0.0
            flat.worse = 0.0
            flat.incomparable = 0.0
        else:
            flat.better = comp.better
            flat.worse = comp.worse
            flat.incomparable = comp.incomparable
    return flat

if mode == "cumulative-diff":
    if not args.analysis2:
        print("Mode cumulative-diff is only allowed when a second comparison analysis is provided", file=sys.stderr)
        exit(1)
    print("count,better")
    cases = map(flatten_case, cases)
    cases = sorted(cases, key=lambda x: x.worse-x.better)
    cbetter = math.inf
    count = 0
    lastcount = -1
    for case in cases:
        better = case.better
        worse = case.worse
        count += 1
        better = better - worse
        if better != cbetter:
            cbetter = better
            print(f"{count},{better}")
            lastcount = count
    if count != lastcount:
        print(f"{count},{cbetter}")


if mode == "cumulative-diff-rec":
    if not args.analysis2:
        print("Mode cumulative-diff-rec is only allowed when a second comparison analysis is provided", file=sys.stderr)
        exit(1)
    print("count,better")
    cases = map(flatten_case, cases)
    cases = sorted(cases, key=lambda x: x.worse-x.better)
    cbetter = math.inf
    count = 0
    lastcount = -1
    for case in cases:
        better = case.better
        worse = case.worse
        if case.suite in ["recursive", "recursive-simple","recursive-with-pointer","verifythis","recursified_loop-crafted","recursified_loop-invariants","recursified_loop-simple","recursified_nla-digbench"]:
            count += 1
            better = better - worse
            if better != cbetter:
                cbetter = better
                print(f"{count},{better}")
                lastcount = count
    if count != lastcount:
        print(f"{count},{cbetter}")
