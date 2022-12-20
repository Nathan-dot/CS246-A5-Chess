#include "player.h"
#include "humanplayer.h"
#include "game.h"
#include "board.h"
#include "position.h"
#include "colour.h"
#include "gamestate.h"
#include "computerai.h"
#include <sstream>
#include <string>
#include <iostream>

Game::Game() : board{new Board()}, white{nullptr}, black{nullptr}, wasSetup(false) {}

Game::~Game() {
	delete board;
	delete white;
	delete black;
}

void Game::setPlayer(Colour colour, int playerLevel) {
	if (playerLevel == 5) {
		if (colour == Colour::White) {
			white = new HumanPlayer(board, colour);
		} else {
			black = new HumanPlayer(board, colour);
		}
	} else {
		if (colour == Colour::White) {
			white = new ComputerAi(board, colour, playerLevel); 
		} else {
			black = new ComputerAi(board, colour, playerLevel);
		}
	}
}

void Game::startGame(int whitePlayerLevel, int blackPlayerLevel) {
	Colour whiteTurn = board->whoseTurn();
	Player* current = nullptr;
	GameState gameResult;
	setPlayer(Colour::White, whitePlayerLevel);
	setPlayer(Colour::Black, blackPlayerLevel);
	if (!wasSetup) {
		// print board
		board->startgame();
	} else {
		std::cout << *board;
	}
	while (true) { // control loop for playing the actual game
		if (whiteTurn == Colour::White) {
			current = white;
		} else {
			current = black;
		}
		try {
			gameResult = current->getState(); // gets gamestate i.e. checkmate, stalemate
		} catch (std::string &input) {
			std::cerr << input << std::endl;
			declareWinner(Colour::NoColour);
			break;
		}
		if (gameResult == GameState::Draw) {
			declareWinner(Colour::NoColour, false);
			break;	
		} else if (gameResult == GameState::NoEnd) {
			if (whiteTurn == Colour::White) {
				whiteTurn = Colour::Black;
			} else {
				whiteTurn = Colour::White;
			}
		} else if (gameResult == GameState::Resign) {
			if (whiteTurn == Colour::White) {
				declareWinner(Colour::Black, false);
			} else {
				declareWinner(Colour::White, false);
			}
			break;
		} else if (gameResult == GameState::Checkmate) {
			(whiteTurn == Colour::White) ? declareWinner(Colour::White, true) : declareWinner(Colour::Black, true);
			break;
		} else if (gameResult == GameState::History) {
			board->printHistory(whiteTurn);	
		} else if (gameResult == GameState::Error) {
			declareWinner(Colour::NoColour);
			break;
		}
	}

}

void Game::setup() {
	board->setup();
	wasSetup = true;
}

void Game::declareWinner(Colour colour, bool checkmate) {
	if (colour == Colour::White) {
		std::cout << "White wins";
		if (checkmate) { // should represent checkmate
			std::cout << " through checkmate." << std::endl;	
		} else {
			std::cout << " through resignation." << std::endl;
		}
		++whiteWins;
	} else if (colour == Colour::Black) {
		std::cout << "Black wins";
		if (checkmate) {
			std::cout << " through checkmate." << std::endl;
		} else {
			std::cout << " through resignation." << std::endl;
		}
		++blackWins;
	} else {
		std::cout << "Draw" << std::endl;
	}
	std::cout << "ScoreBoard:" << std::endl;
	std::cout << "White: " << whiteWins << " .vs. " << "Black: " << blackWins << std::endl;
	delete board;
	delete white;
	delete black;
	board = new Board();
	white = nullptr;
	black = nullptr;
	wasSetup = false;
}

