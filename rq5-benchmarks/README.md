There are two branches of the `analyzer` repository of relevance here:

- `pldi25_eval_runtime` is to be used with `update_bench_propertimings.rb` to obtain reliable runtimes
- `pldi25_eval_stats` collects additional statistics and is to be used with `update_bench_fullpreccomb.rb` for precision comparisons.


In the artifact, `analyzer` is already checked out and dependencies are installed. If not proceed to **General setup of the analyzer** at the bottom.




Steps for reproducing plots `4 & 7`:
    - (If not there already): Clone analyzer into top-level directory `git clone git@github.com:goblint/analyzer.git`
    - Change into the analyzer repo, run `git checkout pldi25_eval_stats` and `make release`   (TODO: is prec compare build automatically?)
    - From the `rq5-benchmarks`, run `./update_bench_fullpreccmp.rb --idead --priv-only &> plot4-7-raw.txt`
    - For plot 4:
        - Run `./fullpreccmp_to_csv_cumulative.py --mode all --compare glob plot4-7-raw.txt base > plot4-differences.csv`
        - Run `../helper-scripts/postprocess-csv.py plot4-differences.csv`
        -




TODO:
- `bench.txt` should only include the terminating ones, provide a separate file for those that do not
- Run `update_bench_fullpreccomb.rb` with `--idead` and `--priv-only` for Plot 4



# A list of claims from the paper supported by the artifact, and how/why.



# A list of claims from the paper not supported by the artifact, and how/why.

Our motivation for (RQ4) is producing reliable performance measurements by using benchexec which uses cgroups and other mechanisms to ensure that runtimes are reliable.
Given the virtualization which occurs by using VirtualBox, the results of such a run would be no more representative than runs conducted with the setup we used for (RQ1-3).
While the configurations for (RQ1-3) incur some overhead for marshaling, it is the same for all update rules.
Thus, the results from that run can stand in to inspire confidence in the numbers for (RQ4) but cannot directly reproduce them.


## General setup of analyzer

- Clone analyzer into top-level directory `git clone git@github.com:goblint/analyzer.git`
- `cd analyzer`
- `git checkout pldi25_eval_stats` (`pldi25_eval_runtime` will do too, dependencies are identical)
- `make setup`
- `make dev`
- `make release`
