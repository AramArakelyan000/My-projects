#ifndef QUEEN_HPP
#define QUEEN_HPP
#include "chess.hpp"

class Queen : public Piece {
public:
    Queen(char color);
    bool permissibleMove(int x, int y) const override;
    char getSymbol() const override;
};

#endif