There are two branches of the `analyzer` repository of relevance here:

- `pldi25_eval_runtime` is to be used with `update_bench_propertimings.rb` to obtain reliable runtimes
- `pldi25_eval_stats` collects additional statistics and is to be used with `update_bench_fullpreccomb.rb` for precision comparisons.


TODO:
- `bench.txt` should only include the terminating ones, provide a separate file for those that do not
- Run `update_bench_fullpreccomb.rb` with `--idead` and `--priv-only` for Plot 4