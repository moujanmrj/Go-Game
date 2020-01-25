#include "includes.h"
#include "funcs.h"

char symbolp1[] = "X";
char symbolp2[] = "Y";

Cell* head = NULL;
Cell* addCell (int x,int y, int team);
bool access(int n,Tile map[n][n] , int x, int y);
char * getSymbol(int x , int y);

void printMap (int n,Tile map[n][n]);

void startGame(int n,int map[n][n],bool singlePlayer,bool loaded){
	if (!loaded){
		int cellNum = nextInt();
		count(cellNum){
			int randX = randomNumber(0,n);
			int randY = randomNumber(0,n);
			while(!access(n,map,randX,randY)){
				randX = randomNumber(0,n);
				randY = randomNumber(0,n);
			}
			addCell(randX,randY,1);
		}
	}

	//game starts
	while(1)
	{
		clear
		printMap(n,map);
	}
}

int main(){
	srand(time(NULL));
	while(1){
		clear
		printMenu
		int input = nextInt();
//		if (input == Load){
//			
//		}
		if (input == Sp || input == Mp){
			unsigned int n;
			char cd[100];
			scanf("%s" , cd);
			FILE *fp = fopen(cd, "rb");
			fread(&n, sizeof(unsigned int),1,fp);
			Tile arr[n][n];
			for (int i=0;i<n;i++){
				for (int j=0;j<n;j++){
					unsigned char temp;
					fread(&temp, sizeof(unsigned char),1,fp);
					arr[i][j].type = toInt(temp);
					arr[i][j].energy = 100;
				}
			}
			fclose(fp);
			startGame(n, arr, input==Sp, false);
		}
		if (input == Exit){
			return 0;
		}
	}
}

Cell* addCell (int x,int y,int team){
	Cell * cell = (Cell *) malloc (sizeof(Cell));
	strcpy(cell->name, randomString());
	cell->energy = 80;
	cell->x = x;
	cell->y = y;
	cell->team = team;
	cell->next = NULL;
	if (head == NULL){
		head = cell;		
	}
	else{
		Cell* current = head;
		while (current->next != NULL){
			current = current->next;
		}
		current->next = cell;
	}
	return cell;
}

bool access(int n,Tile map[n][n] , int x, int y){
	if (x<0 || x>=n || y<0 || y>=n) return false;
	if (map[x][y].type == Forbidden) return false;
	Cell* current = head;
	while (current != NULL){
		if (x == current->x && y == current->y) return false;
		current = current->next;
	}
	return true;
}

void printMap(int n,Tile map[n][n]){
	for (int i=0;i<n;i++){
		for ( int j=0;j<n;j+=2){
			printf("_____     ");
		}
		printf("\n");
		for ( int j=0;j<n;j+=2){
			printf("| %s |     " , getSymbol(i,j));
		}
		printf("\n");
		for ( int j=0;j<n;j+=2){
			printf("|___|     ");
		}
		printf("\n");
		for ( int j=1;j<n;j+=2){
			printf("     _____");
		}
		printf("\n");
		for ( int j=1;j<n;j+=2){
			printf("     | %s |" , getSymbol(i,j));
		}
		printf("\n");
		for ( int j=1;j<n;j+=2){
			printf("     |___|");
		}
		printf("\n");

	}
}

char * getSymbol(int x , int y){
	Cell * current =head;
	while(current != NULL){
		if(current->x == x && current->y == y){
			if(current->team == 1)
				return symbolp1;
			else
				return symbolp2;
		}
		current = current->next;
	}
	return " ";
}

