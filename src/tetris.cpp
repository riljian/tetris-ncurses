#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cstring>
#include "cursesFunc.h"
#include "tetris.h"
#include "tetrominos.h"
using namespace std;

const int tetris::scoreArray[]={40,80,160,320};
const int tetris::comboBonus[]={1,3,6,10,25,50,100,150,250,1000};

tetris::tetris(int y, int x, char name[50]):startY(y),startX(x){
	vector<char> tmp(width, '#');
	score = comboLine = line = holdTimes = 0;
	combo = -1;
	shadow = new shadowCube;
	for(int i=0;i<height;++i)
		MAP.push_back(tmp);
	for(int i=0;i<8;++i)
		used[i] = 0;
	for(int i=0;i<5;++i)
		next[i] = randomCube();
	strcpy(playerName, name);
}

void tetris::swapCube(cube*& a, cube*& b){
	cube* tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void tetris::holdCube(){
	clearCube(now);
	if(holdTimes!=0){
		clearCube(hold, 3, -19);
	}
	swapCube(now, hold);
	if(holdTimes==0){
		clearCube(shadow, 0, 0);
		newCube();
	}
	hold->setCube();
	showShadow();
	showCube(hold, 3, -19);
	holdTimes = 1;
}
void tetris::drawBoard(){
	int i, j;
	for(i=0;i<=height+1;++i){
		if(i==0||i==height+1)
			for(j=0;j<width+4;++j){
				move(i+startY, j+startX);
				if(j%2)
					colorOut(7,' ');
				else
					colorOut(7,' ');
			}
		else{
			move(i+startY, 0+startX);
			colorOut(7,' ');
			colorOut(7,' ');
			move(i+startY, width+2+startX);
			colorOut(7,' ');
			colorOut(7,' ');
		}
	}
	mvprintw(startY, startX+25, "Next:");
	mvprintw(startY, startX-12, "Hold:");
	mvprintw(startY+6, startX-12, "Line:");
	mvprintw(startY+8, startX-12, "Combo:");
	mvprintw(startY-1, startX+6, "Player: %s", playerName);
}

void tetris::drawMap(){
	int tmp=MAP.size();
	for(int i=0;i<width;++i)
		for(int j=tmp-1,k=19;k>=0;--j,--k){
			move(startY+1+k, startX+2+i);
			switch(MAP[j][i]){
				case '#': colorOut(0, ' '); break;
				case 'I': colorOut(6, '['); break;
				case 'i': colorOut(6, ']'); break;
				case 'J': colorOut(4, '['); break;
				case 'j': colorOut(4, ']'); break;
				case 'L': colorOut(15, '['); break;
				case 'l': colorOut(15, ']'); break;
				case 'O': colorOut(3, '['); break;
				case 'o': colorOut(3, ']'); break;
				case 'S': colorOut(2, '['); break;
				case 's': colorOut(2, ']'); break;
				case 'Z': colorOut(1, '['); break;
				case 'z': colorOut(1, ']'); break;
				case 'T': colorOut(5, '['); break;
				case 't': colorOut(5, ']'); break;
				case 'B': colorOut(3, '@'); break;
				case 'D': colorOut(14, '~'); break;
			}
		}
}

bool tetris::isBound(cube* ptr){
	for(int i=0;i<8;++i){
		if(ptrr.x<0||ptrr.x>=width||ptrr.y>=height)
			return 1;
		if(ptrr.y<0)
			continue;
		if(MAP[ptrr.y][ptrr.x]!='#')
			return 1;
	}
	return 0;
}

int tetris::lineKind(int n){
//0 is empty line
//1 is not emtpy line
//2 is Bomb line
//3 is full line
	int count=0;
	for(int i=0;i<width;++i){
		if(MAP[n][i]=='B'||MAP[n][i]=='D')
			return 2;
		else if(MAP[n][i]!='#')
			++count;
	}
	if(count==width)
		return 3;
	else if(count==0)
		return 0;
	else return 1;
}

int tetris::topLine(){
	clearCube(now);
	for(int i=0;i<MAP.size();++i)
		if(lineKind(i)==1)
			return height - i;
	return 0;
	showCube(now);
}

int tetris::clearLines(){
	int i, j, count=0, Lines=0;
	vector<char> tmp(width, '#');
	for(i=0;i<height;++i, count=0){
/*		for(j=0;j<width;++j)
			if(MAP[i][j]=='#')
				++count;
		if(!count){
			MAP.erase(MAP.begin()+i);
			MAP.insert(MAP.begin(), tmp);
			++Lines;
		}*/
		if(lineKind(i)==3){
			MAP.erase(MAP.begin()+i);
			MAP.insert(MAP.begin(), tmp);
			++Lines;
		}
	}
	if(Lines){
		line += Lines;
		mvprintw(startY+7, startX-6, "   ");
		mvprintw(startY+7, startX-6, "%3d", line);
	}
	mvprintw(startY+9, startX-6, "   ");
	if(comboLine!=line)
		++combo;
	else
		combo = -1;
	if(combo>0)
		mvprintw(startY+9, startX-6, "%3d", combo);
	score += scoreArray[Lines-1] * comboBonus[combo];
	comboLine = line;
	return Lines;
}

void tetris::addBombLine(int amount){
	for(int j=0;j<amount;++j){
		vector<char> tmp(width-2,'D');
		int r = rand()%(width-2);
		for(int i=0;i<2;++i)
			tmp.insert(tmp.begin()+r, 'B');
		MAP.push_back(tmp);
		MAP.erase(MAP.begin());
		for(int k=0;k<8;++k){
			now->range[k].y -= 1;
			shadow->range[k].y -= 1;
		}
	}
	drawMap();
	showShadow();
	refresh();
}

int tetris::clearBombLine(){
	vector<char> tmp(width, '#');
	int count=0;
	clearCube(now);
	while(lineKind(height-1)==2){
		MAP.erase(MAP.end()-1);
		MAP.insert(MAP.begin(), tmp);
		for(int i=0;i<8;++i)
			now->range[i].y += 1;
		++count;
	}
	showCube(now);
	drawMap();
	return count;
}

void tetris::showShadow(){
	clearCube(shadow, 0, 0);
	*shadow = now;
	while(!isBound(shadow))
		shadow->drop();
	shadow->up();
	showCube(shadow, 0, 0);
}

void tetris::showCube(cube* ptr, int y, int x){
	int a=y, b=x;
	for(int i=0;i<8;++i){
		if((a==-1&&b==-1)||(a==0&&b==0))
			if(ptrr.y<0)
				continue;
		if(a==-1&&b==-1){
			x = y = 0;
			MAP[ptrr.y][ptrr.x] = ptrr.c;
		}
		move(ptrr.y+startY+1+y, ptrr.x+startX+2+x);
		switch(ptrr.c){
			case 'I': colorOut(6, '['); break;
			case 'i': colorOut(6, ']'); break;
			case 'J': colorOut(4, '['); break;
			case 'j': colorOut(4, ']'); break;
			case 'L': colorOut(15, '['); break;
			case 'l': colorOut(15, ']'); break;
			case 'O': colorOut(3, '['); break;
			case 'o': colorOut(3, ']'); break;
			case 'S': colorOut(2, '['); break;
			case 's': colorOut(2, ']'); break;
			case 'Z': colorOut(1, '['); break;
			case 'z': colorOut(1, ']'); break;
			case 'T': colorOut(5, '['); break;
			case 't': colorOut(5, ']'); break;
			case 'W': colorOut(14, '['); break;
			case 'w': colorOut(14, ']'); break;
		}
	}
}

void tetris::clearCube(cube* ptr, int y, int x){
	int a=y, b=x;
	for(int i=0;i<8;++i){
		if((a==-1&&b==-1)||(a==0&&b==0))
			if(ptrr.y<0)
				continue;
		if(a==-1&&b==-1){
			x = y = 0;
			MAP[ptrr.y][ptrr.x] = '#';
		}
		move(ptrr.y+startY+1+y, ptrr.x+startX+2+x);
		addch(' ');
	}
}

void tetris::newCube(){
	for(int i=0;i<3;++i)
		clearCube(next[i], 3+i*5, 17);
	swapCube(now, next[0]);
	for(int i=0;i<4;++i)
		swapCube(next[i], next[i+1]);
	next[4] = randomCube();
	for(int i=0;i<3;++i)
		showCube(next[i], 3+i*5, 17);
	*shadow = now;
	showShadow();
}

cube* tetris::randomCube(){
	if(used[7]==7)
		for(int i=0;i<8;++i)
			used[i] = 0;
	int j = rand() % 7;
	while(used[j])
		j = (j+3) % 7;
	++used[j];
	++used[7];
	switch(j){
		case 0:
			return new Jcube;
		case 1:
			return new Lcube;
		case 2:
			return new Zcube;
		case 3:
			return new Scube;
		case 4:
			return new Ocube;
		case 5:
			return new Icube;
		case 6:
			return new Tcube;
	}
}

void tetris::playMethod(const char* str){
	mvprintw(startY+15, startX-15, "'%c' to rotate", str[0]);
	mvprintw(startY+16, startX-15, "'%c' to right", str[1]);
	mvprintw(startY+17, startX-15, "'%c' to left", str[2]);
	mvprintw(startY+18, startX-15, "'%c' to down", str[3]);
	mvprintw(startY+19, startX-15, "'%c' to drop", str[4]);
	mvprintw(startY+20, startX-15, "'%c' to pause", str[5]);
	mvprintw(startY+21, startX-15, "'%c' to hold", str[6]);
	if(str[7]){
		mvprintw(startY+22, startX-15, "'%c' to save", str[7]);
		mvprintw(startY+23, startX-15, "'%c' to load", str[8]);
	}
}
