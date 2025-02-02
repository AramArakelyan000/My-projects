#ifndef GAME_HPP
#define GAME_HPP
#include "chess.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "board.hpp"


void initBoard(Board &board); 
bool findWhiteKing(Board *board);
bool findBlackKing(Board *board);
#endif