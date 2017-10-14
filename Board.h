/* =============================================================================
#     FileName: Board.h
#         Desc: Breakthrough board
#       Author: YanlongLi
#        Email: lansunlong@gmail.com
#     HomePage: http://www.yanlongli.me
#      Created: 2017-10-14 00:34:42
#      Version: 0.0.1
#   LastChange: 2017-10-14 00:34:42
#      History:
#               0.0.1 | YanlongLi | init
============================================================================= */

#ifndef BOARD_H
#define BOARD_H

#define N 8

class Board {
    int **board;
  public:
    Board();
    Board(const Board& board);
    void operator= (const Board& board);
    ~Board();
    int getValue(int i, int j) const;
    void setValue(int i, int j, int val);
};

#endif /* ifndef BOARD_H */
