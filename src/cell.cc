#include "cell.h"
#include "piece.h"
#include <iostream> // can delete later

Cell::Cell(Position posn) : posn{posn}, currPiece{nullptr} {}

void Cell::getPosition() {
	std::cout << posn.row << " " << posn.col << std::endl;
}

Piece* Cell::getcurrPiece() {
	return currPiece;
}
        
void Cell::setPiece(Piece* piece) {
	remove();
	currPiece = piece;
	if (currPiece) {
		currPiece->update(posn, whiteTouchable, blackTouchable);
	}
}
        
Piece* Cell::remove() {
	Piece* newPiece = currPiece;
	std::vector<Piece*> temp;
	currPiece = nullptr;
	Position a(-1, -1);
	if (newPiece) {
		newPiece->update(a, temp, temp);	
	}
	return newPiece;
}
        
void Cell::update(std::vector<Piece*> white, std::vector<Piece*> black) {
	whiteTouchable = white;
	blackTouchable = black;
	if (currPiece) {
		currPiece->update(posn, whiteTouchable, blackTouchable);
	}
}
        
std::vector<Piece*> Cell::getwhiteTouchable() {
	return whiteTouchable;
}
        
std::vector<Piece*> Cell::getblackTouchable() {
	return blackTouchable;
}

