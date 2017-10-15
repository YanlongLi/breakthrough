/* =============================================================================
#     FileName: MinimaxAgent.h
#         Desc: MinimaxAgent using Minimax
#       Author: YanlongLi
#        Email: lansunlong@gmail.com
#     HomePage: http://www.yanlongli.me
#      Created: 2017-10-14 01:01:58
#      Version: 0.0.1
#   LastChange: 2017-10-14 01:01:58
#      History:
#               0.0.1 | YanlongLi | init
============================================================================= */

#ifndef MYAGENT_H
#define MYAGENT_H

#include "Agent.h"
#include "Evaluator.h"
#include <map>

class MinimaxAgent : public Agent {
    long long MAX_DEPTH;
    bool alphaBetaPrune;
    Evaluator* evaluator;

    long long depth;
    double alpha, beta;

  protected:
    double maxValue(const Board& board);
    double minValue(const Board& board);
  public:
    MinimaxAgent(long long maxdepth, bool alphaBetaPrune, Evaluator* _evaluator);
    virtual Board nextByMaxer(const Board& board);
    virtual Board nextByMiner(const Board& board);
};

#endif /* ifndef MYAGENT_H */
