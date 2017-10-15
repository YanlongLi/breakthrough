/* =============================================================================
#     FileName: Evaluator.cpp
#         Desc: Base class for evaluation function
#       Author: YanlongLi
#        Email: lansunlong@gmail.com
#     HomePage: http://www.yanlongli.me
#      Created: 2017-10-14 22:09:02
#      Version: 0.0.1
#   LastChange: 2017-10-14 22:09:02
#      History:
#               0.0.1 | YanlongLi | init
============================================================================= */

#include "Evaluator.h"
#include <cstdlib>
#include <iostream>

static double simpleEvaluation(const Board& board);

/*
 * 2*(number_of_own_pieces_remaining)
 */
static double defensiveHeuristic(const Board& board, int player);

/*
 * 2*(30 - number_of_opponent_pieces_remaining)
 */
static double offensiveHeuristic(const Board& board, int player);

/*
 * average distance of n workers that far from base
 */
static double distanceFromBase(const Board& board, int n, int player);

/*
 * Evaluator
 */
double Evaluator::randomFloat() {
    return  rand() / (float)RAND_MAX;
}

//////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////
/*
 * Simple Evaluator
 */
double SimpleEvaluator::maxerEvaluation(const Board& board) {
    return simpleEvaluation(board) + randomFloat();
}
double SimpleEvaluator::minerEvaluation(const Board& board) {
    return simpleEvaluation(board) + randomFloat();
}

/*
 * DefensiveHeuristicEvaluator
 */
double DefensiveHeuristicEvaluator::maxerEvaluation(const Board& board) {
    return defensiveHeuristic(board, 1) + randomFloat();
}
double DefensiveHeuristicEvaluator::minerEvaluation(const Board& board) {
    return defensiveHeuristic(board, -1) + randomFloat();
}

/*
 * OffensiveHeuristicEvaluator
 */
double OffensiveHeuristicEvaluator::maxerEvaluation(const Board& board) {
    return offensiveHeuristic(board, 1) + randomFloat();
}
double OffensiveHeuristicEvaluator::minerEvaluation(const Board& board) {
    return offensiveHeuristic(board, -1) + randomFloat();
}

/*
 * DistanceFromBaseEvaluator
 */
DistanceFromBaseEvaluator::DistanceFromBaseEvaluator(int _top): top(_top) {
}
double DistanceFromBaseEvaluator::maxerEvaluation(const Board& board) {
    return distanceFromBase(board, top, 1) + randomFloat();
}
double DistanceFromBaseEvaluator::minerEvaluation(const Board& board) {
    return distanceFromBase(board, top, -1) + randomFloat();
}

//////////////////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////////////////
/*
 * help functions
 */
static double simpleEvaluation(const Board& board) {
    int sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += board.getValue(i, j);
    return sum;
}

static double defensiveHeuristic(const Board& board, int player) {
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

static double offensiveHeuristic(const Board& board, int player) {
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

static double distanceFromBase(const Board& board, int n, int player) {
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
