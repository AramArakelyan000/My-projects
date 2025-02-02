#ifndef PAWN_HPP
#define PAWN_HPP
#include "chess.hpp"

class Pawn : public Piece {
public:
   Pawn(char color);
    bool permissibleMove(int x, int y) const override;
    char getSymbol() const override;
};

#endif
