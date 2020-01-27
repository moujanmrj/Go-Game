#include "includes.h"
#include "funcs.h"

char symbolp1[] = "   X   ";
char symbolp2[] = "   O   ";
WORD Attributes = 0;
Cell* head = NULL;
Cell* addCell (int x,int y, int team);
bool access(int n,Tile map[n][n] , int x, int y);
char * getSymbol(int x , int y , int n , Tile map[n][n]);
Cell* showList(int n);
void movePlayer(int n,Tile map[n][n],Cell * movingCell);
bool checkEmpty(int n,Tile map[n][n],int x,int y);
void removeCell (Cell* movingCell);
void printMap (int n,Tile map[n][n]);
void randomMove(int n,Tile map[n][n],Cell * movingCell);

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
			Cell * nc = addCell(randX,randY,1);
			nc->canMove = true;
		}
		if (!singlePlayer){
			count(cellNum){
				int randX = randomNumber(0,n);
				int randY = randomNumber(0,n);
				while(!access(n,map,randX,randY)){
					randX = randomNumber(0,n);
					randY = randomNumber(0,n);
				}
				Cell* nc = addCell(randX,randY,2);
				nc->canMove = false;
			}
		}
	}

	//game starts
	while(1){
		clear
		printMap(n,map);
		Cell* movingCell = showList(n);
		printMoves
		int play = nextInt();
		if (play == 1){
			movePlayer(n,map,movingCell);
		}
		if (play == 2){
			if(checkEmpty(n,map,movingCell->x,movingCell->y) == 0 || movingCell->energy < 80)
				printf ("Split Failed!");
			else{
				Cell * cell = addCell(movingCell->x,movingCell->y,movingCell->team);
				cell->canMove = true;
				cell = addCell(movingCell->x,movingCell->y,movingCell->team);
				cell->canMove = true;
				randomMove(n,map,cell);
				removeCell(movingCell);
				movingCell= cell;
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
				movingCell->canMove = false;
			}
			else{
				printf("Boost Energy Failed!");
			}
		}
		if (play == 4){
			int count=0;
			Cell* current = head;
			while (current != NULL){
				count++;
				current = current->next;
			}
			FILE *fptr = fopen("cells.mouj", "wb");
			if(fptr == NULL){
				printf("Save failed! please make sure file is closed");
				continue;
			}
			fwrite(&count,sizeof(int) , 1,fptr);
			Cell* writeCell = head;
			for(int i = 0; i < count; i++){
				fwrite(writeCell, sizeof(Cell), 1, fptr);
				writeCell = writeCell->next;
			}
			fclose(fptr);
			fptr = fopen("map.mouj","wb");
			
			if(fptr == NULL){
				printf("Save failed!\nplease make sure file is closed");
				continue;
			}
			fwrite(&n,sizeof(int),1,fptr);
			for2(n){
				fwrite(&map[i][j] , sizeof(Tile) , 1 ,fptr);
			}
			fwrite(&singlePlayer,sizeof(bool),1,fptr);
			fclose(fptr);
		}
		if (play == 5){
			Cell * current = head;
			head = NULL;
			while(current != NULL){
				Cell* rm = current;
				current = current->next;
				free(rm);
			}
			return;
		}
		bool endTurn = true;
		Cell* current = head;
		while(current!=NULL){
			if(current->canMove){
				endTurn = false;
				break;
			}
			current = current->next;
		}
		if(endTurn && !singlePlayer){
			current = head;
			while(current != NULL){
				if(current->team != movingCell->team) current->canMove = true;
				current = current->next;
			}
		}
		if(singlePlayer) movingCell->canMove = true;
	}
}

int main(){
	srand(time(NULL));
	while(1){
		clear
		printMenu
		int input = nextInt();
		if (input == Load){
			int count;
			FILE *fptr = fopen("cells.mouj", "rb");
			if(fptr == NULL){
				printf("Load failed!\nplease make sure file is closed");
				continue;
			}
			fread(&count,sizeof(int) , 1,fptr);
			for(int i = 0; i < count; i++){
				Cell * writeCell = (Cell*) malloc(sizeof(Cell));
				fread(writeCell, sizeof(Cell), 1, fptr);
				writeCell->next= NULL;
				if(head == NULL){
					head = writeCell;
				}
				else{
					Cell*current = head;
					
					while(current->next != NULL){
						current = current->next;
					}
					current->next = writeCell;
				}
			} 
			
			fclose(fptr);
			fptr = fopen("map.mouj","rb");
			if(fptr == NULL){
				printf("Load failed!\nplease make sure file is closed");
				continue;
			}
			int n;
			fread(&n,sizeof(int),1,fptr);
			Tile map[n][n];
			for2(n){
				fread(&map[i][j] , sizeof(Tile) , 1 ,fptr);
			}
			bool sp;
			fread(&sp,sizeof(bool),1,fptr);
			fclose(fptr);
			startGame(n,map,sp,true);
		}
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
	cell->energy = 40;
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

void SetConsoleColour(WORD* Attributes, DWORD Colour)
{
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout, &Info);
    *Attributes = Info.wAttributes;
    SetConsoleTextAttribute(hStdout, Colour);
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
	for ( int j=0;j<n;j+=2){ // khate 0
		if(map[0][j].type == Forbidden) red;
		if(map[0][j].type == Energy) yellow;
		if(map[0][j].type == Mitosis) green;
		if(map[0][j].type == Normal) blue;
		printf("       " , getSymbol(0,j,n,map));
		normal
		printf(" ");
		normal
		printf("       ");
		printf(" ");
	}
	printf("\n");
	for (int i=0;i<n;i++){
		for ( int j=0;j<n;j+=2){ // khate 1
			if(map[i][j].type == Forbidden) red;
			if(map[i][j].type == Energy) yellow;
			if(map[i][j].type == Mitosis) green;
			if(map[i][j].type == Normal) blue;
			printf("       " , getSymbol(i,j,n,map));
			normal
			printf(" ");
			if(i != 0)
			{
				if(map[i-1][j+1].type == Forbidden) red;
				if(map[i-1][j+1].type == Energy) yellow;
				if(map[i-1][j+1].type == Mitosis) green;
				if(map[i-1][j+1].type == Normal) blue;
				printf("_______",getSymbol(i-1,j+1,n,map));
				normal
			}
			else
			{
				normal
				printf("       ");
			}
			printf(" ");
		}
		printf("\n");
		for ( int j=0;j<n;j+=2){ // khate 2
			if(map[i][j].type == Forbidden) red;
			if(map[i][j].type == Energy) yellow;
			if(map[i][j].type == Mitosis) green;
			if(map[i][j].type == Normal) blue;
			printf("%s" , getSymbol(i,j,n,map));
			normal
			printf(" ");
			if(map[i][j+1].type == Forbidden) red;
			if(map[i][j+1].type == Energy) yellow;
			if(map[i][j+1].type == Mitosis) green;
			if(map[i][j+1].type == Normal) blue;
			printf("       " , getSymbol(i,j+1,n,map));
			normal
			printf(" ");
		}
		printf("\n");
		for ( int j=0;j<n;j+=2){ // khate 3
			if(map[i][j].type == Forbidden) red;
			if(map[i][j].type == Energy) yellow;	
			if(map[i][j].type == Mitosis) green;
			if(map[i][j].type == Normal) blue;
			printf("_______" , getSymbol(i,j,n,map));
			normal
			printf(" ");
			if(map[i][j+1].type == Forbidden) red;
			if(map[i][j+1].type == Energy) yellow;
			if(map[i][j+1].type == Mitosis) green;
			if(map[i][j+1].type == Normal) blue;
			printf("%s" , getSymbol(i,j+1,n,map));
			normal
			printf(" ");
		}
		printf("\n");
		for ( int j=0;j<n;j+=2){ // khate 4
			if(i != n-1){
				if(map[i+1][j].type == Forbidden) red;
				if(map[i+1][j].type == Energy) yellow;
				if(map[i+1][j].type == Mitosis) green;
				if(map[i+1][j].type == Normal) blue;
				printf("       " , getSymbol(i+1,j,n,map));
				normal
				printf(" ");
			}
			else
			{
				normal
				printf("       " , getSymbol(i+1,j,n,map));
				printf(" ");
			}
			if(map[i][j+1].type == Forbidden) red;
			if(map[i][j+1].type == Energy) yellow;
			if(map[i][j+1].type == Mitosis) green;
			if(map[i][j+1].type == Normal) blue;
			printf("       " , getSymbol(i,j+1,n,map));
			normal
			printf(" ");
		}
		printf("\n");

	}
	if(n%2 == 0)
	{
		
		for ( int j=0;j<n;j+=2){ // khate 0
		normal
		printf("       ");
		printf(" ");
		if(map[n-1][j+1].type == Forbidden) red;
		if(map[n-1][j+1].type == Energy) yellow;
		if(map[n-1][j+1].type == Mitosis) green;
		if(map[n-1][j+1].type == Normal) blue;
		printf("_______" , getSymbol(n-1,j+1,n,map));
		normal
		printf(" ");
		
		}
	}
		printf("\n");
		SetConsoleColour(&Attributes, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
}

char * getSymbol(int x , int y,int n,Tile map[n][n]){
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
	if(map[x][y].type == Forbidden)return "       ";
//	if(map[x][y].type == Mitosis)return "Mit";
//	if(map[x][y].type == Energy)return "Eng";
	return "       ";
}
	
Cell* showList(int n){
	Cell* current = head;
	int i=1;
	while (current != NULL){
		if(current->canMove){
			printf ("%d) %s (%d,%d) | Energy: %d\n",i,current->name,current->y,n-1-current->x,current->energy);
			current->num = i;
			i++;
		}
		else{
			current->num = 0;
		}
		current = current->next;
	}
	int chooseCell = nextInt();	
	Cell* find = head;
	while (chooseCell != find->num){
		find = find->next;
	}
	if(chooseCell == find->num)
	return find;
	printf("Wrong input!");
	return showList(n);
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
		movingCell->canMove = false;
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

void removeCell (Cell* movingCell){
	Cell* current = head;
	if (movingCell == head)
	{
		head = head->next;
		free(movingCell);
		return;
	}
	while (current->next != movingCell){
		current = current->next;
	}
	if (current->next->next == NULL) 
		current->next = NULL;
	else
		current->next = current->next->next;
	free(movingCell);
}

