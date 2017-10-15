#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <vector>
#include "Board.h"
#include "Agent.h"
#include "MinimaxAgent.h"
#include "Evaluator.h"
#include "RandomAgent.h"
#include "utils.h"

bool interactive = false;

int runMatch(Agent& agent1, Agent& agent2) {
    Board board;
    initializeBoard(board);
    printBoard(board);
    //
    int round = 0, finish = 0;
    while (true) {
        ++round;

        if (interactive) getchar();
        // else this_thread::sleep_for(chrono::milliseconds(500));
        system("clear");
        board = agent1.nextByMaxer(board);
        printBoard(board);
        finish = Agent::checkWinOrLoss(board);
        if (finish != 0) return finish;
        cout << "Maxer: (" << round <<  ")" << endl;

        if (interactive) getchar();
        // else this_thread::sleep_for(chrono::milliseconds(500));
        system("clear");
        board = agent2.nextByMiner(board);
        printBoard(board);
        finish = Agent::checkWinOrLoss(board);
        if (finish != 0) return finish;
        cout << "Miner: (" << round <<  ")" << endl;
    }
}

int main(int argc, char *argv[]) {
    //
    srand(time(0));
    //
    SimpleEvaluator evaluator;
    OffensiveHeuristicEvaluator offeEval;
    //
    // RandomAgent randomAgent = RandomAgent();
    MinimaxAgent minimaxAgent = MinimaxAgent(100, true, &evaluator);
    MinimaxAgent minimaxAgent2 = MinimaxAgent(100, true, &offeEval);
    Agent& agent1 = minimaxAgent;
    Agent& agent2 = minimaxAgent2;
    int status = runMatch(agent1, agent2);
    if (status == 1) {
        cout << "Maxer Win" << endl;
    } else if (status == -1) {
        cout << "Miner Win" << endl;
    } else {
        fprintf(stderr, "Error return status, %d\n", status);
    }
    return 0;
}
