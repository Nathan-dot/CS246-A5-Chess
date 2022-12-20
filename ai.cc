#include "ai.h"
#include "board.h"
#include "position.h"
#include "cell.h"
#include "piece.h"
#include "move.h"

std::vector<Move> legalMove(Board& board, Piece* p) {
	std::vector<Move> vec;
 	Position posn = p->getPosition();
 	if (posn.compare(Position(-1, -1))) {
		return vec;
	}
 	for (int r = 0; r < 8; r++) {
  		for (int c = 0; c < 8; c++) {
   			Position pos(r, c);
   			if (p->move(pos) != MoveType::Illegal) {
    				Move curr;
    				curr.movingPiece = p;
   				curr.initialPos = posn;
   				curr.finalPos = pos;
    				vec.push_back(curr);
   			}
  		}
 	}
 	return vec;
}

int calculate(Board& board, Colour colour) {
	int total1 = 0;
	int total2 = 0;
	for (int i = 1; i < 16; ++i) {
		if (board.whitePieces[i]->getPosition().row >= 0) {
			total1 += board.whitePieces[i]->getVal();
		}
		if (board.blackPieces[i]->getPosition().row >= 0) {
			total2 += board.blackPieces[i]->getVal();
		}
	}
	if (colour == Colour::White) {
		return total1 - total2;
	} 
	return total2 - total1;
}


