# Reproduction of Experiments for RQ1-3

The folder structure for this RQ (`~/precision-recovery-mixed-flowsens-benchmarks/rq1-3-benchmarks`) is as follows:

- `paper-runs`: Folder containing the raw data of the runs underlying the plots in the paper
- `plots`: Tex files with pgplots plots for plotting results
- `bench.txt`: Specifies the full list of benchmark programs
- `reduced.txt`: Specifies the reduced list of benchmark programs recommended for reproduction
- Various Ruby / Python / Shell scripts


There are several levels of reproduction possible here:

- **A**: The folder `paper-runs` contains the data produced by the runs we used for the paper. This allows reproducing the plots and data from our raw results. **(Recommended)**
- **B**: We provide a subset of the benchmarks (including the ones used for Plot 3) for which results can realistically be reproduced inside the VM **(Recommended)**
- **C**: We provide the scripts for a full reproduction (all 11k SV-COMP programs). This requires a machine with a considerable number `N` of cores so runtime is acceptable, e.g., 40 for the config and at least `15GB*N` of RAM and a runtime of several days (assuming N=48 cores). **(Not Recommended)**


In the artifact, `sv-comp` is already checked out at the correct path. If recreating the artifact from scratch proceed to **General setup of SV-COMP** at the bottom.

## Step 1: Producing the raw data

First step: Change into the analyzer repo `cd ..`, run `git checkout pldi25_eval_runtime`, and `make release`.
Then, change back to this directory.

The raw data here takes the form of a text file `svcomp-raw.txt`. The folder `paper-runs` contains the version of this raw data corresponding to the run in the paper.

### Option A

As our raw data is used, nothing is to be done.


### Option B

From this directory, run `./run-sv-comp.rb --pin --clean --reduced > svcomp-raw.txt 2> progress.txt`

**Expected Runtime**: Around 1h40min

If you want to keep track of the progress you can open an additional terminal `tail -f progress.text`.


### Option C

From this directory, run `./run-sv-comp.rb --pin --clean -j 40 > svcomp-raw.txt 2> progress.txt`

The `-j` parameter provides the number of concurrent runs to execute.

(The runtime here is on the magnitude of days with N=48 cores)


##  Step 2: Producing the plots

(For **Option A:** pass `--paper` as an additional argument to the scripts)

- For plot 2
    - Run `./plot2.sh` (Should this fail to the correct output check the individual steps listed in that file)
    - The resulting plot is located in `plots/2/plot2.pdf`
- For plot 3
    - Run `./plot3.sh` (Should this fail to the correct output check the individual steps listed in that file)
    - The resulting plot is located in `plots/3/plot3.pdf`

## A list of claims from the paper supported by the artifact, and how/why.

- Total number of tasks and terminating task
    - plots/2/timeout-counts.tex

- Fig. 2 (by reproducing the plot)
- Fig. 3 (by reproducing the plot)

- **RQ1**

    > Concerning (RQ1), we find a net precision improvement in about 52% of tasks when using the new update rule with the number of W/N switches limited to either 3 (ours3) or 20 (ours20). 13% (ours3) and 20% (ours20) of tasks show substantial improvements. Conversely, ours loses precision compared to the baseline on about 1% of tasks, where almost all show substantial losses in precision.

    - Run `./compare.py --compare ours3` and `./compare.py --compare ours20`
    - (For **Option A:** adding `--paper`)

    > The subcategory ReachSafety-Recursive benefits particularly from update rule ours (see fig. 3). Both analyses provide substantial improvements in about 43% of cases. Interestingly, the share of degraded cases is also greater with about 4%.

    - Run `./compare.py --compare ours3 --rec` and `./compare.py --compare ours20 --rec`
    - (For **Option A:** adding `--paper`)

- **RQ2**

    > W.r.t. (RQ2), the update rule apinis produces an improvement only in about 40% of tasks, which are substantial only in 7% of tasks. At the same time, 18% of the tasks have a net precision loss and 11% a substantial loss.

    - Run `./compare.py --compare apinis`
    - (For **Option A:** adding `--paper`)

    > On the subset of ReachSafety-Recursive the update rule apinis achieves substantial precision improvements only in about 21% of cases, whereas it is 43% for the new update rule.

    - Run `./compare.py --compare apinis --rec`
    - (For **Option A:** adding `--paper`)

- **RQ3**:

    > Regarding (RQ3), the update rule ours yields an improvement on 52% of tasks, regardless of whether the widening limit was set to 3 or 20. However, with a W/N limit of 20, 20% of tasks show substantial improvements, instead of 13% with the limit of 3. On ReachSafety-Recursive, with both limits to the number of W/N switches, an equal amount of precision is recovered (43%).

    - See **RQ1**.


## General setup of SV-COMP

- Clone sv-benchmarks at specific tag `svcomp24` into the parent director directory `git clone --branch svcomp24-final --depth 1 https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks.git`
