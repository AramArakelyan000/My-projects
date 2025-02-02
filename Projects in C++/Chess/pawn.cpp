#include "pawn.hpp"

Pawn::Pawn(char color) : Piece(color) {}

bool Pawn::permissibleMove(int x, int y) const {
    if (color == 'W') {
        return (y == this->y + 1 && x == this->x);
    }else if (color == 'W') {

    } else {
        return (y == this->y - 1 && x == this->x);
    }
}
char Pawn::getSymbol() const {
    return color == 'W' ? 'P' : 'p';
}