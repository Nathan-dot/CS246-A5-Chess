#include "rook.h"
#include "position.h"
#include "board.h"
#include <cstdlib>

Rook::Rook(Board* board, char pieceName, Colour owner) : Piece(board, pieceName, owner) {}
        
int Rook::getVal() {
	return 5;
}


MoveType Rook::touchable(const Position position) {
	int xDist = position.row - posn.row;
	int yDist = position.col - posn.col;
	int xScaleFactor = 0;
	int yScaleFactor = 0;
	Position checkOccupancy(posn.row, posn.col);
	if (!((xDist == 0 && yDist != 0) || (xDist != 0 && yDist == 0))) {
		return MoveType::Illegal;
	} else if ((xDist > 0) && (yDist == 0)) {
		xScaleFactor = 1;
	} else if ((xDist < 0) && (yDist == 0)) {
		xScaleFactor = -1;
	} else if ((xDist == 0) && (yDist > 0)) {
		yScaleFactor = 1;
	} else if ((xDist == 0) && (yDist < 0)) {
		yScaleFactor = -1;
	}
	if (xScaleFactor == 0) {
		for (int i = 1; i < std::abs(yDist); ++i) {
			checkOccupancy.col += yScaleFactor;
			if (board->hasOccupancy(checkOccupancy, owner) != Colour::NoColour) {
				return MoveType::Illegal;
			}
		}
	} else {
		for (int i = 1; i < std::abs(xDist); ++i) {
			checkOccupancy.row += xScaleFactor;
			if (board->hasOccupancy(checkOccupancy, owner) != Colour::NoColour) {
				return MoveType::Illegal;
			}
		}
	}
	return MoveType::Legal;
}
