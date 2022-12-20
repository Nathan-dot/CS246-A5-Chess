CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD -g
EXEC = chess
OBJECTS = cell.o computerai.o ai.o move.o driver.o king.o piece.o queen.o bishop.o game.o humanplayer.o pawn.o position.o knight.o player.o rook.o textdisplay.o board.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
