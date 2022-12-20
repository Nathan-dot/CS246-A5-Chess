#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
#include "colour.h"
#include "movetype.h"

class Board;

class Knight : public Piece {
public:
	Knight(Board* board, char pieceName, Colour owner);
	int getVal() override;
        MoveType touchable(const Position position) override;	
};




#endif
