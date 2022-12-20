#ifndef MOVE_H
#define MOVE_H
#include "position.h"

class Piece;

struct Move {
	Piece* movingPiece;
        Piece* capturedPiece;
        Piece* enPassant;
	bool isCastle;
	bool isPromotion;
	Position initialPos;
	Position finalPos;
	char pieceName;
};

#endif
