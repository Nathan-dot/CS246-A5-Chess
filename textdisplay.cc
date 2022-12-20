#include "textdisplay.h"
#include "position.h"
#include "piece.h"
#include <vector>

TextDisplay::TextDisplay() {
	std::vector<char> evenRow;
	std::vector<char> oddRow;
        // since every other row is same - only have 2 variants
        for (int i = 0; i < 8; ++i) {
                (i % 2 == 0) ? evenRow.emplace_back('_') : evenRow.emplace_back(' ');
                (i % 2 == 0) ? oddRow.emplace_back(' ') : oddRow.emplace_back('_');
        }
        // check if row is even or odd now
        for (int j = 0; j < 8; ++j) {
                if (j % 2 == 0) {
                        board.emplace_back(evenRow);
                } else {
                        board.emplace_back(oddRow);
                }
        }
}

void TextDisplay::setDefaultBoard() {
	 board[0][0] = 'r';
         board[0][7] = 'r';
         board[0][1] = 'n';
	 board[0][6] = 'n';
	 board[0][2] = 'b';
	 board[0][5] = 'b';
	 board[0][3] = 'q';
	 board[0][4] = 'k';
	 board[7][0] = 'R';
	 board[7][7] = 'R';
	 board[7][1] = 'N';
	 board[7][6] = 'N';
	 board[7][2] = 'B';
	 board[7][5] = 'B';
	 board[7][3] = 'Q';
	 board[7][4] = 'K';	
	for (int i = 0; i < 8; ++i) {
		board[1][i] = 'p';
		board[6][i] = 'P';
	}
}

void TextDisplay::alter(const Position position, const char piece) {
	board[position.row][position.col] = piece;
}
        
void TextDisplay::notify(const Move curr, bool undoDisplay) {
	int initialRow = curr.initialPos.row;
	int initialCol = curr.initialPos.col;
	int finalRow = curr.finalPos.row;
	int finalCol = curr.finalPos.col;
	if (!undoDisplay) {
		if ((initialRow + initialCol) % 2 == 0) {
			board[initialRow][initialCol] = '_';
		} else {
			board[initialRow][initialCol] = ' ';
		}
		board[finalRow][finalCol] = curr.movingPiece->getPieceName();
		if (curr.isCastle) {
			if (initialCol < finalCol) {
				if (curr.movingPiece->getOwner() == Colour::White) {
					board[initialRow][5] = 'R';
					if (initialRow % 2 == 0) { // dont actually have to do this way
						board[initialRow][7] = '_'; // even row
					} else {
						board[initialRow][7] = ' ';
					}
				} else {
					board[initialRow][5] = 'r';
					if (initialRow % 2 == 0) {
						board[initialRow][7] = ' ';
					} else {
						board[initialRow][7] = '_';
					}
				}
			} else {
				if (curr.movingPiece->getOwner() == Colour::White) {
                                        board[initialRow][3] = 'R';
                                        if (initialRow % 2 == 0) { // dont actually have to do this way
                                                board[initialRow][0] = '_'; // even row
                                        } else {
                                                board[initialRow][0] = ' ';
                                        }
                                } else {
                                        board[initialRow][3] = 'r';
                                        if (initialRow % 2 == 0) {
                                                board[initialRow][0] = ' ';
                                        } else {
                                                board[initialRow][0] = '_';
                                        }
                                }

			}
		}
		if (curr.enPassant) {
			if ((initialRow + finalCol) % 2 == 0) {
				board[initialRow][finalCol] = ' ';
			} else {
				board[initialRow][finalCol] = '_';
			}
		}
	} else {
			board[initialRow][initialCol] = curr.movingPiece->getPieceName();
                	if (curr.capturedPiece) { // something wrong with
                        	board[finalRow][finalCol] = curr.capturedPiece->getPieceName();
                	} else {
                        	if ((finalRow + finalCol) % 2 == 0) {
                                	board[finalRow][finalCol] = '_';
                        	} else {
                                	board[finalRow][finalCol] = ' ';
                        	}
                	}
                	if (curr.enPassant) {
                        	board[initialRow][finalCol] = curr.enPassant->getPieceName();
                	} if (curr.isCastle) {
                        	if (initialCol < finalCol) {
                                	if (curr.movingPiece->getOwner() == Colour::White) {
                                        	board[initialRow][7] = 'R';
                                        	if (initialRow % 2 == 0) {
                                                	board[initialRow][5] = '_';
                                        	} else {
                                                	board[initialRow][5] = ' ';
                                        	}
                                	} else {
                                        	board[initialRow][7] = 'r';
                                        	if (initialRow % 2 == 0) {
                                                	board[initialRow][5] = '_';
                                        	} else {
                                                	board[initialRow][5] = ' ';
                                        	}
                                	}
                        	} else {
                                	if (curr.movingPiece->getOwner() == Colour::White) {
                                        	board[initialRow][0] = 'R';
                                        	if (initialRow % 2 == 0) {
                                                	board[initialRow][3] = '_';
                                        	} else {
                                                	board[initialRow][3] = ' ';
                                        	}
                                	} else {
                                        	board[initialRow][0] = 'r';
                                        	if (initialRow % 2 == 0) {
                                                	board[initialRow][3] = '_';
                                        	} else {
                                                	board[initialRow][3] = ' ';
                                        	}
                               	 	}
                        	}
                	}
	}
}

std::vector<std::vector<char>> TextDisplay::getBoard() {
	return board;
}


std::ostream &operator<<(std::ostream &out, TextDisplay& display) {
        for (int i = 0; i < 8; ++i) {
                out << 8 - i << " ";
                for (int j = 0; j < 8; ++j) {
                        out << display.board[i][j];
                }
		out << std::endl;
        }
        out << "  ";
        for (char i = 'A'; i <= 'H'; ++i) {
                out << i;
        }
	out << std::endl;
        return out;
}
