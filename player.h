#ifndef PLAYER_H
#define PLAYER_H
#include "colour.h"
#include "position.h"
#include "gamestate.h"

class Board;

class Player {
protected:
	Board* board;
	Colour colour;
public:
	Player(Board* board, Colour colour);
	virtual GameState getState() = 0; // will return gamestate of the current game
      	virtual ~Player();	
};



#endif
