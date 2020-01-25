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
	int team;
	struct cell* next;
}Cell;

int randomNumber(int min,int max){
	return rand()%(max+1 - min) + min;
}

char * randomString(){
	char *str = (char *) malloc((10 + 1) * sizeof(char)); 
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	for (size_t i = 0; i < 10; i++){ 
		int key = rand() % (sizeof(charset) / sizeof(char) - 1); 
		str[i] = charset[key]; 
		} 
		str[10] = '\0'; 
		return str; 
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
