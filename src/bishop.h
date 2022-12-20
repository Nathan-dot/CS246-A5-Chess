#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
#include "colour.h"
#include "board.h"
#include "movetype.h"

class Bishop : public Piece {
public:
	Bishop(Board* board, char pieceName, Colour owner);
	int getVal() override;
	MoveType touchable(const Position position) override;		

};

#endif
