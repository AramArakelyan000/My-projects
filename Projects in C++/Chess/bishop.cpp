#include "bishop.hpp"
#include <cmath>
#include <iostream>

Bishop::Bishop(char color) : Piece(color) {}

bool Bishop::permissibleMove(int x, int y) const {
    return abs(x - this->x) == abs(y - this->y);
}

char Bishop::getSymbol() const {
    return (color == 'W') ? 'B' : 'b';
}