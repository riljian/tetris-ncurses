#ifndef tetris_h
#define tetris_h

#include <vector>
#include "tetrominos.h"
using namespace std;

class tetris{
	friend class game;
	public:
		tetris(int, int, char[]);
	private:
		void drawBoard();
		void drawMap();
		int lineKind(int);
		int topLine();
		int clearLines();
		bool isBound(cube*);
		void showShadow();
		void showCube(cube*, int=-1, int=-1);
		void clearCube(cube*, int=-1, int=-1);
		void swapCube(cube*&, cube*&);
		void newCube();
		void holdCube();
		void playMethod(const char*);
		void addBombLine(int);
		int clearBombLine();
		cube* randomCube();
		cube *next[5], *hold, *now, *shadow;
		static const int scoreArray[], comboBonus[];
		const int startY, startX;
		int used[8], holdTimes, line, combo, comboLine, score;
		char playerName[50];
		vector<vector<char> > MAP;
};

#endif
