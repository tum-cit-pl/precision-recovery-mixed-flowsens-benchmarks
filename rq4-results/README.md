# Data for Experiments for RQ4

In this folder, we provide the resulting tables from runs on SV-COMP controlled under Benchexec.

### A list of claims from the paper supported by the artifact, and how/why.

> Overall, the analyses have almost identical runtimes on the tasks when they terminate. An exception is the configuration apinis, for which quite a few outliers with high runtime overheads are observed.

- Open `table-generator.table.html` and navigate to the tab titled `Scatter Plot`.
- Change `Correct only` for `Results:` to `All`.
- Change `X-Axis` to `cputime` for `base`.
- Change `Y-Axis` to `cputime` for one of `ours3`, `ours20`, or `apinis`.

The resulting plot shows runtimes of the `base` approach vs. the other. Each point is one program.
For points on the diagonal, both approaches took the same time. For points below it, the other approach was faster;
for those above it, `base` was faster.


> The analyses with WizWoz’s default update rule (972) and the update rule ours with a limit of 3 (975) and 20 (974) to the number of W/N switches, fail to complete in a similar number of cases, whereas the analysis with the update rule extracted from Apinis et al. (1003) fails to complete slightly more often

- Open `table-generator.table.html` and navigate to the tab titled `Table`.
- Then in the column `Goblint [...] base` (last one), select `Category -> Error`.
- The number at the top right `Showing 972 of 11222 tasks` gives the number of failures.

- Repeat for `ours3`, `ours20`, and `apinis`.


> The majority of timeouts and other failures are shared between all considered analyses.

Open `table-generator.diff.html`. This lists all tasks where the type of failure differs or one of the analysis produced a timeout and the other did not. Observe that it is only `42/11222` tasks where this is the case.

### A list of claims from the paper not supported by the artifact, and how/why.

Our motivation for (RQ4) is producing reliable performance measurements by using benchexec which uses cgroups and other mechanisms to ensure that runtimes are reliable. Given the virtualization which occurs by using VirtualBox, the results of such a run would be no more representative than runs conducted with the setup we used for (RQ1-3). While the configurations for (RQ1-3) incur some overhead for marshaling, it is the same for all update rules.
Thus, the results from that run can stand in to inspire confidence in the numbers for (RQ4) but cannot directly reproduce them.
