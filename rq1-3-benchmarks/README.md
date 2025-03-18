Steps:
    - Change into the analyzer repo, run `git checkout pldi25_eval_runtime` and `make release`
    - Run `./run-sv-comp.rb --pin --clean -j 40 > svcomp-raw.txt 2> progress.txt`

    - For plot 2
        - Run `./plot2.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/2/plot2.pdf`
    - For plot 3
        - Run `./plot3.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/3/plot3.pdf`


# A list of claims from the paper supported by the artifact, and how/why.

- Total number of tasks and terminating task
    - plots/2/timeout-counts.tex

- Fig. 2 (by potentially reproducing the plot)
- Fig. 3 (by reproducing the plot)

- **RQ1**

    > Concerning (RQ1), we find a net precision improvement in about 52% of tasks when using the new update rule with the number of W/N switches limited to either 3 (ours3) or 20 (ours20). 13% (ours3) and 20% (ours20) of tasks show substantial improvements. Conversely, ours loses precision compared to the baseline on about 1% of tasks, where almost all show substantial losses in precision.

    - Run `./compare.py --compare ours3` and `./compare.py --compare ours20`
    - (adding `--paper` to use our results)

    > The subcategory ReachSafety-Recursive benefits particularly from update rule ours (see fig. 3). Both analyses provide substantial improvements in about 43% of cases. Interestingly, the share of degraded cases is also greater with about 4%.

    - Run `./compare.py --compare ours3 --rec` and `./compare.py --compare ours20 --rec`
    - (adding `--paper` to use our results)

- **RQ2**

    > W.r.t. (RQ2), the update rule apinis produces an improvement only in about 40% of tasks, which are substantial only in 7% of tasks. At the same time, 18% of the tasks have a net precision loss and 11% a substantial loss.

    - Run `./compare.py --compare apinis`
    - (adding `--paper` to use our results)

    > On the subset of ReachSafety-Recursive the update rule apinis achieves substantial precision improvements only in about 21% of cases, whereas it is 43% for the new update rule.

    - Run `./compare.py --compare apinis --rec`
    - (adding `--paper` to use our results)

- **RQ3**:

    > Regarding (RQ3), the update rule ours yields an improvement on 52% of tasks, regardless of whether the widening limit was set to 3 or 20. However, with a W/N limit of 20, 20% of tasks show substantial improvements, instead of 13% with the limit of 3. On ReachSafety-Recursive, with both limits to the number of W/N switches, an equal amount of precision is recovered (43%).

    - See **RQ1**.


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

- Clone sv-benchmarks at specific tag `svcomp24` into this directory `git clone --branch svcomp24-final --depth 1 https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks.git`


---------------------

We would like to thank the anonymous reviewers for their valuable feedback, which was instrumental in polishing the paper.
DeepSeek was used to help with the creation of scripts for extracting precision data from logfiles.
This work was supported in part by the Shota Rustaveli National Science Foundation of Georgia (FR-21-7973) and by Deutsche Forschungsgemeinschaft (DFG) -- 378803395/2428 ConVeY.
