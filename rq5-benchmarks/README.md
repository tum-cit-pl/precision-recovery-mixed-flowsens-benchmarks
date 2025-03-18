# Reproduction of Experiments for RQ5

There are several levels of reproduction possible here:

- **A**: The folder `paper-runs` contains the data produced by the runs we used for the paper. This allows reproducing the plots and data from our raw results. **(Recommended)**
- **B**: We provide a subset of the benchmarks which realistically be reproduced inside the VM **(Recommended)**
- **C**: We provide the scripts for a full reproduction. The runtime for this is several days. **(Not Recommended)**

## Producing the raw data

The raw data here takes the form of two text files `plot4-7-raw.txt` and `plot5-6-raw.txt`. The folder `paper-runs` contains the version of this raw data corresponding to the run in the paper.

### Option A

As our raw data is used, nothing is to be done.

### Option B

1. Change into the analyzer repo, run `git checkout pldi25_eval_runtime` and `make release`
2. From the `rq5-benchmarks`, run `./update_bench_propertimings.rb --i 1 --reduced &> plot5-6-raw.txt`
        (By modifying the number supplied after `i`, you can specify that the average of more runs should be taken. To reduce runtimes, we recommend against it when reproducing results)

**Note:** Those with more patience may add programs from `bench.txt` back to `reduced.txt` to increase the subset of considered programs.

### Option C

1. Change into the analyzer repo, run `git checkout pldi25_eval_runtime` and `make release`
2. From the `rq5-benchmarks`, run `./update_bench_propertimings.rb --i 1 &> plot5-6-raw.txt`
        (By modifying the number supplied after `i`, you can specify that the average of more runs should be taken. To reduce runtimes, we recommend against it when reproducing results)


3. Change into the analyzer repo, run `git checkout pldi25_eval_stats` and `make release`
4. From the `rq5-benchmarks`, run `./update_bench_fullpreccmp.rb --idead --priv-only &> plot4-7-raw.txt`


## Producing the plots

(For **Option A:** pass `--paper` as an additional argument to the scripts)

- Steps for reproducing plots `5 & 6`:
    - For plot 5
        - Run `./plot5.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/5/plot5.pdf`
    - For plot 6
        - Run `./plot6.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/6/plot6.pdf`

- Steps for reproducing plots `4 & 7`:
    - For plot 4:
        - Run `./plot4.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/4/plot4.pdf`
    - For plot 7:
        - Run `./plot7.sh` (Should this fail to the correct output check the individual steps listed in that file)
        - The resulting plot is located in `plots/7/plot7.pdf`

## A list of claims from the paper supported by the artifact, and how/why.

Plots 4-7: By reproducing them as outlined above

**N.B.**: Runtimes in the VM were observed to be quite a lot slower overall, though the relationship between configurations should still be the same.

**Specific claims:**

-
    > When turning to net precision changes by aggregating precision losses and gains per program, we find that the update rule ours improves precision in 24 out of 38 cases, with 12 of these improvements being substantial. ours-bot improves precision for 32 programs, with 15 substantial improvements.

    > ours and ours-bot worsen net precision in only three and two cases, respectively, with two cases showing substantial losses for both approaches.

    - Run `./compare.py --compare ours` and `./compare.py --compare ours-bot`
     - (For **Option A:** adding `--paper`)

-
    > ours-bot always improves at least as many unknowns as ours and often more.

    -   From Plot 4


-
    > The update rule apinis, on the other hand, improves net precision in only 11 cases, with six of these being substantial.
    Conversely, it worsens net precision in 18 cases, with 11 of these precision losses being substantial.

    -  Run `./compare.py --compare apinis`
     - (For **Option A:** adding `--paper`)


-
    > Abstract garbage collection generally comes with a moderate slowdown, but causes a slowdown by a factor of 2.72 in the extreme.

    - From Plot 5 and Running `./overhead.py`
    - (For **Option A:** adding `--paper`)

-
    > For 18 out of 38 cases, over 40\% of contexts are identified as dead.

    -  Run `./dead-contexts.py`
    - (For **Option A:** adding `--paper`)


    > We find that ours-bot increases memory usage by 15% for two programs, while it yields a reduction for 18 programs. At the extremes, the magnitude of the reduction is considerable. For ypbind and smtprc, e.g., the heap memory footprint is roughly halved.

    - Run `./garbage.py`
    - (For **Option A:** adding `--paper`)


TODO:
- `bench.txt` should only include the terminating ones, provide a separate file for those that do not
