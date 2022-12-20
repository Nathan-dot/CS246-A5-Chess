#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
#include "colour.h"
#include "movetype.h"

class Pawn : public Piece {
	bool hasMoved;
	//bool isGoingToMove;
	Piece* toPromoted;

public:
	Pawn(Board* board, char pieceName, Colour owner);
	void update(const Position position, std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces);
	int getVal() override;
	MoveType checkEnPassant(const Position position);
	char getPieceName() override;
        MoveType touchable(const Position position);
	void promote(Piece* toPromoted);
	~Pawn();
	void revertPromotion();
};


#endif
