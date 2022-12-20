#include "position.h"
#include <string>

Position::Position(): row(-1), col(-1) {}

Position::Position(int row, int col) : row{row}, col{col} {}

bool Position::compare(Position posn) const {
	if (row == posn.row && col == posn.col) {
		return true;
	}
	return false;
}

// non-memeber
Position convertRowAndCol (std::string cell) {
	int row = '8' - cell[1];
	int col = cell[0] - 'a';
	if ((col >= 0) && (col <= 7)) {
		if ((row >= 0) && (row <= 7)) {
			return Position(row, col);
		}
	}
	return Position(-1, -1);
}
