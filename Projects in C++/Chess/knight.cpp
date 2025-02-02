#include "knight.hpp"
#include <cmath>
#include <iostream>

Knight::Knight(char color) : Piece(color) {}

bool Knight::permissibleMove(int x, int y) const {
    return ((abs(x - this->x) == 2 && abs(y - this->y) == 1) || (abs(x - this->x) == 1 && abs(y - this->y) == 2));
}

char Knight::getSymbol() const {
    return (color == 'W') ? 'N' : 'n';
}