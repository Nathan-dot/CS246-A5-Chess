#ifndef COMPUTERAI_H
#define COMPUTERAI_H
#include <vector>
#include "player.h"
#include "colour.h"
#include "move.h"


class ComputerAi : public Player {
	int level;
	Piece* computer[16];
	Piece* enemy[16];
	std::vector<Move> legalMoves;

public:
	ComputerAi(Board* board, Colour colour, int level);
	void setAiPieces(Piece* whitePieces[], Piece* blackPieces[]);
	Move generateRandom();
        Move generateRandom(std::vector<Move> moves);
	std::vector<Move> generateCaptures();
	std::vector<Move> generateLegalMoves();
	std::vector<Move> generateChecks();
	GameState getState();
	void setLevel(int level);
};




#endif
