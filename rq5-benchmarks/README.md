Login `goblint:goblint`


There are two branches of the `analyzer` repository of relevance here:

- `pldi25_eval_runtime` is to be used with `update_bench_propertimings.rb` to obtain reliable runtimes
- `pldi25_eval_stats` collects additional statistics and is to be used with `update_bench_fullpreccomb.rb` for precision comparisons.


In the artifact, `analyzer` is already checked out and dependencies are installed. If not proceed to **General setup of the analyzer** at the bottom.


- Steps for reproducing plots `5 & 6`:
    - Change into the analyzer repo, run `git checkout pldi25_eval_runtime` and `make release`
    - From the `rq5-benchmarks`, run `./update_bench_propertimings.rb --i 1 &> plot5-6-raw.txt`
            (By modifying the number supplied after `i`, you can specify that the average of more runs should be taken. To reduce runtimes, we recommend against it when reproducing results)
    - For plot 5
        - Run `./plot5.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/5/plot5.pdf`
    - For plot 6
        - Run `./plot6.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/6/plot6.pdf`

- Steps for reproducing plots `4 & 7`:
    - Change into the analyzer repo, run `git checkout pldi25_eval_stats` and `make release`   (TODO: is prec compare build automatically?)
    - From the `rq5-benchmarks`, run `./update_bench_fullpreccmp.rb --idead --priv-only &> plot4-7-raw.txt`
    - For plot 4:
        - Run `./plot4.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/4/plot4.pdf`
    - For plot 7:
        - Run `./plot7.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/7/plot7.pdf`

**To re-generate results based on the data we used for the paper, you can supply `--paper` as an argument to any of the `./plotN.sh`**


# A list of claims from the paper supported by the artifact, and how/why.

Plots 4-7: By reproducing them as outlined above

**Specific claims:**

-
    > When turning to net precision changes by aggregating precision losses and gains per program, we find that the update rule ours improves precision in 24 out of 38 cases, with 12 of these improvements being substantial. ours-bot improves precision for 32 programs, with 15 substantial improvements.

    > ours and ours-bot worsen net precision in only three and two cases, respectively, with two cases showing substantial losses for both approaches.

    -  and `./compare.py--compare ours-bot`

        (Supplying `--paper` to run with our results)

-
    > ours-bot always improves at least as many unknowns as ours and often more.

    -   From Plot 4


-
    > The update rule apinis, on the other hand, improves net precision in only 11 cases, with six of these being substantial.
    Conversely, it worsens net precision in 18 cases, with 11 of these precision losses being substantial.

    -  Run `./compare.py --compare apinis`
        (Supplying `--paper` to run with our results)

-
    > Abstract garbage collection generally comes with a moderate slowdown, but causes a slowdown by a factor of 2.72 in the extreme.

    - From Plot 5 and Running `./overhead.py`
        (Supplying `--paper` to run with our results)

-
    > For 18 out of 38 cases, over 40\% of contexts are identified as dead.

    -  Run `./dead-contexts.py`
        (Supplying `--paper` to run with our results)

    > We find that ours-bot increases memory usage by 15% for two programs, while it yields a reduction for 18 programs. At the extremes, the magnitude of the reduction is considerable. For ypbind and smtprc, e.g., the heap memory footprint is roughly halved.

    - Run `./garbage.py`
        (Supplying `--paper` to run with our results)

TODO:
- `bench.txt` should only include the terminating ones, provide a separate file for those that do not






# A list of claims from the paper not supported by the artifact, and how/why.

Our motivation for (RQ4) is producing reliable performance measurements by using benchexec which uses cgroups and other mechanisms to ensure that runtimes are reliable.
Given the virtualization which occurs by using VirtualBox, the results of such a run would be no more representative than runs conducted with the setup we used for (RQ1-3).
While the configurations for (RQ1-3) incur some overhead for marshaling, it is the same for all update rules.
Thus, the results from that run can stand in to inspire confidence in the numbers for (RQ4) but cannot directly reproduce them.


## General setup of analyzer

- Clone analyzer into top-level directory `https://github.com/goblint/analyzer.git`
- `cd analyzer`
- `git checkout pldi25_eval_stats` (`pldi25_eval_runtime` will do too, dependencies are identical)
- `make setup`
- `make dev`
- `make release`
