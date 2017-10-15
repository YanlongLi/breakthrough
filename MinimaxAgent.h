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
#include <map>

class MinimaxAgent : public Agent {
    long long MAX_DEPTH;
    bool alphaBetaPrune;

    long long depth;
    double alpha, beta;

    double simpleUtility(const Board& board);
    double defensiveHeuristic(const Board& board, int player);
    double offensiveHeuristic(const Board& board, int player);
    double distanceFromBase(const Board& board, int n, int player);
  protected:
    double maxerUtility(const Board& board);
    double minerUtility(const Board& board);
    double maxValue(const Board& board);
    double minValue(const Board& board);
  public:
    MinimaxAgent(long long maxdepth, bool alphaBetaPrune);
    virtual Board nextByMaxer(const Board& board);
    virtual Board nextByMiner(const Board& board);
};

#endif /* ifndef MYAGENT_H */
