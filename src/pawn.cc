#include "pawn.h"
#include <cstdlib>
#include <vector>
#include "board.h"
#include "colour.h"
#include "movetype.h"

// enum class MoveType {Illegal, Legal, Castling, Promotion, EnPassant};


Pawn::Pawn(Board* board, char pieceName, Colour owner) : Piece(board, pieceName, owner), hasMoved(false), toPromoted(nullptr) {}
        
void Pawn::update(const Position position, std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces) {
	if (!posn.compare(Position(-1, -1)) && !(posn.compare(position))) {
		hasMoved = true;
        } else {
		bool change = false;
		std::vector<Move>* moveHistory = board->getHistory();
		if (moveHistory->size()) {
			for (auto i = moveHistory->rbegin(); i != moveHistory->rend(); ++i) {
				if (i->movingPiece == this) {
					change = true;
					break;
				}
			}	
		}
		hasMoved = change;
	}
	posn = position;
	if (owner == Colour::White) {
		checks = blackPieces;
		defenders = whitePieces;
	} else if (owner == Colour::Black) {
		checks = whitePieces;
		defenders = blackPieces;
	}
	if (checks.size() == 0) {
		checked = false;
	} else {
		checked = true;
	}
	if (defenders.size() == 0) {
		isProtected = false;
	} else {
		isProtected = true;
	}
}

int Pawn::getVal() {
	if (toPromoted == nullptr) {
		return toPromoted->getVal();
	} else {
		return 1;
	}
}
        
char Pawn::getPieceName() {
	if (toPromoted != nullptr) {
		return toPromoted->getPieceName();
	} else {
		return pieceName;
	}
}
        
MoveType Pawn::touchable(const Position position) {
	if (toPromoted == nullptr) {
		if (owner == Colour::White) {
			if (position.col == posn.col) { // moves forward 2 steps
				if ((position.row == posn.row - 2)) {
					if (!hasMoved) {
						if (board->hasOccupancy(Position(posn.row - 1, posn.col), owner) == Colour::NoColour) {
							if (board->hasOccupancy(position, owner) == Colour::NoColour) {
								return MoveType::Legal;
							} else {
								return MoveType::Illegal;
							}
						}
					} else {
						return MoveType::Illegal;
					}
				} else if (position.row == posn.row - 1) { // moving forward 1 step
					if (board->hasOccupancy(position, owner) != Colour::NoColour) {
						return MoveType::Illegal;
					} else {
						if (toPromoted == nullptr && position.row == 0) {
							return MoveType::Promotion;
						} else {
							return MoveType::Legal;
						}
					}
				}
			}
			if (std::abs(position.col - posn.col) == 1) {
				// en passant case
				if (position.row == posn.row - 1) {
					if (board->hasOccupancy(position, owner) != Colour::NoColour) {
						if (toPromoted == nullptr && position.row == 0) {
							return MoveType::Promotion;
						} else {
							return MoveType::Legal;
						}
					} else {
						return checkEnPassant(position);
					}
				} else {
					return MoveType::Illegal;
				}
			}
		} else if (owner == Colour::Black) {
			if (position.col == posn.col) {
                                if ((position.row - 2 == posn.row)) {
					if (board->hasOccupancy(Position(posn.row + 1, position.col), owner) != Colour::NoColour) {
						return MoveType::Illegal;
					}
                                        if (!hasMoved) {
                                        	if (board->hasOccupancy(position, owner) != Colour::NoColour) {
                                                	return MoveType::Illegal;
                                                } else {
                                                	if (toPromoted == nullptr && position.row == 7) {
								return MoveType::Promotion;
							} else {
								return MoveType::Legal;
							}
						}
                                        } else {
                                                return MoveType::Illegal;
                                        }
                                } else if (posn.row == position.row - 1) { // moving forward 1 step
                                        if (board->hasOccupancy(position, owner) != Colour::NoColour) {
                                                return MoveType::Illegal;
                                        } else {
                                                if (toPromoted == nullptr && position.row == 7) {
                                                        return MoveType::Promotion;
                                                } else {
                                                        return MoveType::Legal;
                                                }
                                        }
                                }
                        }
                        if (std::abs(position.col - posn.col) == 1) {
                                // en passant case
                                if (position.row - 1 == posn.row) {
                                        if (board->hasOccupancy(position, owner) != Colour::NoColour) {
                                                if (toPromoted == nullptr && position.row == 7) {
                                                        return MoveType::Promotion;
                                                } else {
                                                        return MoveType::Legal;
                                                }
                                        } else {
                                                return checkEnPassant(position);
                                        }
                                } else {
                                        return MoveType::Illegal;
                                }
                        }  
		}	
	} else {
		return toPromoted->touchable(position);
	}
	return MoveType::Illegal;
}

MoveType Pawn::checkEnPassant(const Position position) {
	// need to check if this pawn just moved twice
	/*if (enPassantAble) {
		return MoveType::EnPassant;
	} else {
		return MoveType::Illegal;
	}*/
	if (toPromoted != nullptr) {
		return MoveType::Illegal;
	}
	Position curr(posn.row, position.col);
	if (board->getHistory()->empty()) {
		return MoveType::Illegal;
	}
	Move current = board->getHistory()->back();
        Position after ((owner == Colour::White) ? 1 : 6, position.col);
	if (after.compare(current.initialPos) && curr.compare(current.finalPos)) {
		if (owner == Colour::White && current.pieceName == 'p') {
			return MoveType::EnPassant;
		} else if (owner == Colour::Black && current.pieceName == 'P') {
			return MoveType::EnPassant;
		}
	}
	return MoveType::Illegal;

}
 
void Pawn::promote(Piece* toPromoted) {
	this->toPromoted = toPromoted;
	if (owner == Colour::White || owner == Colour::Black) {
		toPromoted->update(posn, defenders, checks);
	}
}

Pawn::~Pawn() {
	delete toPromoted;
}

void Pawn::revertPromotion() {
	delete toPromoted;
	toPromoted = nullptr;
}
