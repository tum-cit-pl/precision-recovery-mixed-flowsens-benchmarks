# Changes made to Goblint

Below, we describe the changes made to Goblint in the course of implementing the proposed update rules.
These changes can be inspected on [this site](https://github.com/goblint/analyzer/compare/50e8ab969afa1c35e035ecae57fb90863dbbae94...pldi25_eval_runtime) under the `Files changed` tab.

In the following, we describe the changes that can be seen at this URL in more detail.

#### Update Rules in `src/solver/td3.ml`:
The update rules where added to the top-down solver that is implemented in `td3.ml`.
The version of the top-down solver is described in ["The Top-Down Solver—An Exercise in A²I"](https://link.springer.com/chapter/10.1007/978-981-19-9601-6_9).
A version of the top-down solver for side-effecting constraint systems (TD_{side}) is described in ["Three Improvements to the Top-Down Solver"](https://doi.org/10.1017/S0960129521000499); this description is closer to the implementation in Goblint.

There are some peculiarities in Goblint in the implementation of side-effecting constraint systems for dealing with mixed flow-sensitivity that make the implementation of the update rules more challenging.

In particular:
- In Goblint, the evaluation of a right-hand side may throw exceptions that indicate that the contribution yields `Deadcode`.
- Side-effects occur *during* the evaluation of a right-hand side.
- During the evaluation of a right-hand side, *multiple* side-effects to the same unknown may occur.
- Some side-effected contributions are performed at the beginning as a setup with no origin associated to them. We call these *orphaned* contributions.

These additional challenges are reflected in the code changes in the `td3.ml` file.
Explanations for the changes in that file are as follows:

- Lines 81 - 83, 132-134, 255-257: maps `prev_sides`, `divided_side_effects` and `orphan_side_effects` are introduced.
 The map `prev_sides` is used to track contributions for the abstract garbage collection and corresponds to `old_contribs` in listing 10.
 The map `divided_side_effects` corresponds to `cmap` in the paper.
 The map `orphan_side_effects` is used to track orphaned side-effects to allow special treatment for them.
- [Lines 180-193: Some explicit reloading of those maps is defined for the case the solver is run in the incremental mode.]
- Lines 280-288: Configuration options for update rules are loaded. There, `narrow_sides` indicates that our proposed update rule should be used.
The option `narrow_sides_conservative_widen` corresponds to reluctant widening in the paper.
- Lines 382-417:
	- Our update rule is integrated into the place where a right-hand side is evaluated.
	Before our changes, this evaluation happened by calling `eq x (eval l x) (side ~x)`.
	For our approach (when `narrow_sides` is `true`), an adapted call `eq x (eval l x) (side_acc acc changed x)` is performed.
	- To deal with the possibility that the evaluation of the right-hand side throws an exception, this call is wrapped in a `Fun.protect`, together with the code in lines 386-414 that is to be executed after the evaluation.
	- Lines 386-404 take care of the treatment of withdrawn contributions:
	For each unknown that received a side-effect earlier, i.e., is in `prev_sides_x`, if it does not receive a side-effect now, i.e., is not in `acc`, then an explicit bottom side-effect is performed.
	For the case that `y` has now the value bottom, line 394 contains the call to `solve` for all unknowns returned by the function `postmortem`.
	In the case that `y` is an unknown for the start point of a procedure, `postmortem` returns the end point, (see lines 553-556 in `src/framework/constraints.ml`).
    - Lines 398-404: The data structure `prev_sides` is updated.
	- Lines 405-414 we detail the case which is also used for the experiments where growing contributions are applied immediately.
	In line 406, for all side-effects in `acc` that have not been eagerly applied during the evaluation of the right-hand side, i.e., are not in `changed`, narrowing is performed.
- Lines 473-477: Define the function `combined_side` that, for a given global `y`, joins the contributions from all origins (stored in `divided_side_effects`), as well as the orphaned contributions to it.
- Lines 479-492: Define the function `side_acc acc changed x y d` that replaces `side x y d`.
When a contribution `d` to `y` is encountered, it is checked, whether it is already subsumed by previous contributions from this evaluation of the right-hand side of `x`.
In this case, nothing happens.
Otherwise, the data structure `acc` is updated to account for this value.
Additionally, `divided_side D_Widen ~x y new_acc` is called.
If this results in a change, i.e., returns `true`, `y` is added to `changed` as the side-effect has been eagerly applied.
This serves as the interface between the solver and the update rules.
- Lines 498-556 implement the apinis update rule.
- Lines 557-650 implement the "ours" update rule.
   - Lines 569-635 handle the case that the contribution has an origin (i.e., not orphaned).
		- Lines 570-573 adds the contribution to the data structure `sides` as required by the solver
		- Lines 574-575 initializes `divided_side_effects`.
		- Lines 578-583 determine the phase, i.e., which operator to apply
		If the phase is narrowing, but the gas is exhausted, the function returns `false`.
		- Lines 585-632: Otherwise, we distinguish two cases.
			- Lines 587-594:
				- If widening is to be applied, we first check whether the old side effect `old_side` subsumes the new one `d`. If this is the case, we return the old side-effect. Otherwise, if reluctant widening is used, and the new value is subsumed by the join over all origins, the stored phase is switched to widening, and the new and the old contribution are joined. Otherwise, a widening is performed.
			- Lines 595-608:
				- If narrowing is to be applied, it is applied.
				As the Goblint framework does not natively ensure that narrowing with bottom yields bottom, this is enforced in line 600.
				- If narrowing changed the value, and this was the first narrowing after widening, the gas is reduced.
		- If the new side-effect is equal to the old side-effect, we return `false`.
		- Lines 611-630: Otherwise:
			- Lines 613-616: The contribution is recorded in `y_sides`. For infinite widening gas, as an optimization, the binding can be removed completely, if the value is bottom.
			- Lines 617-622: The new value of `y` is computed as the join over the contributions from all origins; with an optimization to reduce the number of binary joins where applicable.
			- Lines 623-628: In case the value of `y` changed, the solver processes the new values of `y` as usual, i.e., replaces the value in `rho` and performs a `destabilize` to mark all potentially affected unknowns as unstable.
   - Lines 635-650 handle the case that the contribution does not have an origin.

#### Configuration options in `src/config/options.schema.json`:
New configuration options for Goblint were added. Configuration options specific to the new update rule are defined in lines 2503-2551.

#### Added tests in `tests/regression/*`:
Test files were added to the regression suite of Goblint for showcasing precision gains and checking for soundness.
Goblint can be run on specific tests using `regtest.sh` and giving the index of the group and test with in the group.
For example, goblint can be run on `tests/regression/95-divided/03-guarded_inc.c` with the command:
```
./regtest.sh 95 03
```
The output can then be inspected on the console.

#### BasePriv `src/analyses/basePriv.ml`:
Some improvements were made to the analysis of concurrent code to gain additional precision as these opportunities were noticed during development.
