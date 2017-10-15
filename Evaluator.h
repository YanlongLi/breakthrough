/* =============================================================================
#     FileName: Evaluator.h
#         Desc: Base class for evaluation function
#       Author: YanlongLi
#        Email: lansunlong@gmail.com
#     HomePage: http://www.yanlongli.me
#      Created: 2017-10-14 22:08:36
#      Version: 0.0.1
#   LastChange: 2017-10-14 22:08:36
#      History:
#               0.0.1 | YanlongLi | init
============================================================================= */

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Board.h"

class Evaluator {
  protected:
    /*
     * Generate random float value between [0.0, 1,0)
     */
    double randomFloat();
  public:
    Evaluator() {}
    virtual ~Evaluator() {}
    virtual double maxerEvaluation(const Board& board) = 0;
    virtual double minerEvaluation(const Board& board) = 0;
};

/*
 * Simple evaluator, compute the the difference of work number
 */
class SimpleEvaluator : public Evaluator {
  public:
    virtual ~SimpleEvaluator() {}
    virtual double maxerEvaluation(const Board& board);
    virtual double minerEvaluation(const Board& board);
};

/*
 * 2*(number_of_own_pieces_remaining)
 */
class DefensiveHeuristicEvaluator : public Evaluator {
  public:
    virtual ~DefensiveHeuristicEvaluator() {}
    virtual double maxerEvaluation(const Board& board);
    virtual double minerEvaluation(const Board& board);
};

/*
 * 2*(30 - number_of_opponent_pieces_remaining)
 */
class OffensiveHeuristicEvaluator : public Evaluator {
  public:
    virtual ~OffensiveHeuristicEvaluator() {}
    virtual double maxerEvaluation(const Board& board);
    virtual double minerEvaluation(const Board& board);
};

/*
 * average distance of n workers that far from base
 */
class DistanceFromBaseEvaluator: public Evaluator {
    int top;
  public:
    DistanceFromBaseEvaluator(int _top);
    virtual ~DistanceFromBaseEvaluator() {}
    virtual double maxerEvaluation(const Board& board);
    virtual double minerEvaluation(const Board& board);
};

#endif /* ifndef EVALUATOR_H */
