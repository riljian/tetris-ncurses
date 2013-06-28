#include "cursesFunc.h"
#include <cstring>
using namespace std;

void colorOut(int color, chtype letter){
	if(color>13)
		attrset(COLOR_PAIR(color));
	else
		attrset(A_BOLD|COLOR_PAIR(color));
	addch(letter);
	attrset(A_NORMAL);
}

void startCurses(){
	initscr();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);
	init_pair(8, COLOR_BLACK, COLOR_RED);
	init_pair(9, COLOR_BLACK, COLOR_GREEN);
	init_pair(10, COLOR_BLACK, COLOR_YELLOW);
	init_pair(11, COLOR_BLACK, COLOR_BLUE);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(13, COLOR_BLACK, COLOR_CYAN);
	init_pair(14, COLOR_WHITE, COLOR_BLACK);
	init_pair(15, COLOR_YELLOW, COLOR_BLACK);
	nodelay(stdscr, true);
	noecho();
	keypad(stdscr, true);
}

void printMiddle(const char* str){
	int x, y;
	erase();
	getmaxyx(stdscr, y, x);
	mvaddstr(y/2, (x-strlen(str))/2, str);
	refresh();
}

int drawNumber(int y, int x, int n){
	int i, j;
	switch(n){
		case 0:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else
							colorOut(2, ACS_BSBS);
					}
					else if(i==1){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_BSSB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i<=3){
						if(j==1||j==3||j==5)
							continue;
						else
							colorOut(2, ACS_SBSB);
					}
					else if(i==4){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_SSBB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_SBBS);
						else continue;
					}
					else{
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else
							colorOut(2, ACS_BSBS);
					}
				}
			return 0;
		case 1:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i<4&&j>4)
						continue;
					else if(i==0){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else
							colorOut(2, ACS_BSBS);
					}
					else if(i==1){
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==1)
							colorOut(2, ACS_BSBS);
						else if(j==2)
							colorOut(2, ACS_BBSS);
						else if(j==4)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i<=3){
						if(j==2||j==4)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==4){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==1||j==5)
							colorOut(2, ACS_BSBS);
						else if(j==2)
							colorOut(2, ACS_SBBS);
						else if(j==4)
							colorOut(2, ACS_SSBB);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else{
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else
							colorOut(2, ACS_BSBS);
					}
				}
			return 0;
		case 2:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else
							colorOut(2, ACS_BSBS);
					}
					else if(i==1){
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==1||j==2)
							colorOut(2, ACS_BSBS);
						else if(j==3)
							colorOut(2, ACS_BBSS);
						else if(j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==2){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==1||j==2)
							colorOut(2, ACS_BSBS);
						else if(j==3)
							colorOut(2, ACS_SBBS);
						else if(j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==3){
						if(j==0)
							colorOut(2, ACS_SBSB);
						else if(j==3)
							colorOut(2, ACS_BSSB);
						else if(j==4||j==5)
							colorOut(2, ACS_BSBS);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else continue;
					}
					else if(i==4){
						if(j==0)
							colorOut(2, ACS_SBSB);
						else if(j==3)
							colorOut(2, ACS_SSBB);
						else if(j==4||j==5)
							colorOut(2, ACS_BSBS);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else{
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else
							colorOut(2, ACS_BSBS);
					}
				}
			return 0;
		case 3:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else
							colorOut(2, ACS_BSBS);
					}
					else if(i==1){
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==1||j==2)
							colorOut(2, ACS_BSBS);
						else if(j==3)
							colorOut(2, ACS_BBSS);
						else if(j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==2||i==4){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==1||j==2)
							colorOut(2, ACS_BSBS);
						else if(j==3)
							colorOut(2, ACS_SBBS);
						else if(j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==3){
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==1||j==2)
							colorOut(2, ACS_BSBS);
						else if(j==3)
							colorOut(2, ACS_BBSS);
						else if(j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else{
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else
							colorOut(2, ACS_BSBS);
					}
				}
			return 0;
		case 4:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0||j==4)
							colorOut(2, ACS_BSSB);
						else if(j==1||j==5)
							colorOut(2, ACS_BSBS);
						else if(j==2||j==6)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i==1){
						if(j==1||j==3||j==5)
							continue;
						else
							colorOut(2, ACS_SBSB);
					}
					else if(i==2){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_SSBB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_SBBS);
						else continue;
					}
					else if(i==3){
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j<=3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else if(j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==4){
						if(j==4||j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else{
						if(j==4)
							colorOut(2, ACS_SSBB);
						else if(j==5)
							colorOut(2, ACS_BSBS);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else continue;
					}
				}
			return 0;
		case 5:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else
							colorOut(2, ACS_BSBS);
					}
					else if(i==1){
						if(j==0)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_BSSB);
						else if(j>2&&j<6)
							colorOut(2, ACS_BSBS);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else continue;
					}
					else if(i==2){
						if(j==0)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_SSBB);
						else if(j>2&&j<6)
							colorOut(2, ACS_BSBS);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i==3){
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j<=3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else if(j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==4){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j<=3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_SBBS);
						else if(j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else{
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else
							colorOut(2, ACS_BSBS);
					}
				}
			return 0;
		case 6:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==1)
							colorOut(2, ACS_BSBS);
						else if(j==2)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i==1){
						if(j==0||j==2)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==2){
						if(j==0)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_SSBB);
						else if(j>2&&j<6)
							colorOut(2, ACS_BSBS);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i==3){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_BSSB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i==4){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_SSBB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_SBBS);
						else continue;
					}
					else{
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else
							colorOut(2, ACS_BSBS);
					}
				}
			return 0;
		case 7:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else
							colorOut(2, ACS_BSBS);
					}
					else if(i==1){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_BSSB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i==2){
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==1)
							colorOut(2, ACS_BSBS);
						else if(j==2)
							colorOut(2, ACS_SBBS);
						else if(j==4||j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==3||i==4){
						if(j==4||j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else{
						if(j==4)
							colorOut(2, ACS_SSBB);
						else if(j==5)
							colorOut(2, ACS_BSBS);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else continue;
					}
				}
			return 0;
		case 8:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else
							colorOut(2, ACS_BSBS);
					}
					else if(i==1){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_BSSB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i==2){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_SSBB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_SBBS);
						else continue;
					}
					else if(i==3){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_BSSB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i==4){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_SSBB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_SBBS);
						else continue;
					}
					else{
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else
							colorOut(2, ACS_BSBS);
					}
				}
			return 0;
		case 9:
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0)
							colorOut(2, ACS_BSSB);
						else if(j==6)
							colorOut(2, ACS_BBSS);
						else
							colorOut(2, ACS_BSBS);
					}
					else if(i==1){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_BSSB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else continue;
					}
					else if(i==2){
						if(j==0||j==6)
							colorOut(2, ACS_SBSB);
						else if(j==2)
							colorOut(2, ACS_SSBB);
						else if(j==3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_SBBS);
						else continue;
					}
					else if(i==3){
						if(j==0)
							colorOut(2, ACS_SSBB);
						else if(j<=3)
							colorOut(2, ACS_BSBS);
						else if(j==4)
							colorOut(2, ACS_BBSS);
						else if(j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else if(i==4){
						if(j==4||j==6)
							colorOut(2, ACS_SBSB);
						else continue;
					}
					else{
						if(j==4)
							colorOut(2, ACS_SSBB);
						else if(j==5)
							colorOut(2, ACS_BSBS);
						else if(j==6)
							colorOut(2, ACS_SBBS);
						else continue;
					}
				}
			return 0;
		case ':':
			for(i=0;i<=5;++i)
				for(j=0;j<=6;++j){
					move(y+i, x+j);
					if((i==1&&j==2)||(i==3&&j==2))
						colorOut(2, ACS_BSSB);
					else if((i==1&&j==4)||(i==3&&j==4))
						colorOut(2, ACS_BBSS);
					else if((i==2&&j==2)||(i==4&&j==2))
						colorOut(2, ACS_SSBB);
					else if((i==2&&j==4)||(i==4&&j==4))
						colorOut(2, ACS_SBBS);
					else if(j==3&&(i>0&&i<5))
						colorOut(2, ACS_BSBS);
					else continue;
				}
			return 0;
		case 'G':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0)
						colorOut(7, ' ');
					else if(i==1){
						if(j==0)
							colorOut(7, ' ');
						else continue;
					}
					else if(i==2){
						if(j==1||j==2)
							continue;
						else
							colorOut(7, ' ');
					}
					else if(i==3){
						if(j==0||j==4)
							colorOut(7, ' ');
						else continue;
					}
					else
						colorOut(7, ' ');
				}
			return 0;
		case 'O':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0||i==4)
						colorOut(8, ' ');
					else{
						if(j==0||j==4)
							colorOut(8, ' ');
						else continue;
					}
				}
			return 0;
		case 'V':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i<3){
						if(j==0||j==4)
							colorOut(9, ' ');
						else continue;
					}
					else if(i==3){
						if(j==1||j==3)
							colorOut(9, ' ');
						else continue;
					}
					else{
						if(j==2)
							colorOut(9, ' ');
						else continue;
					}
				}
			return 0;
		case 'M':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0)
						colorOut(10, ' ');
					else{
						if(j==1||j==3)
							continue;
						else
							colorOut(10, ' ');
					}
				}
			return 0;
		case 'A':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0||i==2)
						colorOut(11, ' ');
					else{
						if(j==0||j==4)
							colorOut(11, ' ');
						else continue;
					}
				}
			return 0;
		case 'E':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0||i==2||i==4)
						colorOut(12, ' ');
					else{
						if(j==0||j==1)
							colorOut(12, ' ');
						else continue;
					}
				}
			return 0;
		case 'R':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0||i==2)
						colorOut(13, ' ');
					else if(i==1){
						if(j==0||j==4)
							colorOut(13, ' ');
						else continue;
					}
					else if(i==3){
						if(j==0||j==3)
							colorOut(13, ' ');
						else continue;
					}
					else{
						if(j==0||j==4)
							colorOut(13, ' ');
						else continue;
					}
				}
			return 0;
		case 'P':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0||i==2)
						colorOut(13, ' ');
					else if(i==1){
						if(j==0||j==4)
							colorOut(13, ' ');
						else continue;
					}
					else if(i==3){
						if(j==0)
							colorOut(13, ' ');
						else continue;
					}
					else{
						if(j==0)
							colorOut(13, ' ');
						else continue;
					}
				}
			return 0;
		case 'L':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i<4){
						if(j==1||j==0)
							colorOut(12, ' ');
						else continue;
					}
					else
						colorOut(12, ' ');
				}
			return 0;
		case 'Y':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0||j==4)
							colorOut(11, ' ');
						else continue;
					}
					else if(i==1){
						if(j==1||j==3)
							colorOut(11, ' ');
						else continue;
					}
					else{
						if(j==2)
							colorOut(11, ' ');
						else continue;
					}
				}
			return 0;
		case 'W':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==4){
						if(j==1||j==3)
							colorOut(10, ' ');
						else continue;
					}
					else{
						if(j==1||j==3)
							continue;
						else
							colorOut(10, ' ');
					}
				}
			return 0;
		case 'I':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i>0&&i<4){
						if(j==2)
							colorOut(11, ' ');
						else continue;
					}
					else
						colorOut(11, ' ');
				}
			return 0;
		case 'D':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i>0&&i<4){
						if(j==0||j==3||j==4)
							colorOut(7, ' ');
						else continue;
					}
					else
						colorOut(7, ' ');
				}
			return 0;
		case 'N':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0){
						if(j==0||j==4)
							colorOut(8, ' ');
						else continue;
					}
					else if(i==1){
						if(j==1||j==4||j==0)
							colorOut(8, ' ');
						else continue;
					}
					else if(i==2){
						if(j==2||j==4||j==0)
							colorOut(8, ' ');
						else continue;
					}
					else if(i==3){
						if(j==3||j==4||j==0)
							colorOut(8, ' ');
						else continue;
					}
					else{
						if(j==0||j==4)
							colorOut(8, ' ');
						else continue;
					}
				}
			return 0;
		case 'S':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i==0||i==2||i==4)
						colorOut(10, ' ');
					else if(i==1){
						if(j==0||j==1)
							colorOut(10, ' ');
						else continue;
					}
					else{
						if(j==3||j==4)
							colorOut(10, ' ');
						else continue;
					}
				}
			return 0;
		case 'T':
			for(i=0;i<5;++i)
				for(j=0;j<5;++j){
					move(y+i, x+j);
					if(i>0){
						if(j==2)
							colorOut(9, ' ');
						else continue;
					}
					else
						colorOut(9, ' ');
				}
			return 0;
	}
}
