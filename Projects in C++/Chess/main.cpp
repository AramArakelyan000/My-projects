#include <iostream>
#include <cstring>
#include "chess.hpp"
#include "game.hpp"

int main() {
    Board board;
    Board &refBoard = board;
    initBoard(refBoard);
    board.display();
    std::cout << std::endl;

    char cord[5];
    while (true) {
  
        if (!(findWhiteKing(&board)) || !(findBlackKing(&board))) {
            std::cout << "Game over" << std::endl;
            break;
        }

        std::cout << "Enter coordinates (e.g., a2a3): " << std::endl;
        std::cin >> cord;
        if (std::strlen(cord) != 4) {
            std::cout << "Invalid input, please enter exactly 4 characters (e.g., a2a3)." << std::endl;
            continue;
        }

        int x1 = cord[0] - 'a';
        int y1 = cord[1] - '1';
        int x2 = cord[2] - 'a';
        int y2 = cord[3] - '1';
        bool pawn = false;
        if ((board.getPiece(x1, y1)->getSymbol()) == 'P' && ((x2 == x1 + 1) || (x2 == x1 - 1)) && (y2 = y1 + 1) && (board.getPiece(x2, y2) != nullptr) && (board.getPiece(x2, y2)->getColor() != board.getPiece(x1, y1)->getColor())) {
            pawn = true;
            delete board.getPiece(x2, y2);
            board.movePiece(x1, y1, x2, y2, pawn);
            board.display();
            continue;
            
        }else if ((board.getPiece(x1, y1)->getSymbol() == 'p') && ((x2 == x1 + 1 || x2 == x1 - 1)) && (y2 == y1 - 1) && (board.getPiece(x2, y2) != nullptr) && (board.getPiece(x2, y2)->getColor() != board.getPiece(x1, y1)->getColor())) {
            pawn = true;
            delete board.getPiece(x2, y2);
            board.movePiece(x1, y1, x2, y2, pawn);
            board.display();
            continue;
        }
        else if ((x1 < 0 || x1 >= 8 || y1 < 0 || y1 >= 8 || x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8) || board.getPiece(x1, y1) == nullptr || !(board.getPiece(x1, y1)->permissibleMove(x2, y2))) {
            std::cout << "Invalid coordinates, try again." << std::endl;
            continue;
        }
        else if (((board.getPiece(x1, y1)->getSymbol() == 'p') || (board.getPiece(x1, y1)->getSymbol() == 'P')) && (board.getPiece(x2, y2) != nullptr) && (( y2 = y1 + 1) || (y2 = y1 - 1))) {
            std::cout << "Invalid coordinates, try again." << std::endl;
            continue;
        }
        else if (board.getPiece(x2, y2) != nullptr) {
            Piece* targetPiece = board.getPiece(x2, y2);
            if (targetPiece->getColor() != board.getPiece(x1, y1)->getColor()) {
                if (board.getPiece(x1, y1)->permissibleMove(x2, y2)) {
                    delete board.getPiece(x2, y2);
                    board.movePiece(x1, y1, x2, y2, pawn);
                }else {
                    std::cout << "Invalid coordinates, try again." << std::endl;
                }
            }else{
                std::cout << "Invalid coordinates, try again." << std::endl;
            }
        }else {
            board.movePiece(x1, y1, x2, y2, pawn);
        }

        board.display();
        std::cout << std::endl;

        
    }

    return 0;
}
