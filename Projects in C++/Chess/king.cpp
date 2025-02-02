#include "king.hpp"
#include <iostream>

King::King(char color) : Piece(color) {}

bool King::permissibleMove(int x, int y) const {
    return (abs(x - this->x) <= 1 && abs(y - this->y) <= 1);
}

char King::getSymbol() const {
    return (color == 'W') ? 'K' : 'k';
}