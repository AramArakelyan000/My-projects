#include "rook.hpp"

Rook::Rook(char color) : Piece(color) {}

bool Rook::permissibleMove(int x, int y) const {
    return (x == this->x || y == this->y);
}

char Rook::getSymbol() const {
    return (color == 'W') ? 'R' : 'r';
}