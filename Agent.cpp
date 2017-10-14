/* =============================================================================
#     FileName: Agent.cpp
#         Desc: Breakthrough Agent
#       Author: YanlongLi
#        Email: lansunlong@gmail.com
#     HomePage: http://www.yanlongli.me
#      Created: 2017-10-14 00:10:15
#      Version: 0.0.1
#   LastChange: 2017-10-14 00:10:15
#      History:
#               0.0.1 | YanlongLi | init
============================================================================= */

#include "Agent.h"
#include "Board.h"
#include "utils.h"

/*
 * Action
 */
void Action::set(int _fx, int _fy, int _tx, int _ty) {
    fx = _fx;
    fy = _fy;
    tx = _tx;
    ty = _ty;
}

Board Action::result() {
    int v = board.getValue(fx, fy);
    if ( v == 0 ) fprintf(stderr, "not a valid step from: (%d,%d)\n", fx, fy);
    Board result = board;
    result.setValue(tx, ty, v);
    result.setValue(fx, fy, 0);
    return result;
}

/*
 * Agent
 */

int Agent::checkWinOrLoss(const Board& board) {
    for (int i = 0; i < N; i++)
        if (board.getValue(0, i) == -1) return -1;
    for (int i = 0; i < N; i++)
        if (board.getValue(N - 1, i) == 1) return 1;
    bool hasOne = false, hasMinusOne = false;
    int v;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            v = board.getValue(i, j);
            if (v == 1) hasOne = true;
            else if (v == -1) hasMinusOne = true;
        }
        if (hasOne && hasMinusOne) break;
    }
    if (!hasOne) return -1;
    if (!hasMinusOne) return 1;
    return 0;
}

vector<Action> Agent::validActionByMaxer(const Board& board) {
    vector<Action> actions;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board.getValue(i, j) == 1 && i + 1 < N) {
                if (j - 1 >= 0 && board.getValue(i + 1, j - 1) != 1) {
                    Action action = Action(board);
                    action.set(i, j, i + 1, j - 1);
                    actions.push_back(action);
                }
                if (board.getValue(i + 1, j) == 0) {
                    Action action = Action(board);
                    action.set(i, j, i + 1, j);
                    actions.push_back(action);
                }
                if (j + 1 < N && board.getValue(i + 1, j + 1) != 1) {
                    Action action = Action(board);
                    action.set(i, j, i + 1, j + 1);
                    actions.push_back(action);
                }
            }
        }
    }
    return actions;
}

vector<Action> Agent::validActionByMiner(const Board& board) {
    vector<Action> actions;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board.getValue(i, j) == -1 && i - 1 >= 0) {
                if (j - 1 >= 0 && board.getValue(i - 1, j - 1) != -1) {
                    Action action = Action(board);
                    action.set(i, j, i - 1, j - 1);
                    actions.push_back(action);
                }
                if (board.getValue(i - 1, j) == 0) {
                    Action action = Action(board);
                    action.set(i, j, i - 1, j);
                    actions.push_back(action);
                }
                if (j + 1 < N && board.getValue(i - 1, j + 1) != -1) {
                    Action action = Action(board);
                    action.set(i, j, i - 1, j + 1);
                    actions.push_back(action);
                }
            }
        }
    }
    return actions;
}
