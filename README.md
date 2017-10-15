
# AI for Breakthrough

- `make` to build
- `make run` to run the program

## V1:
- no alpha-beta pruning
 - several utility/evaluation function
     - controlled by `MinimaxAgent::maxerUtility()` and `MinimaxAgent::minerUtility()`

## V2
- with alpha-beta pruning
- `MinimaxAgent(maxdepth, enablePrune, evaluatorClass)`
- `MinimaxAgent` uses an Evaluator class to do evaluation, see the defination of `class Evalutor`
- Some Evaluators are defined in fiel `Evaluator.h/cpp`, these evaluators can be combined with different factors.
    - `SimpleEvaluator`
    - `DefensiveHeuristicEvaluator`
    - `OffensiveHeuristicEvaluator`
    - `DistanceFromBaseEvaluator` : poor evaluator
- set `interactive=true` in `main.cpp` to observe the moves
