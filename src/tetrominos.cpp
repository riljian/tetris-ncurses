#include "tetrominos.h"

cube& cube::drop(){
	for(int i=0;i<8;++i)
		range[i].y += 1;
	return *this;
}

cube& cube::up(){
	for(int i=0;i<8;++i)
		range[i].y -= 1;
	return *this;
}

cube& operator>>(cube& tmp, int n){
	for(int i=0;i<8;++i)
		tmp.range[i].x += n;
	return tmp;
}

cube& operator<<(cube& tmp, int n){
	for(int i=0;i<8;++i)
		tmp.range[i].x -= n;
	return tmp;
}

void cube::operator=(cube* ptr){
	for(int i=0;i<8;i++){
		range[i].x = ptrr.x;
		range[i].y = ptrr.y;
	}
}

void Icube::setCube(){
	for(int i=0;i<8;++i){
		range[i].y = 0 - i/2;
		range[i].x = width/2 + i%2;
		if(i%2)
			range[i].c = 'i';
		else
			range[i].c = 'I';
	}
	degree = 0;
}

Icube& Icube::operator+(int n){
	degree += (90*n);
	if(n<0)
		n *= -1;
	if(degree%180)
		n *= -1;
	range[0].y += (2*n);
	range[0].x += (4*n);
	range[1].y += (2*n);
	range[1].x += (4*n);
	range[2].y += n;
	range[2].x += (2*n);
	range[3].y += n;
	range[3].x += (2*n);
	range[6].y -= n;
	range[6].x -= (2*n);
	range[7].y -= n;
	range[7].x -= (2*n);
}

void Ocube::setCube(){
	for(int i=0;i<8;++i){
		range[i].y = 0 - i/4;
		range[i].x = width/2 + i%4;
		if(i%2)
			range[i].c = 'o';
		else
			range[i].c = 'O';
	}
}

void Scube::setCube(){
	for(int i=0;i<8;++i){
		range[i].y = 0 - i/4;
		if(i>=4)
			range[i].x = width/2 + i%4 + 2;
		else
			range[i].x = width/2 + i%4;
		if(i%2)
			range[i].c = 's';
		else
			range[i].c = 'S';
	}
	degree = 0;
}

Scube& Scube::operator+(int n){
	degree += (90*n);
	if(n<0)
		n *= -1;
	if(degree%180)
		n *= -1;
	range[0].y += (2*n);
	range[1].y += (2*n);
	range[6].x += (4*n);
	range[7].x += (4*n);
}

void Zcube::setCube(){
	for(int i=0;i<8;++i){
		range[i].y = 0 - i/4;
		if(i>=4)
			range[i].x = width/2 + i%4;
		else
			range[i].x = width/2 + i%4 + 2;
		if(i%2)
			range[i].c = 'z';
		else
			range[i].c = 'Z';
	}
	degree = 0;
}

Zcube& Zcube::operator+(int n){
	degree += (90*n);
	if(n<0)
		n *= -1;
	if(degree%180)
		n *= -1;
	range[0].y += (2*n);
	range[1].y += (2*n);
	range[2].x += (4*n);
	range[3].x += (4*n);
}

void Tcube::setCube(){
	for(int i=0;i<8;++i){
		range[i].y = 0 - i/6;
		if(i>=6)
			range[i].x = width/2 + i%6;
		else
			range[i].x = width/2 + i%6 - 2;
		if(i%2)
			range[i].c = 't';
		else
			range[i].c = 'T';
	}
	degree = 0;
}

Tcube& Tcube::operator+(int n){
	if(n<0)
		degree -= 90;
	if(degree%360==0){
		range[0].x += (2*n);
		range[0].y += n;
		range[1].x += (2*n);
		range[1].y += n;
	}
	else if(degree%360==90){
		range[0].x -= (2*n);
		range[0].y -= n;
		range[1].x -= (2*n);
		range[1].y -= n;
		range[6].y += (2*n);
		range[7].y += (2*n);
	}
	else if(degree%360==180){
		range[6].y -= (2*n);
		range[7].y -= (2*n);
		range[4].x -= (2*n);
		range[4].y += n;
		range[5].x -= (2*n);
		range[5].y += n;
	}
	else if(degree%360==270){
		range[4].x += (2*n);
		range[4].y -= n;
		range[5].x += (2*n);
		range[5].y -= n;
	}
	if(n>0)
		degree += 90;
}

void Lcube::setCube(){
	for(int i=0;i<8;++i){
		if(i<=3){
			range[i].y = 0;
			range[i].x = width/2 + i -2;
		}
		else{
			range[i].y = 1 - i/2;
			range[i].x = width/2 + i%2 - 2;
		}
		if(i%2)
			range[i].c = 'l';
		else
			range[i].c = 'L';
	}
	degree = 0;
}

Lcube& Lcube::operator+(int n){
	if(n<0)
		degree -= 90;
	if(degree%360==0){
		range[0].x += (2*n);
		range[0].y -= (2*n);
		range[1].x += (2*n);
		range[1].y -= (2*n);
		range[2].x += (2*n);
		range[2].y -= (2*n);
		range[3].x += (2*n);
		range[3].y -= (2*n);
	}
	else if(degree%360==90){
		range[2].x -= (2*n);
		range[2].y += (2*n);
		range[3].x -= (2*n);
		range[3].y += (2*n);
		range[4].x += (2*n);
		range[5].x += (2*n);
	}
	else if(degree%360==180){
		range[6].y += n;
		range[7].y += n;
		range[2].x -= (4*n);
		range[2].y -= n;
		range[3].x -= (4*n);
		range[3].y -= n;
	}
	else if(degree%360==270){
		range[0].x -= (2*n);
		range[0].y += (2*n);
		range[1].x -= (2*n);
		range[1].y += (2*n);
		range[2].x += (4*n);
		range[2].y += n;
		range[3].x += (4*n);
		range[3].y += n;
		range[4].x -= (2*n);
		range[5].x -= (2*n);
		range[6].y -= n;
		range[7].y -= n;
	}
	if(n>0)
		degree += 90;
}

void Jcube::setCube(){
	for(int i=0;i<8;++i){
		if(i<=3){
			range[i].y = 0;
			range[i].x = width/2 + i -2;
		}
		else{
			range[i].y = 1 - i/2;
			range[i].x = width/2 + i%2;
		}
		if(i%2)
			range[i].c = 'j';
		else
			range[i].c = 'J';
	}
	degree = 0;
}

Jcube& Jcube::operator+(int n){
	if(n<0)
		degree -= 90;
	if(degree%360==0){
		range[0].x += (4*n);
		range[0].y -= n;
		range[1].x += (4*n);
		range[1].y -= n;
		range[2].x += (4*n);
		range[2].y -= n;
		range[3].x += (4*n);
		range[3].y -= n;
	}
	else if(degree%360==90){
		range[0].y -= n;
		range[1].y -= n;
		range[2].x -= (4*n);
		range[2].y += n;
		range[3].x -= (4*n);
		range[3].y += n;
	}
	else if(degree%360==180){
		range[0].x -= (6*n);
		range[1].x -= (6*n);
		range[2].x -= (2*n);
		range[2].y -= (2*n);
		range[3].x -= (2*n);
		range[3].y -= (2*n);
	}
	else if(degree%360==270){
		range[0].x += (2*n);
		range[0].y += (2*n);
		range[1].x += (2*n);
		range[1].y += (2*n);
		range[2].x += (2*n);
		range[2].y += (2*n);
		range[3].x += (2*n);
		range[3].y += (2*n);
	}
	if(n>0)
		degree += 90;
}

shadowCube::shadowCube(){
	for(int i=0;i<8;++i){
		range[i].x = range[i].y = 10;
		if(i%2)
			range[i].c = 'w';
		else
			range[i].c = 'W';
	}
}
