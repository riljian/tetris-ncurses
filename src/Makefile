main: main.o cursesFunc.o game.o tetris.o tetrominos.o
	g++ -O -o tetris main.o cursesFunc.o game.o tetris.o tetrominos.o -lncurses
	rm main.o cursesFunc.o tetris.o game.o tetrominos.o
main.o: main.cpp game.h cursesFunc.h
	g++ -O -c main.cpp -lncurses
game.o: game.h game.cpp tetris.h cursesFunc.h
	g++ -O -c game.cpp -lncurses
cursesFunc.o: cursesFunc.h cursesFunc.cpp
	g++ -O -c cursesFunc.cpp -lncurses
tetris.o: tetris.h tetris.cpp tetrominos.h cursesFunc.h
	g++ -O -c tetris.cpp -lncurses
tetrominos.o: tetrominos.h tetrominos.cpp
	g++ -O -c tetrominos.cpp
