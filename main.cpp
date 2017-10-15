#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Board.h"
#include "Agent.h"
#include "MinimaxAgent.h"
#include "RandomAgent.h"
#include "utils.h"

static bool checkFinish(const Board& board) {
    int status = Agent::checkWinOrLoss(board);
    if (status == 0) return false;
    else if (status == 1) {
        cout << "Maxer Win" << endl;
    } else if (status == -1) {
        cout << "Miner Win" << endl;
    }
    return true;
}


bool interactive = false;

int main(int argc, char *argv[]) {
    //
    srand(time(0));
    //
    Board board;
    initializeBoard(board);
    printBoard(board);
    //
    RandomAgent agent = RandomAgent();
    MinimaxAgent myAgent = MinimaxAgent(100, true);
    int round = 0;
    while (true) {
        ++round;

        system("clear");
        cout << "Maxer: (" << round <<  ")" << endl;
        board = myAgent.nextByMaxer(board);
        printBoard(board);
        if (checkFinish(board)) break;
        if (interactive) getchar();

        system("clear");
        cout << "Miner: (" << round <<  ")" << endl;
        board = agent.nextByMiner(board);
        printBoard(board);
        if (checkFinish(board)) break;
        if (interactive) getchar();
    }
    return 0;
}
