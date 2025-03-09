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


## General setup of analyzer

- Clone analyzer into top-level directory `git clone git@github.com:goblint/analyzer.git`
- `cd analyzer`
- `git checkout pldi25_eval_stats` (`pldi25_eval_runtime` will do too, dependencies are identical)
- `make setup`
- `make dev`
- `make release`
