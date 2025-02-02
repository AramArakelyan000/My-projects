#include "board.hpp"
#include <iostream>

Board::Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
}

Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete board[i][j];
        }
    }
}

Piece* Board::getPiece(int x, int y) const {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        return board[x][y];
    }
    return nullptr;
}

void Board::setPiece(int x, int y, Piece* piece) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        board[x][y] = piece;
        if (piece) {
            piece->setMove(x, y);
        }
    }
}

void Board::movePiece(int startX, int startY, int endX, int endY, bool pawn) {
    if (startX >= 0 && startX < 8 && startY >= 0 && startY < 8 && endX >= 0 && endX < 8 && endY >= 0 && endY < 8) {
        Piece* piece = board[startX][startY];
        if (piece && piece->permissibleMove(endX, endY) && !pawn) {
            board[endX][endY] = piece;
            board[startX][startY] = nullptr;
            piece->setMove(endX, endY);
        }
        if (pawn) {
            board[endX][endY] = piece;
            board[startX][startY] = nullptr;
            piece->setMove(endX, endY);
        }
    }
}

void Board::display() const {
    std::cout << "   a b c d e f g h\n -------------------" << std::endl;
    for (int y = 7; y >= 0; --y) {
        std::cout << ' ' << y + 1 << "|";
        for (int x = 0; x < 8; ++x) {
            if (board[x][y]) {
                std::cout << board[x][y]->getSymbol() << ' ';
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "|" << y + 1 << std::endl;;
    }
    std::cout << " -------------------\n   a b c d e f g h" << std::endl;
}