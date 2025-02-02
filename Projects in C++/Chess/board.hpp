#ifndef BOARD_HPP
#define BOARD_HPP
#include "chess.hpp"

class Board {
private:
    Piece* board[8][8];

public:
    Board();
    ~Board();
    Piece* getPiece(int x, int y) const;
    void setPiece(int x, int y, Piece* piece);
    void movePiece(int startX, int startY, int endX, int endY, bool pawn);
    void display() const;
};

#endif
