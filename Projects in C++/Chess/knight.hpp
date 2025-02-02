#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include "chess.hpp"

class Knight : public Piece {
public:
   Knight(char color);
    bool permissibleMove(int x, int y) const override;
    char getSymbol() const override;
};
#endif
