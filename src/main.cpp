#include <cstdlib>
#include <ctime>
#include "cursesFunc.h"
#include "game.h"
using namespace std;

int main(){
	int mode;
	startCurses();
	srand(time(NULL));
	game Game;
	while(1){
		mode = Game.start();
		if(!mode)
			break;
		Game.loop(mode);
	}
	endwin();
	return 0;
}
