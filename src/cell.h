#ifndef CELL_H
#define CELL_H
#include "position.h"
#include <vector>

class Piece;

class Cell {
	Position posn;
	Piece* currPiece;
	std::vector<Piece*> whiteTouchable;
	std::vector<Piece*> blackTouchable;
public:
	Cell(Position posn);
	Piece* getcurrPiece();
	void getPosition(); // delete later for testing only
	std::vector<Piece*> getwhiteTouchable();
        std::vector<Piece*> getblackTouchable();
	void setPiece(Piece* currPiece);
	Piece* remove();
	void update(std::vector<Piece*> whiteTouchable, std::vector<Piece*> blackTouchable);
	
};
#endif
