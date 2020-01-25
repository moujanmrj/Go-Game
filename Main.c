#include "includes.h"
#include "funcs.h"

cell* head = NULL;

void startGame(int n,int map[n][n],bool singlePlayer){
	
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
			tile arr[n][n];
			for (int i=0;i<n;i++){
				for (int j=0;j<n;j++){
					unsigned char temp;
					fread(&temp, sizeof(unsigned char),1,fp);
					arr[i][j].type = toInt(temp);
					arr[i][j].energy = 100;
				}
			}
			fclose(fp);
			startGame(n, map, input==Sp);
		}
		if (input == Exit){
			return 0;
		}
	}
}


