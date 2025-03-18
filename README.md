This is the artifact accompanying the conditionally accepted PLDI'25 paper **Taking out the Toxic Trash: Recovering Precision in Mixed Flow-Sensitive Static Analyses**.

**The system called `WizWoz` in the paper for double-blind review is in fact [Goblint](https://goblint.in.tum.de).**

The folder structure of this artifact (`~/precision-recovery-mixed-flowsens-benchmarks`) is as follows:

- `analyzer`: the Goblint analyzer
- `helper-scripts`: Some helper scripts
- `rq1-3benchmarks`: Contains the instructions to reproduce the evaluation for **RQ1-RQ3**
- `rq4-results`: Contains the raw data for **RQ4**
- `rq5-benchmarks`: Contains the instructions to reproduce the evaluation for **RQ5**

- `new-eval.pdf`: the updated evaluation section
- `README.md`: this file


There are two branches of the `analyzer` repository of relevance here:

- `pldi25_eval_runtime` used to measure runtimes.
- `pldi25_eval_stats` collects additional statistics but is slower.

In the artifact, `analyzer` is already checked out and dependencies are installed. If not proceed to **General setup of the analyzer** at the bottom.


# Getting Started

The artifact is a virtual machine packaged for `Oracle VirtualBox 6.1`, which is available from [Oracle](https://www.virtualbox.org/) and through the package manager of most distributions. The operating system is Ubuntu 24.04 LTS.

- The login is `goblint:goblint`.

- **Users not using `EN-US` keyboard**: Switch the keyboard layout to match yours by
    - Clicking `en` in the right upper corner and
    - Choosing your layout if suggested or clicking on `keyboard Settings` to set up another.


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

As the reviewers requested additional experiments, these instructions refer to reproducing the results of the evaluation section as submitted for the second deadline. We thus suggest proceeding in the following manner:

- Verify that the claims between the submitted version from HotCRP and the updated version of the evaluation (`new-eval.pdf`) do not differ substantially
- Verify that this artifact supports the claims from the updated version.

- The steps for reproduction and claims are split by **RQs**, as is the evaluation section.
    - For **RQ1-3**, follow the instructions in `./rq1-3-benchmarks/README.md`
    - For **RQ4**, see `/rq4-results/README.md`
    - For **RQ5**, follow the instructions in `./rq5-benchmarks/README.md`


# Reusability

The Goblint analyzer comes with extensive documentation (see `analyzer/docs`) or (perhaps more conveniently) the [rendered online version](https://goblint.readthedocs.io/). Of particular relevance are:

- The step-to-step user guide and the instructions for running on larger projects (https://goblint.readthedocs.io/en/latest/user-guide/running/#project-analysis). In this way, it is possible to conduct experiments on further programs
- The accessible step-by-step tutorial on adding custom analyses to the framework at https://goblint.readthedocs.io/en/latest/developer-guide/firstanalysis/. In the interest of a concise file, we opted against inlining this tutorial here.
- Any newly added analysis will be able to benefit from the update rules provided here.


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
This work was supported in part by the Shota Rustaveli National Science Foundation of Georgia (FR-21-7973) and by Deutsche Forschungsgemeinschaft (DFG) -- 378803395/2428 ConVeY.
