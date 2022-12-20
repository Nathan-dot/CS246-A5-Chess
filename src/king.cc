#include "position.h"
#include "king.h"
#include "board.h"
#include "piece.h"
#include <vector>
#include <cstdlib>

King::King(Board* board, char pieceName, Colour owner) : Piece(board, pieceName, owner), hasMoved{false} {}

bool King::castleMove(const Position position) {
	if (position.row != posn.row || std::abs(position.col - posn.col) != 2) {
		return false;
	}
	if (position.col > posn.col) {
		// castle king side
		if (owner == Colour::White) {
			if (board->vulnerable(Position(posn.row, 5), Colour::Black)) {
                            	return false;
              		} else if (board->hasOccupancy(Position(posn.row, 6), Colour::White) != Colour::NoColour) {
                                return false;
			}
		} else {
			if (board->vulnerable(Position(posn.row, 5), Colour::White)) {
				return false;
			} else if (board->hasOccupancy(Position(posn.row, 6), Colour::Black) != Colour::NoColour) {
				return false;
			}
		}
	} else {
		// castle queen side
             	if (owner == Colour::White) {
			if (board->vulnerable(Position(posn.row, 3), Colour::Black)) {
				return false;
			} else if (board->hasOccupancy(Position(posn.row, 2), Colour::Black) != Colour::NoColour) {
				return false;
                	}
		} else {
			if (board->vulnerable(Position(posn.row, 3), Colour::White)) {
                                return false;
                        } else if (board->hasOccupancy(Position(posn.row, 2), Colour::White) != Colour::NoColour) {
                                return false;
                        }
		}
	}
	if (!hasMoved && !checked) {
		std::vector<Move>* moveHistory = board->getHistory();
		if (moveHistory->size() == 0) {
			return true;
		} else {
			bool check = true;
			if (position.col > posn.col) {
				if (board->hasOccupancy(Position(posn.row, posn.col + 1), owner) != Colour::NoColour) {
					return false;
				}
				for (auto i = moveHistory->rbegin(); i != moveHistory->rend(); ++i) {
					if (i->initialPos.compare(Position(posn.row, 7)) || 
							i->finalPos.compare(Position(posn.row, 7))) {
						check = false;
					}
				}
				return check;
			} else {
				if (board->hasOccupancy(Position(posn.row, posn.col - 1), owner) != Colour::NoColour || 
						board->hasOccupancy(Position(posn.row, posn.col - 3), owner) != Colour::NoColour) {
					return false;
				}
				for (auto it = moveHistory->rbegin(); it != moveHistory->rend(); ++it) {
					if (it->initialPos.compare(Position(posn.row, 0)) || 
								(it->finalPos.compare(Position(posn.row, 0)))) {
						check = false;
					}
				}
				return check;
			}
		}
	}
	return false;
}

int King::getVal() {
	return 100;
}
        
MoveType King::touchable(const Position position) {
	int xDist = std::abs(position.row - posn.row);
	int yDist = std::abs(position.col - posn.col);
	if (((yDist == 1) || (yDist == 0)) && ((xDist == 1) || 
				(xDist == 0)) && (!((xDist == 0) && (yDist == 0)))) {
			return MoveType::Legal;
	} else {
		if (castleMove(position)) {
			return MoveType::Castling;
		} else {
			return MoveType::Illegal;
		}
	}	
}

void King::update(const Position position, std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces) {
	if (!(posn.compare(Position(-1, -1))) && !(posn.compare(position))) {
		hasMoved = true;
	} else {
		bool res;
		std::vector<Move>* moveHistory = board->getHistory();
		if (moveHistory->size()) {
			for (auto it = moveHistory->rbegin(); it != moveHistory->rend(); ++it) {
				if (it->movingPiece == this) {
					res = true;
					break;
				}
			}
		}
		hasMoved = res;
	}
	posn = position;
	if (owner == Colour::White) {
		checks = blackPieces;
		defenders = whitePieces;
	} else {
		checks = whitePieces;
		defenders = blackPieces;
	}
	checked = checks.empty() ? false : true;
	isProtected = defenders.empty() ? false : true;
}
