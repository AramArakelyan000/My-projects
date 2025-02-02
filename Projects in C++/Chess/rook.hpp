#ifndef ROOK_HPP
#define ROOK_HPP
#include "chess.hpp"

class Rook : public Piece {
public:
   Rook(char color);
    bool permissibleMove(int x, int y) const override;
    char getSymbol() const override;
};
#endif
