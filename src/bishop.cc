#include "position.h"
#include "bishop.h"
#include "piece.h"
#include <cstdlib>

class Board;

Bishop::Bishop(Board* board, char pieceName, Colour owner) : Piece(board, pieceName, owner) {}

int Bishop::getVal() {
	return 3;
}

MoveType Bishop::touchable(const Position position) {
	int xDist = position.row - posn.row; // from Piece superclass
	int yDist = position.col - posn.col;
	Position checkOccupancy(0, 0);
	if (std::abs(xDist) != std::abs(yDist)) {
		return MoveType::Illegal;
	}
	for (int i = 1; i < abs(xDist); ++i) {
		checkOccupancy.row = posn.row + i * ((xDist) / (std::abs(xDist)));
	        checkOccupancy.col = posn.col + i * ((yDist) / (std::abs(yDist)));
		if (board->hasOccupancy(checkOccupancy, owner) != Colour::NoColour) {
			return MoveType::Illegal;
		}	
	}
	return MoveType::Legal;

}

