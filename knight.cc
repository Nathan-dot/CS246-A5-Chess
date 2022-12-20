#include "knight.h"
#include "position.h"
#include "board.h"
#include <cstdlib>

Knight::Knight(Board* board, char pieceName, Colour owner) : Piece(board, pieceName, owner) {}

int Knight::getVal() {
	return 3;
}

// check over later
MoveType Knight::touchable(const Position position) {
	int xDist = position.row - posn.row;
	int yDist = position.col - posn.col;
	Position checkOccupancy(position.row, position.col);
	if ((std::abs(xDist) == 2 && std::abs(yDist) == 1) || ((std::abs(xDist) == 1 && std::abs(yDist) == 2))) {
			return MoveType::Legal;
	}
	return MoveType::Illegal;
}
