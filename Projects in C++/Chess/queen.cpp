#include "queen.hpp"
#include <cmath>
#include <iostream>

Queen::Queen(char color) : Piece(color) {}

bool Queen::permissibleMove(int x, int y) const {
    return (x == this->x || y == this->y || abs(x - this->x) == abs(y - this->y));
}
char Queen::getSymbol() const {
    return color == 'W' ? 'Q' : 'q';
}