#ifndef KING_H
#define KING_H
#include "colour.h"
#include "movetype.h"
#include "piece.h"

class Board;

class King : public Piece {
	bool hasMoved;
	bool castleMove(const Position position);
public:
	King(Board* board, char pieceName, Colour owner);
        int getVal() override;
        MoveType touchable(const Position position) override;
	// distinguish case where castling
	void update(const Position position, std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces);
};


#endif
