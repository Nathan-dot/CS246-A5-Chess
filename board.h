#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include "position.h"
#include "textdisplay.h"
#include "colour.h"
#include "move.h"
#include "gamestate.h"
#include "movetype.h"
#include <vector>
#include "computerai.h"
#include "ai.h"

class Piece;
class TextDisplay;
class Cell;

class Board {
	Cell* board[8][8];
	std::vector<Move>* moveHistory;
	TextDisplay* display;
        Colour turn;
        int turnCount;
	void update(); // notify
	bool playerInCheck(Colour player);
	bool gameStalemate(Colour player);
	bool checkmate(Colour player);

public:
	Piece* whitePieces[16];
        Piece* blackPieces[16];
	Board();
	~Board();
	void setup();
	GameState move(const Position initialPos, const Position finalPos, bool showDisplay = true, bool ai = false);
	void startgame();
	std::vector<Move>* getHistory();
	void undo(bool show = true);
	void printHistory(Colour turn);
	Colour hasOccupancy(const Position cell, Colour owner); // need to change return type to Colour if time
	bool causeVulnerable(const Position initialPos, const Position finalPos, Colour owner); 
	// checks if move causes king square to be reachable
	bool vulnerable(const Position initialPos, Colour owner);
	// checks if square is reachable
	void setAiPieces(ComputerAi& ai);
	Colour whoseTurn();
	friend std::ostream& operator<<(std::ostream&, Board&);
};

#endif
