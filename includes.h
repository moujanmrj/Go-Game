#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define printMenu printf("1)Load\n2)New single player game\n3)New Multiplayer game\n4)Exit\n");
#define printMoves printf("1)Move\n2)Split a Cell\n3)Boost Energy\n4)save\n5)Exit\n");
#define compass printf("1)North\n2)South\n3)NorthEast\n4)NorthWest\n5)SouthEast\n6)SouthWest\n");
#define clear system("cls");
#define count(X) for(int i = 0;i < X;i++)
#define for2(X) for(int i = 0;i < X;i++)for(int j = 0;j < X;j++)
#define setRed SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_RED);

#ifndef _INCLUDES_H
#define _INCLUDES_H

#endif
