#ifndef BISHOP_HPP
#define BISHOP_HPP
#include "chess.hpp"

class Bishop : public Piece {
public:
   Bishop(char color);
    bool permissibleMove(int x, int y) const override;
    char getSymbol() const override;
};
#endif
