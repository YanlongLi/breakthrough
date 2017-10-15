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
#include "utils.h"
#include <cfloat>
#include <algorithm>

MinimaxAgent::MinimaxAgent(long long maxdepth, bool alphaBetaProune) {
    depth = 0;
    MAX_DEPTH = maxdepth;
}

double MinimaxAgent::maxerUtility(const Board& board) {
    // double r = simpleUtility(board);
    // double r = defensiveHeuristic(board, 1);
    double r = offensiveHeuristic(board, 1);
    // double r = 2 * distanceFromBase(board, 2, 1) + 2 * distanceFromBase(board, 2, -1);
    return r + (rand() / (float)RAND_MAX);
}

double MinimaxAgent::minerUtility(const Board& board) {
    // double r = simpleUtility(board);
    // double r = defensiveHeuristic(board, -1);
    double r = offensiveHeuristic(board, -1);
    // double r = 2 * distanceFromBase(board, 2, 1) + 2 * distanceFromBase(board, 2, -1);
    return r + (rand() / (float)RAND_MAX);
}

/*
 * SimpleUtility, compute the the difference of work number
 */
double MinimaxAgent::simpleUtility(const Board& board) {
    int finish = this->checkWinOrLoss(board);
    if (finish != 0) {
        return finish == 1 ? 20 : -20;
    }
    int sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += board.getValue(i, j);
    return sum;
}

/*
 * 2*(number_of_own_pieces_remaining)
 */
double MinimaxAgent::defensiveHeuristic(const Board& board, int player) {
    if (player != 1 && player != -1) {
        fprintf(stderr, "invalid player value: %d\n", player);
        exit(-1);
    }
    int nOne = 0, nMinusOne = 0;
    for (int  i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board.getValue(i, j) == 1) nOne ++;
            else if (board.getValue(i, j) == -1) nMinusOne ++;
        }
    }
    return 2 * (player == 1 ? nOne : nMinusOne);
}

/*
 * 2*(30 - number_of_opponent_pieces_remaining)
 */
double MinimaxAgent::offensiveHeuristic(const Board& board, int player) {
    if (player != 1 && player != -1) {
        fprintf(stderr, "invalid player value: %d\n", player);
        exit(-1);
    }
    int nOne = 0, nMinusOne = 0;
    for (int  i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board.getValue(i, j) == 1) nOne ++;
            else if (board.getValue(i, j) == -1) nMinusOne ++;
        }
    }
    return 2 * (player == 1 ? nMinusOne : nOne);
}

/*
 * average distance of n workers that far from base
 */
double MinimaxAgent::distanceFromBase(const Board& board, int n, int player) {
    if (player != 1 && player != -1) {
        fprintf(stderr, "invalid player value: %d\n", player);
        exit(-1);
    }
    int count = 0, sum = 0;
    if (player == 1) {
        for (int k = N * N - 1; k >= 0; k--) {
            int i = k / N, j = k % N;
            if (board.getValue(i, j) == 1) {
                count ++;
                sum += j * j;
                if (count == n) {
                    break;
                }
            }
        }
        if (count == 0) {
            fprintf(stderr, "invalid board, no type %d worker\n", player);
            exit(-1);
        }
        return sum / (double)count;
    } else {
        for (int k = 0; k < N * N; k++) {
            int i = k / N, j = k % N;
            if (board.getValue(i, j) == 1) {
                count ++;
                sum += (N - 1 - j) * (N - 1 - j);
                if (count == n) {
                    break;
                }
            }
        }
        if (count == 0) {
            fprintf(stderr, "invalid board, no type %d worker\n", player);
            exit(-1);
        }
        return sum / (double)count;
    }
}

/*
 * the max value we can get under current state
 * current board is result of maxer's action
 * so we simulate miner's actions and get the max
 */
double MinimaxAgent::maxValue(const Board& board) {
    int wl = this->checkWinOrLoss(board);
    if (wl != 0) return maxerUtility(board); // terminal state, so maxer win
    //
    depth ++;
    if (depth >= MAX_DEPTH) { // reatch max depth
        return maxerUtility(board);
    }
    //
    vector<Action> actions = validActionByMiner(board);
    double v = DBL_MIN;
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
    if (wl != 0) return minerUtility(board); // terminal state, so miner win
    //
    depth ++;
    if (depth >= MAX_DEPTH) { // reatch max depth
        return minerUtility(board);
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
    double v = DBL_MIN;
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
    alpha = DBL_MIN;
    beta = DBL_MAX;
    // assume the input is not a terminal state
    vector<Action> actions = validActionByMiner(board);
    Action* decision = NULL;
    double v = DBL_MAX;
    for (auto action : actions) {
        double t = minValue(action.result());
        if (t > v) {
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
