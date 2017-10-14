/* =============================================================================
#     FileName: Agent.h
#         Desc: Breakthrough Agent
#       Author: YanlongLi
#        Email: lansunlong@gmail.com
#     HomePage: http://www.yanlongli.me
#      Created: 2017-10-14 00:10:45
#      Version: 0.0.1
#   LastChange: 2017-10-14 00:10:45
#      History:
#               0.0.1 | YanlongLi | init
============================================================================= */
#ifndef AGENT_H

#include <vector>
#include <iostream>
#include "Board.h"

using namespace std;

class Action {
    Board board;
    int fx, fy;
    int tx, ty;
  public:
    bool isDefensive;
    Action(const Board& _board): board(_board) {
    }
    void set(int _fx, int _fy, int _tx, int _ty);
    Board result();
};

class Agent {
  protected:
    vector<Action> validActionByMaxer(const Board& board);
    vector<Action> validActionByMiner(const Board& board);
  public:
    virtual Board nextByMaxer(const Board& board) = 0;
    virtual Board nextByMiner(const Board& board) = 0;
    /*
     * -1: win by Miner
     *  1: win by Maxer
     *  0: tie, not final status
     */
    static int checkWinOrLoss(const Board& board);
};


#define AGENT_H
#endif /* ifndef AGENT_H */
