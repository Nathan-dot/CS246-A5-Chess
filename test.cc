#include <vector>
#include <iostream>

int main () {
	std::vector<std::vector<char>> board;
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

	 for (int i = 0; i < 8; i++) {
		 std::cout << 8 - i << " ";
                for (int j = 0; j < 8; ++j) {
			std::cout << board[i][j];
                }
		std::cout << std::endl;
        }
	 std::cout << " ";
        for (char i = 'A'; i <= 'H'; ++i) {
		std::cout << i;
        }
}
