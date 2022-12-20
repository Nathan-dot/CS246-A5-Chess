#ifndef PIECE_H
#define PIECE_H
#include "position.h"
#include "colour.h"
#include "gamestate.h"
#include "movetype.h"
#include <vector>

// enum class MoveType {Illegal, Legal, Castling, Promotion, EnPassant};

class Board;

class Piece {
protected:
	Board* board;
	char pieceName;
	Colour owner;
	Position posn;
	std::vector<Piece*> checks;
	std::vector<Piece*> defenders;
	bool checked;
	bool isProtected;
public:
	Piece(Board* board, char pieceName, Colour owner);
	Colour getOwner();
	MoveType move(Position position);
	Position getPosition();
	virtual int getVal() = 0;
	virtual char getPieceName();
	std::vector<Piece*> getChecks();
	std::vector<Piece*> getDefenders();
	bool getProtected();
	bool getChecked();
	virtual ~Piece();
	virtual MoveType touchable(const Position position) = 0;
	virtual void update(const Position position, std::vector<Piece*> whiteTouchable, std::vector<Piece*> blackTouchable);
};

#endif
