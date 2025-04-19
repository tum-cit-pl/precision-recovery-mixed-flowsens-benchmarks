This is the artifact accompanying the PLDI'25 paper **Taking out the Toxic Trash: Recovering Precision in Mixed Flow-Sensitive Static Analyses** by F. Stemmler, M. Schwarz, J. Erhard, S. Tilscher, and H. Seidl.

The folder structure of this artifact (`~/precision-recovery-mixed-flowsens-benchmarks`) is as follows:

- `analyzer`: the Goblint analyzer
- `helper-scripts`: Some helper scripts
- `rq1-3benchmarks`: Contains the instructions to reproduce the evaluation for **RQ1-RQ3**
- `rq4-results`: Contains the raw data for **RQ4**
- `rq5-benchmarks`: Contains the instructions to reproduce the evaluation for **RQ5**

- `README.md`: this file
- `CODE.md`: A description of the changes made to Goblint.


There are two branches of the `analyzer` repository of relevance here:

- `pldi25_eval_runtime` used to measure runtimes.
- `pldi25_eval_stats` collects additional statistics but is slower.

In the artifact, `analyzer` is already checked out and dependencies are installed. If recreating the artifact from scratch proceed to **General setup of the analyzer** at the bottom.


# Getting Started

The artifact is a virtual machine packaged for `Oracle VirtualBox 6.1`, which is available from [Oracle](https://www.virtualbox.org/) and through the package manager of most distributions. The operating system is Ubuntu 24.04 LTS.

- For help importing the virtual machine, see https://docs.oracle.com/cd/E26217_01/E26796/html/qs-import-vm.html

- The login is `goblint:goblint`.

- **Users not using `EN-US` keyboard**: Switch the keyboard layout to match yours by
    - Clicking `en` in the right upper corner and
    - Choosing your layout if suggested or clicking on `Keyboard Settings` to set up another.


- Verify the analyzer works by
    - (Navigating to the folder of the artifact (`~/precision-recovery-mixed-flowsens-benchmarks`))
    - `cd analyzer`
    - `make sanitytest` (it may run a few minutes)
    - Expected output:

    ```
    Excellent: ignored check on tests/regression/03-practical/21-pfscan_combine_minimal.c:21 is now passing!
    Excellent: ignored check on tests/regression/03-practical/21-pfscan_combine_minimal.c:29 is now passing!
    No errors :)
    ```


# Step-by Step Reproduction

The steps for reproduction and claims are split by **RQs**, as is the evaluation section.
    - For **RQ1-3**, follow the instructions in `./rq1-3-benchmarks/README.md`
    - For **RQ4**, see `./rq4-results/README.md`
    - For **RQ5**, follow the instructions in `./rq5-benchmarks/README.md`


# Reusability

There are several axes along which other researchers can build on this work; we briefly sketch two of these here:

## Re-use the analyzer

The Goblint analyzer comes with extensive documentation (see `analyzer/docs`) or (perhaps more conveniently) the [rendered online version](https://goblint.readthedocs.io/). Of particular relevance here are:

- The step-to-step user guide and the instructions for running on larger projects (https://goblint.readthedocs.io/en/latest/user-guide/running/#project-analysis). In this way, it is possible to conduct experiments on further programs.
- The accessible step-by-step tutorial on adding custom analyses to the framework at https://goblint.readthedocs.io/en/latest/developer-guide/firstanalysis/. In the interest of a concise file, we opted against inlining this tutorial here.
- Any newly added analysis will be able to benefit from the update rules provided here.

Thus, the framework can serve as a testbed for new ideas for static analysis, allowing researchers to focus on the aspect of the system they are interested on while relying on the framework for everything else.
The changes made to Goblint to implement the update rules are outlined in [CODE.md](CODE.md).

### Example

We added an example program `example.c` to the top folder of `analyzer` to highlight precision differences between configurations.
For details see [EXAMPLE.md](EXAMPLE.md).

## Experiment with further programs within this VM

All scripts are written in a way where it is easy to add further programs to the setup, or experiment with different settings and analyses.
To this end, it suffices to modify the respective `bench.txt` files by, e.g.,

- a) adding additional programs on which to experiment to the end or
- b) specifying additional configurations which to run at the beginning of the file.

# General setup of analyzer

- Clone analyzer into top-level directory `git clone git@github.com:goblint/analyzer.git`
- `cd analyzer`
- `git checkout pldi25_eval_stats` (`pldi25_eval_runtime` will do too, dependencies are identical)
- `make setup`
- `make dev`
- `make release`


# Acknowledgments

We would like to thank the anonymous reviewers for their valuable feedback, which was instrumental in polishing the paper.
DeepSeek was used to help with the creation of scripts for extracting precision data from logfiles.
This work was supported in part by Deutsche Forschungsgemeinschaft (DFG) -- 378803395/2428 ConVeY.
