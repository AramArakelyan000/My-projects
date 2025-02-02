#include "chess.hpp"
#include "game.hpp"

void initBoard(Board &board) {
    
    board.setPiece(0, 0, new Rook('W'));
    board.setPiece(1, 0, new Knight('W'));
    board.setPiece(2, 0, new Bishop('W'));
    board.setPiece(3, 0, new Queen('W'));
    board.setPiece(4, 0, new King('W'));
    board.setPiece(5, 0, new Bishop('W'));
    board.setPiece(6, 0, new Knight('W'));
    board.setPiece(7, 0, new Rook('W'));
    for (int i = 0; i < 8; ++i) {
        board.setPiece(i, 1, new Pawn('W'));
    }

    board.setPiece(0, 7, new Rook('B'));
    board.setPiece(1, 7, new Knight('B'));
    board.setPiece(2, 7, new Bishop('B'));
    board.setPiece(3, 7, new Queen('B'));
    board.setPiece(4, 7, new King('B'));
    board.setPiece(5, 7, new Bishop('B'));
    board.setPiece(6, 7, new Knight('B'));
    board.setPiece(7, 7, new Rook('B'));
    for (int i = 0; i < 8; ++i) {
        board.setPiece(i, 6, new Pawn('B'));
    }
}

bool findWhiteKing(Board *board){
    for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board->getPiece(i, j);
                if (piece != nullptr) {
                    if (piece->getSymbol() == 'K') {
                        return true;
                    }        
                }
            }
        }
    return false;
}
bool findBlackKing(Board *board){
    for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* piece = board->getPiece(i, j);
                if (piece != nullptr) {
                    if (piece->getSymbol() == 'k') {
                        return true;
                    }   
                }
            }
        }
    return false;
}