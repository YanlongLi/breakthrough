
#include "utils.h"
#include "Board.h"
#include <iostream>
using namespace std;

void printBoard(const Board& board) {
    cout << "    ";
    for (int i = 0; i < N; i++) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << i << " | ";
        for (int j = 0; j < N; j++) {
            int v = board.getValue(i, j);
            switch (v) {
            case -1:
                cout << "X ";
                break;
            case 0:
                cout << "_ ";
                break;
            case 1:
                cout << "O ";
                break;
            default:
                fprintf(stderr, "invalid board value: (%d, %d, %d)\n", i, j, board.getValue(i, j));
                exit(-1);
            }
        }
        cout << endl;
    }
    cout << endl;
}

void initializeBoard(Board& board) {
    for (int j = 0; j < N; j++) {
        board.setValue(0, j, 1);
        board.setValue(1, j, 1);
        board.setValue(N - 2, j, -1);
        board.setValue(N - 1, j, -1);
    }
}
