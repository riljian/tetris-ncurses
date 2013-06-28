#include <ctime>
#include <cstdio>
#include <fstream>
#include <cstring>
#include "cursesFunc.h"
#include "tetris.h"
#include "game.h"
#define originalSpeed 300000
#define changedSpeed  10000
#define battleTime 120
using namespace std;

void game::showRecord(){
	struct Record tmp;
	ofstream output("record.dat", ios::out);
	erase();
	mvprintw(3, maxX/2-15, "Rank         Name        Score");
	for(int i=1;!recordQueue.empty()&&i<=20;++i){
		tmp = recordQueue.top();
		if(tmp.color)
			attrset(A_BOLD|COLOR_PAIR(3));
		mvprintw(4+i, maxX/2-15, "%2d  %14s   %9d", i, tmp.name, tmp.score);
		attrset(A_NORMAL);
		output << tmp.name << ' ' << tmp.score << ' ' << '0' <<  endl;
		recordQueue.pop();
	}
	output.close();
	mvprintw(maxY-1, maxX/2-11, "Press 't' to continue");
	mvprintw(maxY-2, maxX/2-16, "Press 'd' to delete the record");
	refresh();
	while(!recordQueue.empty())
		recordQueue.pop();
	chtype c;
	while((c=getch())!='t'&&c!='d');
	if(c=='d'){
		output.open("record.dat", ios::out);
		output.close();
	}
}

int game::start(){
	chtype c;
	struct Record tmp;
	while(!recordQueue.empty())
		recordQueue.pop();
	ifstream input("record.dat", ios::in);
	while(input >> tmp.name >> tmp.score >> tmp.color)
		recordQueue.push(tmp);
	input.close();
	for(int i, j=0, k=0;;++j){
		if(!(j%80000)){
			erase();
			mvprintw(maxY/2+2, maxX/2-6, "Classic Mode");
			mvprintw(maxY/2+3, maxX/2-6, "Battle Mode");
			mvprintw(maxY/2+4, maxX/2-6, "Record Board");
			mvprintw(maxY/2+5, maxX/2-6, "Leave");
			drawNumber(maxY/2-8+i%4, maxX/2-21, 'T');
			drawNumber(maxY/2-8+(i+1)%4, maxX/2-14, 'E');
			drawNumber(maxY/2-8+(i+2)%4, maxX/2-7, 'T');
			drawNumber(maxY/2-8+(i+3)%4, maxX/2, 'R');
			drawNumber(maxY/2-8+i%4, maxX/2+7, 'I');
			drawNumber(maxY/2-8+(i+1)%4, maxX/2+14, 'S');
			refresh();
			++i;
		}
		c = getch();
		switch(c){
			case KEY_UP:
				if(k==0)
					break;
				mvprintw(maxY/2+k+2, maxX/2-9, "   ");
				--k;
				break;
			case KEY_DOWN:
				if(k==3)
					break;
				mvprintw(maxY/2+k+2, maxX/2-9, "   ");
				++k;
				break;
			case 10: /*ENTER*/
				if(k<=2)
					return k+1;
				else
					return 0;
		}
		mvprintw(maxY/2+k+2, maxX/2-9, " * ");
		refresh();
	}
}

bool game::loop(int mode){
	if(mode==1)
		classicMode();
	else if(mode==2)
		battleMode();
	else
		showRecord();
	return 0;
}

void game::name(int player, char name[50]){
	nodelay(stdscr, false);
	keypad(stdscr, false);
	echo();
	erase();
	mvprintw(maxY/2-1, maxX/2-12, "Please enter your name:");
	mvprintw(maxY-1, maxX/2-18, "Please press 'Enter' when you finish");
	mvprintw(maxY/2+1, maxX/2-12, "Player %d: ", player);
	refresh();
	getstr(name);
	nodelay(stdscr, true);
	keypad(stdscr, true);
	noecho();
}

bool game::classicMode(){
	int i=0, speed=originalSpeed, holdT=1, initTime, usedTime;
	char Name[50];
	name(1, Name);
	erase();
	tetris player1(maxY/2-10,maxX/2-12,Name);
	player1.drawBoard();
	mvprintw(player1.startY+10, player1.startX-12, "Time:");
	player1.playMethod("^><v pasl");
	player1.newCube();
	usedTime = 0;
	initTime  = time(NULL);
	mvprintw(player1.startY+11, player1.startX-9, "%5d:%02d", usedTime/60, usedTime%60);
	showScore(player1.score, 0);
	while(1)
		while(1){
			c = getch();
			if(!(++i%speed)){
				player1.clearCube(player1.now);
				player1.now->drop();
				if(player1.isBound(player1.now)){
					player1.now->up();
					player1.showCube(player1.now);
					if((player1.now->range[7]).y < 0){
						gameover(player1.score, player1.playerName);
						return 1;
					}
					delete player1.now;
					holdT = 1;
					if(player1.clearLines()){
						speed = originalSpeed - ((player1.line/10) * changedSpeed);
						player1.drawMap();
						showScore(player1.score, 0);
					}
					player1.newCube();
					break;
				}
				player1.showCube(player1.now);
			}
			if((time(NULL)-initTime)!=usedTime){
				usedTime = time(NULL) - initTime;
				mvprintw(player1.startY+11, player1.startX-9, "        ");
				mvprintw(player1.startY+11, player1.startX-9, "%5d:%02d", usedTime/60, usedTime%60);
			}
			switch(c){
				case KEY_LEFT:
					player1.clearCube(player1.now);
					*(player1.now) << 2;
					if(player1.isBound(player1.now))
						*(player1.now) >> 2;
					player1.showShadow();
					player1.showCube(player1.now);
					break;
				case KEY_RIGHT:
					player1.clearCube(player1.now);
					*(player1.now) >> 2;
					if(player1.isBound(player1.now))
						*(player1.now) << 2;
					player1.showShadow();
					player1.showCube(player1.now);
					break;
				case KEY_UP:
					player1.clearCube(player1.now);
					*(player1.now) + 1;
					if(player1.isBound(player1.now))
						*(player1.now) + (-1);
					player1.showShadow();
					player1.showCube(player1.now);
					break;
				case KEY_DOWN:
					player1.clearCube(player1.now);
					player1.now->drop();
					if(player1.isBound(player1.now))
						player1.now->up();
					player1.showCube(player1.now);
					break;
				case 'a':
					if(holdT){
						player1.holdCube();
						holdT = 0;
					}
					break;
				case 'p':
					nodelay(stdscr, false);
					mvprintw(player1.startY-2, maxX/2-2, "Pause");
					while(c=getch())
						if(c=='p')
							break;
					initTime = time(NULL) - usedTime;
					nodelay(stdscr, true);
					mvprintw(player1.startY-2, maxX/2-2, "     ");
					break;
				case 's':
					{
						mvprintw(player1.startY-2, maxX/2-2, "Save");
						refresh();
						ofstream output("save.dat", ios::out);
						output << player1.line << ' ' << player1.score << endl;
						output << usedTime << ' ' << speed << endl;
						player1.clearCube(player1.now);
						for(int j=0;j<height;++j){
							for(int k=0;k<width;++k)
								output << player1.MAP[j][k];
							output << endl;
						}
						output.close();
						player1.showCube(player1.now);
						int j=100000000;
						while(--j);
					}
					mvprintw(player1.startY-2, maxX/2-2, "    ");
					break;
				case 'l':
					{
						ifstream input("save.dat", ios::in);
						input >> player1.line >> player1.score;
						input >> usedTime >> speed;
						for(int j=0;j<height;++j){
							for(int k=0;k<width;++k)
								input >> player1.MAP[j][k];
						}
						input.close();
						initTime = time(NULL) - usedTime;
						player1.drawMap();
						showScore(player1.score, 0);
						mvprintw(player1.startY+11, player1.startX-7, "      ");
						mvprintw(player1.startY+11, player1.startX-7, "%6d", player1.score);
						mvprintw(player1.startY+7, player1.startX-6, "   ");
						mvprintw(player1.startY+7, player1.startX-6, "%3d", player1.line);
						*(player1.shadow) = player1.now;
						player1.showShadow();
						player1.showCube(player1.now);
					}
					break;
				case ' ':
					while(1){
						player1.clearCube(player1.now);
						player1.now->drop();
						if(player1.isBound(player1.now)){
							player1.now->up();
							player1.showCube(player1.now);
							break;
						}
					}
					break;
				case 27: /*ESC*/
					return 0;
			}
		}
}

bool game::battleMode(){
	int i=0, speed=originalSpeed, holdT1=1, holdT2=1, KO1=0, KO2=0, stillTime=battleTime, initTime, u;
	char player1Name[50], player2Name[50];
	name(1, player1Name);
	name(2, player2Name);
	tetris player1(maxY/2-10,maxX/4-12,player1Name);
	tetris player2(maxY/2-10,(maxX*3)/4-12,player2Name);
	initTime  = time(NULL);
	while((time(NULL)-initTime)<3){
		erase();
		drawNumber(maxY/2-3, maxX/2-3, 3+initTime-time(NULL));
		refresh();
	}
	erase();
	refresh();
	player1.drawBoard();
	player2.drawBoard();
	player1.newCube();
	player2.newCube();
	mvprintw(player1.startY+10, player1.startX-12, "KO:");
	mvprintw(player2.startY+10, player2.startX-12, "KO:");
	player1.playMethod("efsdapq");
	player2.playMethod("^><vlpo");
	initTime  = time(NULL);
	showTime(stillTime);
	while(1){
		while(1){
			c = getch();
			if(!(i%speed)){
				player1.clearCube(player1.now);
				player1.now->drop();
				if(player1.isBound(player1.now)){
					player1.now->up();
					if((player1.now->range[7]).y < 0){
						u = player1.clearBombLine();
						if(u==0)
							KO1 = 5;
						else
							++KO1;
				mvprintw(player2.startY+11, player2.startX-7, " ");
				mvprintw(player2.startY+11, player2.startX-7, "%d", KO1);
				refresh();
					}
					player1.showCube(player1.now);
					delete player1.now;
					holdT1 = 1;
					if(u=player1.clearLines()){
						player1.drawMap();
						if(u+player2.topLine()>20){
							++KO2;
				mvprintw(player1.startY+11, player1.startX-7, " ");
				mvprintw(player1.startY+11, player1.startX-7, "%d", KO2);
				refresh();
							player2.clearBombLine();
						}
						else
							player2.addBombLine(u);
					}
					player1.newCube();
					break;
				}
				player1.showCube(player1.now);
			}
			if(!(++i%speed)){
				player2.clearCube(player2.now);
				player2.now->drop();
				if(player2.isBound(player2.now)){
					player2.now->up();
					if((player2.now->range[7]).y < 0){
						u = player2.clearBombLine();
						if(u==0)
							KO2 = 5;
						else
							++KO2;
				mvprintw(player1.startY+11, player1.startX-7, " ");
				mvprintw(player1.startY+11, player1.startX-7, "%d", KO2);
				refresh();
					}
					player2.showCube(player2.now);
					delete player2.now;
					holdT2 = 1;
					if(u=player2.clearLines()){
						player2.drawMap();
						if(u+player1.topLine()>20){
							++KO1;
				mvprintw(player2.startY+11, player2.startX-7, " ");
				mvprintw(player2.startY+11, player2.startX-7, "%d", KO1);
				refresh();
							player1.clearBombLine();
						}
						else
							player1.addBombLine(u);
					}
					player2.newCube();
					break;
				}
				player2.showCube(player2.now);
			}
			if((battleTime+initTime-time(NULL))!=stillTime){
				stillTime = battleTime + initTime - time(NULL);
				showTime(stillTime);
				speed = originalSpeed - ((12-(stillTime/10)) * changedSpeed);
				if(stillTime<=0)
					break;
			}
			switch(c){
				case 's':
					player1.clearCube(player1.now);
					*(player1.now) << 2;
					if(player1.isBound(player1.now))
						*(player1.now) >> 2;
					player1.showShadow();
					player1.showCube(player1.now);
					break;
				case 'f':
					player1.clearCube(player1.now);
					*(player1.now) >> 2;
					if(player1.isBound(player1.now))
						*(player1.now) << 2;
					player1.showShadow();
					player1.showCube(player1.now);
					break;
				case 'e':
					player1.clearCube(player1.now);
					*(player1.now) + 1;
					if(player1.isBound(player1.now))
						*(player1.now) + (-1);
					player1.showShadow();
					player1.showCube(player1.now);
					break;
				case 'd':
					player1.clearCube(player1.now);
					player1.now->drop();
					if(player1.isBound(player1.now))
						player1.now->up();
					player1.showCube(player1.now);
					break;
				case 'q':
					if(holdT1){
						player1.holdCube();
						holdT1 = 0;
					}
					break;
				case 'p':
					nodelay(stdscr, false);
					mvprintw(player1.startY-2, maxX/2-2, "Pause");
					while(c=getch())
						if(c=='p')
							break;
					initTime = time(NULL) + stillTime -battleTime;
					nodelay(stdscr, true);
					mvprintw(player1.startY-2, maxX/2-2, "     ");
					break;
				case 'a':
					while(1){
						player1.clearCube(player1.now);
						player1.now->drop();
						if(player1.isBound(player1.now)){
							player1.now->up();
							player1.showCube(player1.now);
							break;
						}
					}
					break;
				case KEY_LEFT:
					player2.clearCube(player2.now);
					*(player2.now) << 2;
					if(player2.isBound(player2.now))
						*(player2.now) >> 2;
					player2.showShadow();
					player2.showCube(player2.now);
					break;
				case KEY_RIGHT:
					player2.clearCube(player2.now);
					*(player2.now) >> 2;
					if(player2.isBound(player2.now))
						*(player2.now) << 2;
					player2.showShadow();
					player2.showCube(player2.now);
					break;
				case KEY_UP:
					player2.clearCube(player2.now);
					*(player2.now) + 1;
					if(player2.isBound(player2.now))
						*(player2.now) + (-1);
					player2.showShadow();
					player2.showCube(player2.now);
					break;
				case KEY_DOWN:
					player2.clearCube(player2.now);
					player2.now->drop();
					if(player2.isBound(player2.now))
						player2.now->up();
					player2.showCube(player2.now);
					break;
				case 'o':
					if(holdT2){
						player2.holdCube();
						holdT2 = 0;
					}
					break;
				case 'l':
					while(1){
						player2.clearCube(player2.now);
						player2.now->drop();
						if(player2.isBound(player2.now)){
							player2.now->up();
							player2.showCube(player2.now);
							break;
						}
					}
					break;
				case 27:
					return 0;
			}//end switch
		}
		if(KO1==5||KO2==5||stillTime<=0)
			break;
	}
	if(KO1!=KO2)
		KO1>KO2?gamewin(2):gamewin(1);
	else if(player1.line!=player2.line)
		player1.line>player2.line?gamewin(1):gamewin(2);
	else
		gamewin(0);
	return 0;
}

void game::showTime(int t){
	for(int i=0;i<6;++i){
		move(i, maxX/2-17);
		for(int j=0;j<36;++j)
			addch(' ');
	}
	drawNumber(0, maxX/2-17, t/600);
	drawNumber(0, maxX/2-10, (t/60)%10);
	drawNumber(0, maxX/2-3, ':');
	drawNumber(0, maxX/2+4, (t%60)/10);
	drawNumber(0, maxX/2+11, t%10);
	refresh();
}

void game::showScore(int Score, int y){
	int i, digit, tmp;
	char temp[12];
	digit = sprintf(temp, "%d", Score);
	if(y==0)
		for(i=0;i<6;++i){
			move(i, (maxX/2)-3-((digit/2)*7));
			for(int j=0;j<digit*7;++j)
				addch(' ');
		}
	if(digit%2){
		tmp = (maxX/2)-3-((digit/2)*7);
		for(i=0;i<digit;++i)
			drawNumber(y, tmp+7*i, temp[i]-48);
	}
	else{
		tmp = (maxX/2)-((digit/2)*7);
		for(i=0;i<digit;++i)
			drawNumber(y, tmp+7*i, temp[i]-48);
	}
	refresh();
}

void game::gameover(int score, char pname[50]){
	char c;
	erase();
	drawNumber(3, maxX/2-26, 'G');
	drawNumber(3, maxX/2-20, 'O');
	drawNumber(3, maxX/2-14, 'M');
	drawNumber(3, maxX/2-8, 'E');
	drawNumber(3, maxX/2+2, 'O');
	drawNumber(3, maxX/2+8, 'V');
	drawNumber(3, maxX/2+14, 'E');
	drawNumber(3, maxX/2+20, 'R');
	showScore(score, maxY/2-3);
	struct Record r;
	strcpy(r.name, pname);
	r.score = score;
	r.color = 1;
	recordQueue.push(r);
	mvprintw(maxY-2, maxX/2-10, "Press 't' to continue");
	refresh();
	nodelay(stdscr, false);
	while(1){
		c = getch();
		if(c=='t')
			break;
	}
	nodelay(stdscr, true);
	showRecord();
}

void game::gamewin(int winner){
	chtype tmp;
	if(winner!=1&&winner!=2){
		drawNumber(maxY/2-3, maxX/2-14, 'D');
		drawNumber(maxY/2-3, maxX/2-7, 'R');
		drawNumber(maxY/2-3, maxX/2, 'A');
		drawNumber(maxY/2-3, maxX/2+7, 'W');
	}
	else{
		drawNumber(maxY/2-9, maxX/2-21, 'P');
		drawNumber(maxY/2-9, maxX/2-14, 'L');
		drawNumber(maxY/2-9, maxX/2-7, 'A');
		drawNumber(maxY/2-9, maxX/2, 'Y');
		drawNumber(maxY/2-9, maxX/2+7, 'E');
		drawNumber(maxY/2-9, maxX/2+14, 'R');
		drawNumber(maxY/2, maxX/2-10, 'W');
		drawNumber(maxY/2, maxX/2-3, 'I');
		drawNumber(maxY/2, maxX/2+4, 'N');
		if(winner==1)
			drawNumber(maxY/2-7, maxX/2+21, 1);
		else
			drawNumber(maxY/2-7, maxX/2+21, 2);
	}
	mvprintw(maxY-2, maxX/2-13, "Press 't' key to continue.");
	refresh();
	nodelay(stdscr, false);
	while(1){
		tmp = getch();
		if(tmp=='t')
			break;
	}
	nodelay(stdscr, true);
}
