# Example

We added an example program `example.c` to the top folder of `analyzer` to highlight precision differences between configurations.
The function `__goblint_check(exp)` used inside this program tells Goblint to check whether it can prove that the expression evaluates to true.

The base update rule

```
goblint@goblint-VirtualBox:~/precision-recovery-mixed-flowsens-benchmarks/analyzer$ ./goblint example.c  --enable ana.base.priv.protection.changes-only --enable ana.int.interval
```

yields

```
[Warning][Assert] Assertion "a <= 11" is unknown. (example.c:18:3-18:27)
[Warning][Assert] Assertion "! b" is unknown. (example.c:30:3-30:22)
[Info][Deadcode] Logical lines of code (LLoC) summary:
  live: 18
  dead: 0
  total lines: 18
[Info][Race] Memory locations race summary:
  safe: 2
  vulnerable: 0
  unsafe: 0
  total memory locations: 2
```

Thus, none of the assertions can be shown. When using rule `ours`

```
goblint@goblint-VirtualBox:~/precision-recovery-mixed-flowsens-benchmarks/analyzer$ ./goblint example.c  --enable ana.base.priv.protection.changes-only --enable ana.int.interval --enable solvers.td3.narrow-sides.enabled
```

yields

```
[Success][Assert] Assertion "a <= 11" will succeed (example.c:18:3-18:27)
[Warning][Assert] Assertion "! b" is unknown. (example.c:30:3-30:22)
[Warning][Deadcode] Function 'g' is uncalled: 2 LLoC (example.c:8:1-10:1)
[Warning][Deadcode] Function 'f' has dead code:
  on line 20 (example.c:20-20)
[Warning][Deadcode] Logical lines of code (LLoC) summary:
  live: 14
  dead: 3 (2 in uncalled functions)
  total lines: 17
[Warning][Deadcode][CWE-570] condition 'a > 20' is always false (example.c:19:7-19:13)
[Info][Race] Memory locations race summary:
  safe: 2
  vulnerable: 0
  unsafe: 0
  total memory locations: 2
```

Thus, one of the assertions can be shown, and `g` is correctly determined to be unreachable.
Additionally enabling abstract garbage collection

```
goblint@goblint-VirtualBox:~/precision-recovery-mixed-flowsens-benchmarks/analyzer$ ./goblint example.c  --enable ana.base.priv.protection.changes-only --enable ana.int.interval --enable solvers.td3.narrow-sides.enabled --enable solvers.td3.narrow-sides.eliminate-dead
```

yields

```
[Success][Assert] Assertion "a <= 11" will succeed (example.c:18:3-18:27)
[Success][Assert] Assertion "! b" will succeed (example.c:30:3-30:22)
[Warning][Deadcode] Function 'g' is uncalled: 2 LLoC (example.c:8:1-10:1)
[Warning][Deadcode] Function 'f' has dead code:
  on line 20 (example.c:20-20)
[Warning][Deadcode] Logical lines of code (LLoC) summary:
  live: 14
  dead: 3 (2 in uncalled functions)
  total lines: 17
[Warning][Deadcode][CWE-570] condition 'a > 20' is always false (example.c:19:7-19:13)
[Info][Race] Memory locations race summary:
  safe: 2
  vulnerable: 0
  unsafe: 0
  total memory locations: 2
```

and thus all assertions can be proven.

When adding `--html` to any of these invocations, the system also produces human-readable HTML files. These can be inspected by:
- Running `goblint-result-server` in the analyzer folder
- Navigating to `http://localhost:8000/result/index.xml` in Firefox
- Clicking on the name of the file yields a view where the warnings are displayed inside the code and the local state can be inspected by clicking on a line. The values of globals can be inspected by clicking `globals` at the top right.
- Clicking on a function takes you to a CFG of the function where one can click on nodes to see the respective states.
