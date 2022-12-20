#include "queen.h"
#include "board.h"
#include "position.h"
#include "colour.h"
#include <cstdlib>

Queen::Queen(Board* board, char pieceName, Colour owner) : Piece(board, pieceName, owner) {}
        
int Queen::getVal() {
	return 9;
}
        
MoveType Queen::touchable(const Position position) {
	int xDist = position.row - posn.row;
	int yDist = position.col - posn.col;
	int xScaleFactor = 0;
	int yScaleFactor = 0;
	Position checkOccupancy(posn.row, posn.col);
	// copy and past from Rook + Bishop
       if ((xDist > 0) && (yDist > 0)) {
	       xScaleFactor = 1;
	       yScaleFactor = 1;
       } else if ((xDist < 0) && (yDist > 0)) {
	       xScaleFactor = -1;
	       yScaleFactor = 1;
       } else if ((xDist > 0) && (yDist < 0)) {
	       xScaleFactor = 1;
	       yScaleFactor = -1;
       } else if ((xDist < 0) && (yDist < 0)) {
               xScaleFactor = -1;
               yScaleFactor = -1;
       } else if ((xDist > 0) && (yDist == 0)) {
	       xScaleFactor = 1;
       } else if ((xDist < 0) && (yDist == 0)) {
	       xScaleFactor = -1;
       } else if ((xDist == 0) && (yDist > 0)) {
	       yScaleFactor = 1;
       } else if ((xDist == 0) && (yDist < 0)) {
       	       yScaleFactor = -1;	
       } else {
       	       return MoveType::Illegal;
       }	       
       if (xScaleFactor != 0 && yScaleFactor != 0) { // Bishop-like move
	       if (std::abs(xDist) != std::abs(yDist)) {
		       return MoveType::Illegal;
	       }
	       for (int i = 1; i < std::abs(xDist); ++i) {
		       checkOccupancy.row += xScaleFactor;
		       checkOccupancy.col += yScaleFactor;
		       if (board->hasOccupancy(checkOccupancy, owner) != Colour::NoColour) {
			       return MoveType::Illegal;
		       }
	       }
       } else if (xScaleFactor != 0) { // Rook moving left, right
	       for (int i = 1; i < std::abs(xDist); ++i) {
		       checkOccupancy.row += xScaleFactor;
		       if (board->hasOccupancy(checkOccupancy, owner) != Colour::NoColour) { 
			       return MoveType::Illegal;
		       }
	       }
       } else { // Rook moving y direction
       	       for (int i = 1; i < std::abs(yDist); ++i) {
		       checkOccupancy.col += yScaleFactor;
		       if (board->hasOccupancy(checkOccupancy, owner) != Colour::NoColour) {
			       return MoveType::Illegal;
		       }
	       } 	
       }
       return MoveType::Legal;
}
