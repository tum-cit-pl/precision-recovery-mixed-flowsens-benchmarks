Steps:
    - Change into the analyzer repo, run `git checkout pldi25_eval_runtime` and `make release`
    - Run `./run-sv-comp.rb --pin --clean -j 20 > svcomp-raw.txt 2> progress.txt`


    - From the `rq5-benchmarks`, run `./update_bench_propertimings.rb --i 1 &> plot5-6-raw.txt`
            (By modifying the number supplied after `i`, you can specify that the average of more runs should be taken. To reduce runtimes, we recommend against it when reproducing results)
    - For plot 5
        - Run `./plot5.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/5/plot5.pdf`
        - If you want to generate the plot based on the data we used in the paper call `./plot5.sh --paper`
    - For plot 6
        - Run `./plot6.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/6/plot6.pdf`
        - If you want to generate the plot based on the data we used in the paper call `./plot6.sh --paper`

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


## General setup of sv-comp

- Clone sv-benchmarks at specific tag `svcomp24` into this directory `git clone --branch svcomp24-final --depth 1  https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks.git`
