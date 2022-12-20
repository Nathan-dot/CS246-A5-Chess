#include "board.h"
#include "position.h"
#include "colour.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "textdisplay.h"
#include "cell.h"
#include "gamestate.h"
#include "movetype.h"
#include <cctype>
#include <cstdlib>
// change to vector later
Piece* constructPiece(Board* board, const char pieceName, Colour owner);

Board::Board() : moveHistory(new std::vector<Move>), display(new TextDisplay), turn(Colour::White), turnCount(0) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			board[i][j] = new Cell(Position(i, j));
		}
	}
	whitePieces[0] = (constructPiece(this, 'K', Colour::White));
	whitePieces[1] = (constructPiece(this, 'Q', Colour::White));
	whitePieces[2] = (constructPiece(this, 'R', Colour::White));
	whitePieces[3] = (constructPiece(this, 'R', Colour::White));
	whitePieces[4] = (constructPiece(this, 'N', Colour::White));
	whitePieces[5] = (constructPiece(this, 'N', Colour::White));
	whitePieces[6] = (constructPiece(this, 'B', Colour::White));
	whitePieces[7] = (constructPiece(this, 'B', Colour::White));
	blackPieces[0] = (constructPiece(this, 'k', Colour::Black));
	blackPieces[1] = (constructPiece(this, 'q', Colour::Black));
	blackPieces[2] = (constructPiece(this, 'r', Colour::Black));
	blackPieces[3] = (constructPiece(this, 'r', Colour::Black));
	blackPieces[4] = (constructPiece(this, 'n', Colour::Black));
	blackPieces[5] = (constructPiece(this, 'n', Colour::Black));
	blackPieces[6] = (constructPiece(this, 'b', Colour::Black));
	blackPieces[7] = (constructPiece(this, 'b', Colour::Black));
	for (int i = 8; i < 16; ++i) {
		whitePieces[i] = (constructPiece(this, 'P', Colour::White));
		blackPieces[i] = (constructPiece(this, 'p', Colour::Black));
	}
}

Piece* constructPiece(Board* board, const char pieceName, Colour owner) {
	if (tolower(pieceName) == 'k') {
		return new King(board, pieceName, owner);
	} else if (tolower(pieceName) == 'q') {
		return new Queen(board, pieceName, owner);
	} else if (tolower(pieceName) == 'r') {
		return new Rook(board, pieceName, owner);
	} else if (tolower(pieceName) == 'b') {
		return new Bishop(board, pieceName, owner);
	} else if (tolower(pieceName) == 'n') {
		return new Knight(board, pieceName, owner);
	} else {
		return new Pawn(board, pieceName, owner);	
	}
}

Board::~Board() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			delete board[i][j];
		}
	}
	for (int i = 0; i < 16; ++i) {
		delete whitePieces[i];
		delete blackPieces[i];
	}
	delete display;
	delete moveHistory;
}
        
void Board::setup() {
	std::string command;
	std::cout << "Welcome to Setup Mode" << std::endl;
	do {
		std::cout << "Enter a command:" << std::endl;
		std::cin >> command;
		if (command == "+") {
			char pieceName;
			std::string square;
			std::cin >> pieceName;
			std::cin >> square;
			Position position = convertRowAndCol(square);
		        if (pieceName <= 'a') { // checking colour
				for (int i = 0; i < 16; ++i) {
					Piece* piece = whitePieces[i];
					if (piece->getPieceName() == pieceName && 
							((piece->getPosition().row == -1) || piece->getPosition().col == -1)) {
						board[position.row][position.col]->setPiece(piece);
						display->alter(position, pieceName);
						break;
					}
				}
			} else {
				for (int i = 0; i < 16; ++i) {
					Piece* piece = blackPieces[i];
					 if (piece->getPieceName() == pieceName &&
                                                        ((piece->getPosition().row == -1) || piece->getPosition().col == -1)) {
                                                board[position.row][position.col]->setPiece(piece);
						display->alter(position, pieceName);
                                                break;
                                        }
				}
			}
			std::cout << *display;	
		} else if (command == "-") {
			std::string square;
			std::cin >> square;
			Position position = convertRowAndCol(square);
			(board[position.row][position.col])->remove();
			if ((position.row + position.col) % 2 == 0) {
				display->alter(position, '_');
			} else {
				display->alter(position, ' ');	
			}
			std::cout << *display;
		} else if (command == "=") {
			std::string colour;
			std::cin >> colour;
			if (colour == "black") {
				turn = Colour::Black;
			} else {
				turn = Colour::White;
			}
		}
	       	if (command == "done") {
			bool canLeave = true;
			bool inCheck = false;
			bool pawnWrong = false;
			int whiteKingCount = 0;
			int blackKingCount = 0;
			int blackkingx = -1;
			int blackkingy = -1;
			int whitekingx = -1;
			int whitekingy = -1;
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					if ((display->getBoard()).at(i).at(j) == 'k') {
						++blackKingCount;
						blackkingx = i;
						blackkingy = j;
					} else if ((display->getBoard()).at(i).at(j) == 'K') {
						++whiteKingCount;
						whitekingx = i;
						whitekingy = j;
					} else if ((display->getBoard()).at(i).at(j) == 'P' || 
						(display->getBoard()).at(i).at(j) == 'p') {
						if (i == 0 || i == 7) {
							pawnWrong = true;
						}
					}
				}
			}

			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {	
					if ((display->getBoard().at(i).at(j)) == 'k') {
						if (std::abs(whitekingx - i) == 1 || std::abs(whitekingy - j) == 1) {
							inCheck = true;
						}
					} else if ((display->getBoard().at(i).at(j)) == 'K') {
						if (std::abs(blackkingx - i) == 1 || std::abs(blackkingy - j) == 1) {
                                                        inCheck = true;
                                                }
					} else if ((display->getBoard().at(i).at(j) == 'p')) {
						if (whitekingx - i == 1 && std::abs(whitekingy - j) == 1) {
							inCheck = true;
						}
					} else if ((display->getBoard().at(i).at(j) == 'P')) {
                                                if (i - blackkingx == 1 && std::abs(blackkingy - j) == 1) {
                                                        inCheck = true;
                                                }
                                        } else if ((display->getBoard().at(i).at(j) == 'r')) {
						if (whitekingx == i || whitekingy == j) {
							inCheck = true;
						}
					} else if ((display->getBoard().at(i).at(j) == 'R')) {
						if (blackkingx == i || blackkingy == j) {
							inCheck = true;
						}
					} else if ((display->getBoard().at(i).at(j) == 'n')) {
						if ((std::abs(whitekingx - i) == 1 && std::abs(whitekingy - j) == 2) ||
								(std::abs(whitekingx - i) == 2 && std::abs(whitekingy - j) == 1)) {
							inCheck = true;		
						}
					} else if ((display->getBoard().at(i).at(j) == 'N')) {
                                                if ((std::abs(blackkingx - i) == 1 && std::abs(blackkingy - j) == 2) ||
                                                                (std::abs(blackkingx - i) == 2 && std::abs(blackkingy - j) == 1)) {
                                                        inCheck = true;
                                                }       
                                        } else if ((display->getBoard().at(i).at(j) == 'B')) {
						if (std::abs(blackkingx - i) == std::abs(blackkingy - j)) {
							inCheck = true;
						}
					} else if ((display->getBoard().at(i).at(j) == 'b')) {
                                                if (std::abs(whitekingx - i) == std::abs(whitekingy - j)) {
                                                        inCheck = true;
                                                }
                                        } else if ((display->getBoard().at(i).at(j) == 'Q')) {
						if (blackkingx == i || blackkingy == j || 
								(std::abs(blackkingx - i) == std::abs(blackkingy - j))) {
							inCheck = true;
						}
					} else if ((display->getBoard().at(i).at(j) == 'q')) {
                                                if (whitekingx == i || whitekingy == j || 
                                                                (std::abs(whitekingx - i) == std::abs(whitekingy - j))) {
                                                        inCheck = true;
                                                }
					}
				}
			}
			if (whiteKingCount != 1 || blackKingCount != 1) {
				canLeave = false;
                                std::cout << "Cannot leave setup mode - 1 white King and 1 black King necessary" << std::endl;	
			} else if (inCheck) {
				canLeave = false;
				std::cout << "Cannot leave setup mode - King in Check" << std::endl;
			}
		        if (pawnWrong) {	
				std::cout << "Cannot leave setup - Pawn on final row" << std::endl;
				canLeave = false;
			}	 
			if (canLeave) {
				break;
			}
		}
	} while (true);
	update();
}
        
void Board::startgame() {
	board[0][0]->setPiece(blackPieces[2]);
	board[0][1]->setPiece(blackPieces[4]);
	board[0][2]->setPiece(blackPieces[6]);
	board[0][3]->setPiece(blackPieces[1]);
	board[0][4]->setPiece(blackPieces[0]);
	board[0][5]->setPiece(blackPieces[7]);
	board[0][6]->setPiece(blackPieces[5]);
	board[0][7]->setPiece(blackPieces[3]);
	board[7][0]->setPiece(whitePieces[2]);
	board[7][1]->setPiece(whitePieces[4]);
	board[7][2]->setPiece(whitePieces[6]);
	board[7][3]->setPiece(whitePieces[1]);
	board[7][4]->setPiece(whitePieces[0]);
	board[7][5]->setPiece(whitePieces[7]);
	board[7][6]->setPiece(whitePieces[5]);
	board[7][7]->setPiece(whitePieces[3]);
	for (int i = 0; i < 8; ++i) {
		board[1][i]->setPiece(blackPieces[i + 8]);
		board[6][i]->setPiece(whitePieces[i + 8]);
	}
	display->setDefaultBoard();
	std::cout << *display;	
}

GameState Board::move(const Position initialPos, const Position finalPos, bool showDisplay, bool ai) {
	Cell* initialCell = board[initialPos.row][initialPos.col];
	Cell* finalCell = board[finalPos.row][finalPos.col];
	Piece* movingPiece = initialCell->getcurrPiece();
	bool stale = true;
	if (!movingPiece) {
		return GameState::Error;
	} else if (movingPiece->getOwner() != turn) {
		return GameState::Error;
	}
	MoveType result = movingPiece->move(finalPos);
	if (result == MoveType::Illegal) { // 3 4
		return GameState::Error;
	} else {
		Move current = {movingPiece, finalCell->remove(), nullptr, false, false, initialPos, finalPos, movingPiece->getPieceName()};
		initialCell->remove();
		finalCell->setPiece(movingPiece);
		if (result == MoveType::Castling) {
			current.isCastle = true;
			if (initialPos.col < finalPos.col) { // checking which side
				Piece* rook = board[initialPos.row][7]->remove();
				board[initialPos.row][5]->setPiece(rook);
			} else {
				Piece* rook = board[initialPos.row][0]->remove();
                                board[initialPos.row][3]->setPiece(rook);
			}	
		} if (result == MoveType::Promotion) {
			if (ai) {
				Pawn* pawn = dynamic_cast<Pawn*>(movingPiece);
				if (pawn->getOwner() == Colour::White) {
					pawn->promote(constructPiece(this, 'Q', pawn->getOwner()));
				} else {
					pawn->promote(constructPiece(this, 'q', pawn->getOwner()));
				}
			} else {
				std::cout << "What piece would you like to promote to?" << std::endl;
				char promoteTo;
				std::cin >> promoteTo;
				Pawn* pawn = dynamic_cast<Pawn*> (movingPiece);
				if (pawn->getOwner() == Colour::White) {
					pawn->promote(constructPiece(this, std::toupper(promoteTo), pawn->getOwner()));	
				} else {
					pawn->promote(constructPiece(this, std::tolower(promoteTo), pawn->getOwner()));
				}
				current.isPromotion = true;
			}
		} if (result == MoveType::EnPassant) {
			current.enPassant = board[initialPos.row][finalPos.col]->remove();		
		}
		++turnCount;
		moveHistory->push_back(current);
		if (turn == Colour::White) {
			turn = Colour::Black;
		} else {
			turn = Colour::White;
		}
		update();
		if (showDisplay) {
			display->notify(current);
			std::cout << *display;
		}
		if (playerInCheck(turn)) {
			if (checkmate(turn)) {
				return GameState::Checkmate;
			} else {
				return GameState::Check;
			}
		} else if (gameStalemate(turn)) {
			return GameState::Draw;	
		}
		for (int i = 1; i < 16; ++i) {
			if (whitePieces[i]->getPosition().row >= 0 || blackPieces[i]->getPosition().row >= 0) {
				stale = false;
				break;
			}
		}
		if (stale) {
			return GameState::Draw;	
		} else {
			return GameState::NoEnd;
		}
	}
	return GameState::Error;
}

void Board::undo(bool show) {
	if (moveHistory->size() == 0) {
		std::cout << "You've reached the beginning of the game. No moves in history." << std::endl;
		return;
	} 
	const Move curr = moveHistory->back();
	if (show) {
		display->notify(curr, true);	
	}
	moveHistory->pop_back();
	Cell* initialCell = board[curr.initialPos.row][curr.initialPos.col];
	Cell* finalCell = board[curr.finalPos.row][curr.finalPos.row];
	finalCell->setPiece(curr.capturedPiece);
	if (curr.isCastle) {
		if (curr.initialPos.col < curr.finalPos.col) {
			board[curr.initialPos.row][7]->setPiece(board[curr.initialPos.row][5]->remove());
		} else {
			board[curr.initialPos.row][0]->setPiece(board[curr.initialPos.row][3]->remove());
		}
	} else if (curr.isPromotion) {
		Pawn* pawn = dynamic_cast<Pawn*>(curr.movingPiece);
		pawn->revertPromotion();
	} else if (curr.enPassant) {
		board[curr.initialPos.row][curr.finalPos.col]->setPiece(curr.enPassant);
	}
	initialCell->setPiece(curr.movingPiece);
	update();
	if (show) {
		std::cout << *display;
	}
	if (turn == Colour::White) {
		turn = Colour::Black;
	} else {
		turn = Colour::White;
	}
	--turnCount;
}

        
Colour Board::hasOccupancy(const Position cell, Colour owner) {
	Piece* curr = board[cell.row][cell.col]->getcurrPiece();
	if (!curr) {
		return Colour::NoColour;
	} else {
		return curr->getOwner();
	}
}
        
bool Board::causeVulnerable(const Position initialPos, const Position finalPos, Colour owner) {
	Cell* initialCell = board[initialPos.row][initialPos.col];
	bool vulnerable = false;
	Cell* finalCell = board[finalPos.row][finalPos.col];
	Piece* initialPiece = initialCell->remove();
	Piece* finalPiece = finalCell->remove();
	finalCell->setPiece(initialPiece);
	if (owner == Colour::Black) {
		for (int i = 0; i < 16; ++i) {
			if (((whitePieces[i]->getPosition()).row != -1) && 
					(whitePieces[i]->touchable(blackPieces[0]->getPosition()) != MoveType::Illegal)) {
			// iterating through to see if any whitePieces can touch our black king
				vulnerable = true;
				break;
			} 
		}
	} else {
		for (int i = 0; i < 16; ++i) {
			if (((blackPieces[i]->getPosition()).row != -1) && 
					(blackPieces[i]->touchable(whitePieces[0]->getPosition()) != MoveType::Illegal)) {
				vulnerable = true;
				break;
			}
		}
	}
	finalCell->setPiece(finalPiece);
	initialCell->setPiece(initialPiece);
	return vulnerable;
}
        
bool Board::vulnerable(const Position initialPos, Colour owner) {
	if (owner == Colour::White) {
		return board[initialPos.row][initialPos.col]->getwhiteTouchable().size();
	} else {
		return board[initialPos.row][initialPos.col]->getblackTouchable().size();
	}
}

Colour Board::whoseTurn() {
	return turn;
}


void Board::update() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Position position(i, j);
			std::vector<Piece*> white;
			std::vector<Piece*> black;
			for (int k = 0; k < 16; ++k) {
				Position whitePos = whitePieces[k]->getPosition();
				Position blackPos = blackPieces[k]->getPosition();
				if (!position.compare(whitePos) && whitePos.row >= 0
						       	&& (whitePieces[k]->touchable(position) != MoveType::Illegal)) {
					white.push_back(whitePieces[k]);
				} if (!position.compare(blackPos) && blackPos.row >= 0 
						&& (blackPieces[k]->touchable(position) != MoveType::Illegal)) {
					black.push_back(blackPieces[k]);
				}
			}
			(board[i][j]->update(white, black));	
		}
	}
}

std::vector<Move>* Board::getHistory() {
	return moveHistory;
}

bool Board::playerInCheck(Colour player) {
	// check king threats and see if any exist
	if (player == Colour::White) {
		return whitePieces[0]->getChecked();
	} else {
		return blackPieces[0]->getChecked();
	}
}

bool Board::gameStalemate(Colour player) {
	if (player == Colour::Black) {
		for (int i = 0; i < 16; ++i) {
			if (whitePieces[i]->getPosition().row >= 0) {
				for (int j = 0; j < 8; ++j) { // simulating board squares
					for (int k = 0; k < 8; ++k) {
						if (whitePieces[i]->move(Position(j, k)) != MoveType::Illegal) {
							return false;
						}
					}	
				}
			}
		}
	} else {
		for (int i = 0; i < 16; ++i) {
			if (blackPieces[i]->getPosition().row >= 0) {
				for (int j = 0; j < 8; ++j) {
					for (int k = 0; k < 8; ++k) {
						if (blackPieces[i]->move(Position(j, k)) != MoveType::Illegal) {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}

bool Board::checkmate(Colour player) {
	Piece* newPiece;
	for (int i = 0; i < 16; ++i) {
		if (player == Colour::White) {
			newPiece = whitePieces[i];
		} else {
			newPiece = blackPieces[i];
		}
		std::vector<Move> move = legalMove(*this, newPiece);
		if (!move.empty()) {
			return false;
		}
	}
	return true;
}


std::ostream &operator<<(std::ostream &out, Board &board) {
	std::cout << *(board.display);
	return out;
}

void Board::printHistory(Colour turn) {
	int s = turnCount;
	std::string currentPlayer;
	for (int i = moveHistory->size() - 1; i >= 0; --i) {
		std::cout << "Turn " << s << ": " << moveHistory->at(i).movingPiece->getPieceName() << " from " << 
			(char) (moveHistory->at(i).initialPos.col % 26 + 97) << 8 - moveHistory->at(i).initialPos.row << " to " << 
			(char) (moveHistory->at(i).finalPos.col % 26 + 97) << 8 - moveHistory->at(i).finalPos.row << std::endl;
		
		--s;
	}
}

void Board::setAiPieces(ComputerAi &ai) {
	ai.setAiPieces(whitePieces, blackPieces);
}


