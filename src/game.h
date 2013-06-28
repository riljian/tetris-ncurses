#ifndef game_h
#define game_h

#include <ncurses.h>
#include <queue>
using namespace std;

struct Record{
	char name[50];
	int score;
	bool color;
	bool operator<(const struct Record& in) const{
		return score < in.score;
	}
};

class game{
	public:
		game(){
			getmaxyx(stdscr, maxY, maxX);
		}
		int start();
		bool loop(int);
	private:
		bool classicMode();
		bool battleMode();
		void name(int, char[]);
		void showRecord();
		void showScore(int, int);
		void showTime(int);
		void gameover(int, char[]);
		void gamewin(int);
		chtype c;
		int maxY, maxX;
		priority_queue<struct Record> recordQueue;
};

#endif
