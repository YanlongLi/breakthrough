#include "Board.h"
#include <cstring>
#include <iostream>

using namespace std;

Board::Board() {
    board = new int*[N];
    for (int i = 0; i < N; i++) {
        board[i] = new int[N];
        for (int j = 0; j < N; j++) board[i][j] = 0;
    }
    // memset(board, 0, sizeof(int) * N * N);
}

Board::Board(const Board& _board) {
    board = new int*[N];
    for (int i = 0; i < N; i++) {
        board[i] = new int[N];
        for (int j = 0; j < N; j++)
            board[i][j] = _board.getValue(i, j);
    }
    // memcpy(this->board, _board.board, sizeof(int) * N * N);
}

void Board::operator=(const Board& _board) {
    // memcpy(this->board, _board.board, sizeof(int) * N * N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = _board.getValue(i, j);
}

Board::~Board() {
    for (int i = 0; i < N; i++) {
        delete [] board[i];
    }
    delete board;
}

int Board::getValue(int i, int j) const {
    if ( i < 0 || i >= N ) fprintf(stderr, "%s: %d\n", "row index out of bound:", i);
    if ( j < 0 || j >= N ) fprintf(stderr, "%s: %d\n", "col index out of bound:", j);
    return board[i][j];
}

void Board::setValue(int i, int j, int val) {
    if ( i < 0 || i >= N ) fprintf(stderr, "%s: %d\n", "row index out of bound:", i);
    if ( j < 0 || j >= N ) fprintf(stderr, "%s: %d\n", "col index out of bound:", j);
    if ( val < -1 || val > 1) fprintf(stderr, "%s: %d\n", "invalid val", val);
    board[i][j] = val;
}
