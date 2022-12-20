#include "piece.h"
#include "board.h"
#include "colour.h"
#include "position.h"

Piece::Piece(Board* board, char pieceName, Colour owner) : board(board), pieceName(pieceName), owner(owner), posn(Position(-1, -1)) {}


Colour Piece::getOwner() {
	return owner;
}
        
MoveType Piece::move(Position position) {
	if (board->hasOccupancy(position, owner) == Colour::Black && owner == Colour::Black) {
		return MoveType::Illegal;
	} else if (board->hasOccupancy(position, owner) == Colour::White && owner == Colour::White) {
		return MoveType::Illegal;
	} else if (board->causeVulnerable(posn, position, owner)) {
		return MoveType::Illegal;
	} else {
		return touchable(position); 
	}
}
        
Position Piece::getPosition() {
	return posn;
}
        
char Piece::getPieceName() {
	return pieceName;
}

void Piece::update(const Position position, std::vector<Piece*> whiteTouchable, std::vector<Piece*> blackTouchable) {
	posn = position;
	if (owner == Colour::White) {
		checks = blackTouchable;
		defenders = whiteTouchable;
	} else if (owner == Colour::Black) {
		checks = whiteTouchable;
		defenders = blackTouchable;
	}
	checked = checks.empty() ? false : true;
	isProtected = defenders.empty() ? false : true;
}

std::vector<Piece*> Piece::getChecks() {
	return checks;
}

Piece::~Piece() {}

std::vector<Piece*> Piece::getDefenders() {
	return defenders;
}
        
bool Piece::getProtected() {
	return isProtected;
}
        
bool Piece::getChecked() {
	return checked;
}
