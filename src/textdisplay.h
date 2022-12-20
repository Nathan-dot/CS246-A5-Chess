#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "position.h"
#include <vector>
#include "piece.h"
#include "move.h"
#include <iostream>

class TextDisplay {
	std::vector<std::vector<char>> board;
public:
	TextDisplay();
	void setDefaultBoard();
	std::vector<std::vector<char>> getBoard();
	void alter(const Position position, const char piece); 
	void notify(const Move current, bool undoDisplay = false);
	friend std::ostream& operator<<(std::ostream&, TextDisplay&);

};

#endif
