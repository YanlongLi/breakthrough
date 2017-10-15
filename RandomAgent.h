/* =============================================================================
#     FileName: InputAgent.h
#         Desc: Input Agent
#       Author: YanlongLi
#        Email: lansunlong@gmail.com
#     HomePage: http://www.yanlongli.me
#      Created: 2017-10-14 03:58:35
#      Version: 0.0.1
#   LastChange: 2017-10-14 03:58:35
#      History:
#               0.0.1 | YanlongLi | init
============================================================================= */

#ifndef RANDOMAGENT_H
#define RANDOMAGENT_H
#endif /* ifndef RANDOMAGENT_H */

#include "Agent.h"
#include "Board.h"

class RandomAgent: public Agent {
  public:
    RandomAgent() {}
    virtual ~RandomAgent() { }
    virtual Board nextByMaxer(const Board& board);
    virtual Board nextByMiner(const Board& board);
};
