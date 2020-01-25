#include "includes.h"

#ifndef _FUNCS_H
#define _FUNCS_H

enum{Energy = 1, Mitosis, Forbidden, Normal };
enum{Load = 1, Sp, Mp, Exit};
enum{North = 1, South, NorthEast, NorthWest, SouthEast, SouthWest};

typedef struct tile{
	int type;
	int energy;
}Tile;

typedef struct cell{
	char name[10];
	int x, y;
	int energy;
};

int randomNumber(int min,int max){
	return rand()%(max+1 - min) + min;
}

int nextInt(){
	int n;
	scanf("%d" , &n);
	return n;
}

int toInt(char a){
	return a - '0';
}

#endif
