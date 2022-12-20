#ifndef GAME_H
#define GAME_H
#include <string>
#include "board.h"
#include "player.h"
#include "position.h"
#include "gamestate.h"
#include "colour.h"

class Game {
	// need Board class, Player class, 
	Board* board;
	Player* white;
	Player* black;
	int whiteWins = 0;
	int blackWins = 0;
	bool wasSetup = false;
	void declareWinner(Colour colour, bool gameOver = false);
	void setPlayer(Colour colour, int playerLevel);	

public:
	Game();
	~Game();
	void startGame(int whiteplayerLevel, int blackplayerLevel);
	void setup(); 
};


#endif
