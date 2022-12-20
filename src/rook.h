#ifndef ROOK_H
#define ROOK_H
#include "piece.h"
#include "colour.h"
#include "movetype.h"

class Board;

class Rook : public Piece {

public:
	Rook(Board* board, char pieceName, Colour owner);
	int getVal() override;
        MoveType touchable(const Position position) override;

};





#endif
