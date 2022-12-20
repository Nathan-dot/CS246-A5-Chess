#include "humanplayer.h"
#include "board.h"
#include <iostream>
#include <string>
#include <sstream>

HumanPlayer::HumanPlayer(Board* board, Colour colour) : Player(board, colour) {}

GameState HumanPlayer::getState() {
	try {
	std::string input;
	while (getline(std::cin, input)) {
		GameState result = interpretInput(input);
		if (result != GameState::Undo) {
			if (result != GameState::Error) {
				if (result == GameState::Draw) {
					return GameState::Error;
				} else {
					return result;
				}
			}
		}
	}
	std::string error = "Game Aborted";
	throw error;
	} catch (std::string &input) {
		throw;
	}
}

GameState HumanPlayer::interpretInput(std::string input) {
	std::istringstream ss(input);
	std::string command1;
        std::string command2;	
	if (ss >> input) {
		if (input == "move") {
			if (ss >> command1 && ss >> command2) {
				Position posn1 = convertRowAndCol(command1);
				Position posn2 = convertRowAndCol(command2);
			 	if (posn1.row != -1 && posn2.row != -1) {
                 			GameState state = board->move(posn1, posn2);
                        		if (state == GameState::Error) {
						std::cout << "Invalid Move" << std::endl;
						return GameState::Error;
					} else if (state == GameState::Draw) {
						return GameState::Draw;
					} else if (state == GameState::NoEnd) {
						return GameState::NoEnd;
					} else if (state == GameState::Checkmate) {
						return GameState::Checkmate;
					} else if (state == GameState::Check) {
						if (colour == Colour::White) {
							std::cout << "White puts Black in check" << std::endl;
						} else {
							std::cout << "Black puts White in check" << std::endl;
						}
						return GameState::NoEnd;
					}
 		 		}
			}
		} else if (input == "resign") {
			return GameState::Resign;
		} else if (input == "undo") {
			if (board->getHistory()->size() < 2) {
				std::cout << "Have not progressed far enough in the game to undo" << std::endl;
				return GameState::Error;
			} else {
				board->undo();
				board->undo();
				return GameState::Undo;
			}
		} else if (input == "history") {
			return GameState::History;	
		} else {
			std::cout << "Invalid input" << std::endl;
			return GameState::Error;
		}
	}
	return GameState::Error;
}
// may need to 
// Draw, NoEnd, Resign, Checkmate
