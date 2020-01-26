#include "includes.h"
#include "funcs.h"

char symbolp1[] = " X ";
char symbolp2[] = " Y ";

Cell* head = NULL;
Cell* addCell (int x,int y, int team);
bool access(int n,Tile map[n][n] , int x, int y);
char * getSymbol(int x , int y , int n , Tile map[n][n]);
Cell* showList();
movePlayer(int n,Tile map[n][n],Cell * movingCell);

void printMap (int n,Tile map[n][n]);

void startGame(int n,Tile map[n][n],bool singlePlayer,bool loaded){
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
	while(1){
		clear
		printMap(n,map);
		Cell* movingCell = showList();
		printMoves
		int play = nextInt();
		if (play == 1){
			movePlayer(n,map,movingCell);
		}
		if (play == 2){
			if(checkEmpty(n,map,movingCell->x,movingCell->y) == 0)
				printf ("Split Failed!");
			else{
				addCell(movingCell->x,movingCell->y,movingCell->team);
				Cell * cell = addCell(movingCell->x,movingCell->y,movingCell->team);
				randomMove(n,map,cell);
				removeCell(movingCell);
			}
		}
		if (play == 3){
			if (map[movingCell->x][movingCell->y].type == Energy && map[movingCell->x][movingCell->y].energy != 0){
				if (map[movingCell->x][movingCell->y].energy < 15){
					movingCell->energy += map[movingCell->x][movingCell->y].energy;
					map[movingCell->x][movingCell->y].energy = 0;
				}
				else{
					movingCell->energy += 15;
					map[movingCell->x][movingCell->y].energy -= 15;
				}
				if (movingCell->energy > 100){
					map[movingCell->x][movingCell->y].energy += movingCell->energy - 100;
					movingCell->energy = 100;
				}
			}
			else{
				printf("Boost Energy Failed!");
			}
		}	
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
			printf("|%s|     " , getSymbol(i,j,n,map));
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
			printf("     |%s|" , getSymbol(i,j,n,map));
		}
		printf("\n");
		for ( int j=1;j<n;j+=2){
			printf("     |___|");
		}
		printf("\n");

	}
}

char * getSymbol(int x , int y,int n,Tile map[n][n]){
	Cell * current =head;
	if(map[x][y].type == Forbidden)return "\\|/";
	while(current != NULL){
		if(current->x == x && current->y == y){
			if(current->team == 1)
				return symbolp1;
			else
				return symbolp2;
		}
		current = current->next;
	}
	return "   ";
}
	
Cell* showList(){
	Cell* current = head;
	int i=1;
	while (current != NULL){
		printf ("%d) %s (%d,%d) | Energy: %d\n",i,current->name,current->x,current->y,current->energy);
		i++;
		current = current->next;
	}
	int chooseCell = nextInt();	
	i=1;
	Cell* find = head;
	while (i != chooseCell){
		find = find->next;
		i++;
	}
	return find;
}

void movePlayer(int n,Tile map[n][n],Cell * movingCell){
	compass
	startMove:;
	int dir = nextInt();
		if (dir == North && access(n,map,movingCell->x-1,movingCell->y))
			movingCell->x=movingCell->x-1;
		else if (dir == South && access(n,map,movingCell->x+1,movingCell->y))
			movingCell->x=movingCell->x+1;
		else if (dir == NorthEast){
			if(movingCell->y %2 == 0 && access(n,map,movingCell->x-1,movingCell->y+1)){
				movingCell->x=movingCell->x-1;
				movingCell->y=movingCell->y+1;
			}
			else if(movingCell->y %2 == 1 && access(n,map,movingCell->x,movingCell->y+1)){
				movingCell->y=movingCell->y+1;
			}
			else{
				printf("Wrong Direction!\n");
				goto startMove;
			}	
		}
		else if (dir == NorthWest){
			if(movingCell->y %2 == 0 && access(n,map,movingCell->x-1,movingCell->y-1)){
				movingCell->x=movingCell->x-1;
				movingCell->y=movingCell->y-1;
			}
			else if(movingCell->y %2 == 1 && access(n,map,movingCell->x,movingCell->y-1)){
				movingCell->y=movingCell->y-1;
			}
			else{
				printf("Wrong Direction!\n");
				goto startMove;
			}
		}
		else if (dir == SouthEast){
			if(movingCell->y %2 == 1 && access(n,map,movingCell->x-1,movingCell->y+1)){
				movingCell->x=movingCell->x+1;
				movingCell->y=movingCell->y+1;
			}
			else if(movingCell->y %2 == 0 && access(n,map,movingCell->x,movingCell->y+1)){
				movingCell->y=movingCell->y+1;
			}
			else{
				printf("Wrong Direction!\n");
				goto startMove;
			}
		}
		else if (dir == SouthWest){
			if(movingCell->y %2 == 1 && access(n,map,movingCell->x-1,movingCell->y-1)){
				movingCell->x=movingCell->x+1;
				movingCell->y=movingCell->y-1;
			}
			else if(movingCell->y %2 == 0 && access(n,map,movingCell->x,movingCell->y-1)){
				movingCell->y=movingCell->y-1;
			}
			else{
				printf("Wrong Direction!\n");
				goto startMove;
			}
		}
		else{
			printf("Wrong Direction!\n");
			goto startMove;
		}
}

bool checkEmpty(int n,Tile map[n][n],int x,int y){
	int empty=0;
	if (y%2 == 1){
		if (access(n,map,x,y-1) == true) empty=1;
		if (access(n,map,x,y+1) == true) empty=1;
		if (access(n,map,x-1,y) == true) empty=1;
		if (access(n,map,x+1,y-1) == true) empty=1;
		if (access(n,map,x+1,y+1) == true) empty=1;
		if (access(n,map,x+1,y) == true) empty=1;
	}
	else{
		if (access(n,map,x,y-1) == true) empty=1;
		if (access(n,map,x,y+1) == true) empty=1;
		if (access(n,map,x-1,y) == true) empty=1;
		if (access(n,map,x-1,y-1) == true) empty=1;
		if (access(n,map,x-1,y+1) == true) empty=1;
		if (access(n,map,x+1,y) == true) empty=1;
	}
	return empty;
}

void randomMove(int n,Tile map[n][n],Cell * movingCell){
	startMove:;
	while(1){
		int dir = rand()%6 +1;
			if (dir == North && access(n,map,movingCell->x-1,movingCell->y)){
				movingCell->x=movingCell->x-1;
				break;
			}
			else if (dir == South && access(n,map,movingCell->x+1,movingCell->y)){
				movingCell->x=movingCell->x+1;
				break;
			}
			else if (dir == NorthEast){
				if(movingCell->y %2 == 0 && access(n,map,movingCell->x-1,movingCell->y+1)){
					movingCell->x=movingCell->x-1;
					movingCell->y=movingCell->y+1;
					break;
				}
				else if(movingCell->y %2 == 1 && access(n,map,movingCell->x,movingCell->y+1)){
					movingCell->y=movingCell->y+1;
					break;
				}
			}
			else if (dir == NorthWest){
				if(movingCell->y %2 == 0 && access(n,map,movingCell->x-1,movingCell->y-1)){
					movingCell->x=movingCell->x-1;
					movingCell->y=movingCell->y-1;
					break;
				}
				else if(movingCell->y %2 == 1 && access(n,map,movingCell->x,movingCell->y-1)){
					movingCell->y=movingCell->y-1;
					break;
				}
			}
			else if (dir == SouthEast){
				if(movingCell->y %2 == 1 && access(n,map,movingCell->x-1,movingCell->y+1)){
					movingCell->x=movingCell->x+1;
					movingCell->y=movingCell->y+1;
					break;
				}
				else if(movingCell->y %2 == 0 && access(n,map,movingCell->x,movingCell->y+1)){
					movingCell->y=movingCell->y+1;
					break;
				}
			}
			else if (dir == SouthWest){
				if(movingCell->y %2 == 1 && access(n,map,movingCell->x-1,movingCell->y-1)){
					movingCell->x=movingCell->x+1;
					movingCell->y=movingCell->y-1;
					break;
				}
				else if(movingCell->y %2 == 0 && access(n,map,movingCell->x,movingCell->y-1)){
					movingCell->y=movingCell->y-1;
					break;
				}
			}
	}
}

removeCell ()

