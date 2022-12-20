#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
#include "colour.h"
#include "movetype.h"

class Board;

class Queen : public Piece {

public:
        Queen(Board* board, char pieceName, Colour owner);
        int getVal() override;
        MoveType touchable(const Position position) override;

};


#endif  
