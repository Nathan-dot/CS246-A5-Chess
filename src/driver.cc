#include "game.h"
#include <iostream>
#include <sstream>
#include <string>


// 0 is default, 5 is human, 1-4 is for computer 
int interpretLevel(std::string player) {
        // hard coded to match input format "computer [1-4]"
        if (player.length() == 9 && player.substr(0, 8) == "computer") {
                return player[8] - '0';
        } else if (player == "human") {
		return 5;
	}
        return 0;
}

int main() {
	 std::string input;
	 Game newGame;
	 while (getline(std::cin, input)) {
                std::string command1;
                std::string command2;
		std::istringstream ss(input);
		int whitePlayerLevel = 0;
                int blackPlayerLevel = 0;
		if (ss >> input) {
			if (input == "game") {
				if ((ss >> command1) && (ss >> command2)) {
					whitePlayerLevel = interpretLevel(command1);
					blackPlayerLevel = interpretLevel(command2);
					if (whitePlayerLevel > 0 && blackPlayerLevel > 0) {
						std::cout << "Game Start!" << std::endl;
						newGame.startGame(whitePlayerLevel, blackPlayerLevel);
					// say some error otherwise
					}
				}
			} else if (input == "setup") {
				newGame.setup();	
			}
	 	}
	 }
}
