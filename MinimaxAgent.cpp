/* =============================================================================
#     FileName: MinimaxAgent.cpp
#         Desc: MinimaxAgent
#       Author: YanlongLi
#        Email: lansunlong@gmail.com
#     HomePage: http://www.yanlongli.me
#      Created: 2017-10-14 01:02:34
#      Version: 0.0.1
#   LastChange: 2017-10-14 06:43:11
#      History:
#               0.0.1 | YanlongLi | init
============================================================================= */

#include "MinimaxAgent.h"
#include "Evaluator.h"
#include "utils.h"
#include <cfloat>
#include <algorithm>

MinimaxAgent::MinimaxAgent(long long maxdepth, bool _alphaBetaPrune, Evaluator* _evaluator)
    : MAX_DEPTH(maxdepth), alphaBetaPrune(_alphaBetaPrune), evaluator(_evaluator) {
    depth = 0;
}

/*
 * the max value we can get under current state
 * current board is result of maxer's action
 * so we simulate miner's actions and get the max
 */
double MinimaxAgent::maxValue(const Board& board) {
    int wl = this->checkWinOrLoss(board);
    if (wl != 0) return (*evaluator).maxerEvaluation(board); // terminal state, so maxer win
    //
    depth ++;
    if (depth >= MAX_DEPTH) { // reatch max depth
        return (*evaluator).maxerEvaluation(board);
    }
    //
    vector<Action> actions = validActionByMiner(board);
    double v = -DBL_MAX;
    for (auto action : actions) {
        v = max(v, minValue(action.result()));
        if (alphaBetaPrune) {
            if (v >= beta) break;
            alpha = max(alpha, v);
        }
    }
    return v;
}

/*
 * the min value we can get under current state
 * current board is result of miner's action
 * so we simulate maxer's actions and get the min
 */
double MinimaxAgent::minValue(const Board& board) {
    int wl = this->checkWinOrLoss(board);
    if (wl != 0) return (*evaluator).minerEvaluation(board); // terminal state, so miner win
    //
    depth ++;
    if (depth >= MAX_DEPTH) { // reatch max depth
        return (*evaluator).minerEvaluation(board);
    }
    //
    double v = DBL_MAX;
    vector<Action> actions = validActionByMaxer(board);
    for (auto action : actions) {
        v = min(v, maxValue(action.result()));
        if (alphaBetaPrune) {
            if (v <= alpha) break;
            beta = min(beta, v);
        }
    }
    return v;
}

Board MinimaxAgent::nextByMaxer(const Board& board) {
    depth = 0;
    // assume the input is not a terminal state
    vector<Action> actions = validActionByMaxer(board);
    Action* decision = NULL;
    double v = -DBL_MAX;
    for (auto action : actions) {
        double t = maxValue(action.result());
        if (t > v) {
            v = t;
            if (decision == NULL) {
                decision = new Action(board);
            }
            *decision = action;
        }
    }
    if (decision == NULL) {
        fprintf(stderr, "no action returned\ncurrent board for maxer:\n");
        printBoard(board);
        fprintf(stderr, "valid action: %ld\n", actions.size());
        fprintf(stderr, "%f\n", v);
        for (Action action : actions) {
            double t = maxValue(action.result());
            fprintf(stderr, "%f\n", t);
        }
        exit(-1);
    }
    return decision->result();
}
Board MinimaxAgent::nextByMiner(const Board& board) {
    depth = 0;
    alpha = -DBL_MAX;
    beta = DBL_MAX;
    // assume the input is not a terminal state
    vector<Action> actions = validActionByMiner(board);
    Action* decision = NULL;
    double v = DBL_MAX;
    for (auto action : actions) {
        double t = minValue(action.result());
        if (t < v) {
            v = t;
            if (decision == NULL) {
                decision = new Action(board);
            }
            *decision = action;
        }
    }
    if (decision == NULL) {
        fprintf(stderr, "no action returned\ncurrent board for miner:\n");
        printBoard(board);
        fprintf(stderr, "valid action: %ld\n", actions.size());
        for (Action action : actions) {
            double t = minValue(action.result());
            fprintf(stderr, "%f\n", t);
        }
        exit(-1);
    }
    return decision->result();
}
