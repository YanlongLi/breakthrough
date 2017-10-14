/* =============================================================================
#     FileName: RandomAgent.cpp
#         Desc: Random Agent
#       Author: YanlongLi
#        Email: lansunlong@gmail.com
#     HomePage: http://www.yanlongli.me
#      Created: 2017-10-14 03:58:52
#      Version: 0.0.1
#   LastChange: 2017-10-14 03:58:52
#      History:
#               0.0.1 | YanlongLi | init
============================================================================= */

#include "RandomAgent.h"
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

Board RandomAgent::nextByMaxer(const Board& board) {
    vector<Action> actions = validActionByMaxer(board);
    int index = rand() % actions.size();
    return actions[index].result();
}
Board RandomAgent::nextByMiner(const Board& board) {
    vector<Action> actions = validActionByMiner(board);
    int index = rand() % actions.size();
    return actions[index].result();
}
