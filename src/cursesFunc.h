#ifndef cursesFunc_h
#define cursesFunc_h

#include <ncurses.h>

void colorOut(int, chtype);
void startCurses();
void printMiddle(const char*);
int drawNumber(int, int, int);

#endif
