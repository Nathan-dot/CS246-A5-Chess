#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include "colour.h"
#include "gamestate.h"
#include <string>

class Board;

class HumanPlayer : public Player {
public:
	HumanPlayer(Board* board, Colour colour); 
	GameState getState();
	GameState interpretInput(std::string input);
};






#endif
