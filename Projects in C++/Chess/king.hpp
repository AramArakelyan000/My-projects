#ifndef KING_HPP
#define KING_HPP
#include "chess.hpp"

class King : public Piece {
public:
    King(char color);
    bool permissibleMove(int x, int y) const override;
    char getSymbol() const override;
};

#endif