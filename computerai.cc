#include "board.h"
#include "player.h"
#include "ai.h"
#include "colour.h"
#include <vector>
#include <cstdlib>
#include <time.h>



ComputerAi::ComputerAi (Board* board, Colour colour, int level) : Player(board, colour), level(level) {
	board->setAiPieces(*this);
	srand(time(nullptr));
}


void ComputerAi::setAiPieces(Piece* whitePieces[], Piece* blackPieces[]) {
	for (int i = 0; i < 16; ++i) {
		if (colour == Colour::White) {
			computer[i] = whitePieces[i];
			enemy[i] = blackPieces[i];	
		} else {
			computer[i] = blackPieces[i];
                        enemy[i] = whitePieces[i];
		}
	}
}

Move ComputerAi::generateRandom() {
	int i = rand() % legalMoves.size();
       return legalMoves[i];	
}

Move ComputerAi::generateRandom(std::vector<Move> moves) {
	int i = rand() % moves.size();
	return moves[i];
}

std::vector<Move> ComputerAi::generateLegalMoves() {
	std::vector<Move> possibleMoves;
	for (int i = 0; i < 16; ++i) {
		std::vector<Move> pieceMoves = legalMove(*board, computer[i]);
		for (auto it = pieceMoves.begin(); it != pieceMoves.end(); ++it) {
			possibleMoves.push_back(*it);
		}
	}
	return possibleMoves;
}

std::vector<Move> ComputerAi::generateCaptures() {
	std::vector<Move> moves;
	for (auto it = legalMoves.begin(); it != legalMoves.end(); ++it) {
		int x = calculate(*board, colour);
		board->move(it->initialPos, it->finalPos, false, true);
		int y = calculate(*board, colour);
		if (y > x) {
			moves.push_back(*it);
		}
		board->undo(false);
	}
	return moves;
}

std::vector<Move> ComputerAi::generateChecks() {
	std::vector<Move> moves;
	std::vector<Move> checkmates;
	for (auto it = legalMoves.begin(); it != legalMoves.end(); ++it) {
		GameState result = board->move(it->initialPos, it->finalPos, false, true);
		if (result == GameState::Checkmate) {
			checkmates.push_back(*it);
			break;
		} else if (result == GameState::Check) {
			moves.push_back(*it);
		}
		board->undo(false);
	}
	if (checkmates.size() > 0) {
		return checkmates;
	} 
	return moves;
}


GameState ComputerAi::getState() {
	Move nextMove;
	legalMoves = generateLegalMoves();
	if (legalMoves.empty()) {
		return GameState::Error;	
	} 
	if (level == 1) {
		nextMove = generateRandom();	
	}
	if (level == 2) {
		std::vector<Move> checks = generateChecks();
		if (!checks.empty()) {
			nextMove = generateRandom(checks);
		} else {
			checks = generateCaptures();
			if (!checks.empty()) {
				nextMove = generateRandom(checks);
			} else {
				nextMove = generateRandom();
			}
		}
	}
	GameState result = board->move(nextMove.initialPos, nextMove.finalPos, true, true);
	if (result == GameState::Draw) {
		return GameState::Error;
	} else if (result == GameState::Checkmate) {
		return GameState::Checkmate;
	} else {
		if (result == GameState::Check) {
			if (colour == Colour::White) {
				std::cout << "White puts Black in check." << std::endl;
			} else {
				std::cout<< "Black puts White in check." << std::endl;
			}
		} else {
			return GameState::NoEnd;
		}
	}
	return GameState::Error;
}


