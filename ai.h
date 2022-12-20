#ifndef __AI_H__
#define __AI_H__
#include <vector>
#include "colour.h"

struct Move;
class Position;
class Piece;
class Board;


std::vector<Move> legalMove(Board& board, Piece* piece);

int calculate(Board&, Colour colour);

#endif
