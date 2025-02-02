#include <iostream>
#include "chess.hpp"


Piece::Piece() {
    color = 'W';
    x = 0;
    y = 0;
}

Piece::Piece(char color) {
    this -> color = color;
    x = 0;
    y = 0;
}

char Piece::getColor() const {
    return color;
}

bool Piece::setColor(char color) {
    if (color == 'W' || color == 'B') {
        this->color = color;
        return true;
    } 
}

void Piece::setMove(int x, int y) {
    this->x = x;
    this->y = y;
}


