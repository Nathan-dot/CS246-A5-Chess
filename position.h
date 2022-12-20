#ifndef POSITION_H
#define POSITION_H
#include <string>

struct Position {
	int row;
	int col;
	Position();
	Position(int row, int col);
	bool compare(Position posn) const;
};

Position convertRowAndCol (std::string cell);


#endif 
