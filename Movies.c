#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 300
#define LISTSIZE 9
#define STRINGSIZE 100

char table[TABLESIZE][4][STRINGSIZE];

void clearTable(){
	for(int i = 0; i < TABLESIZE; i++){
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < STRINGSIZE; k++){
				table[i][j][k] = 0;
			}
		}
	}
}

void readTable(){
	FILE *movies;
	int column, character, row = -1;
	char input;
	movies = fopen("Movies.txt", "r");
	do{
		row++;
		input = getc(movies);
		column = character = 0;
		while(input != 10 && input != -1){
			if(input == 9){
				column++;
				character = 0;
				input = getc(movies);
			}
			if(input != 10){
				table[row][column][character] = input;
				character++;
				input = getc(movies);
			}
		}
	}while(input != -1);
	fclose(movies);
}

int compareString(char string1[STRINGSIZE], char string2[STRINGSIZE]){
	char character1, character2;
	for(int character = 0; character < STRINGSIZE; character++){
		character1 = string1[character];
		character2 = string2[character];
		if(character1 < 91) character1 += 32;
		if(character2 < 91) character2 += 32;
		if(character1 != character2) return 1;
		else if(character == STRINGSIZE - 1) return 0;
	}
	return 1;
}

int allMovies(int start){
	char input;
	system("cls");
	printf("MOVIES\n\nall movies\n");
	for(int row = start; row < start + LISTSIZE; row++){
		if(table[row][0][0] != 0) printf("\n%d %s", row + 1, table[row][0]);
	}
	printf("\n\nh: home");
	if(start > 0) printf(", n: previous page");
	if(table[start + LISTSIZE][0][0] != 0) printf(", m: next page");
	printf(", q: quit\ninput: ");
	while(1){
		while(getchar() != '\n');
		input = getchar();
		if(input == 'h') return 0;
		else if(input == 'n' && start > 0) return allMovies(start - LISTSIZE);
		else if(input == 'm' && table[start + LISTSIZE][0][0] != 0) return allMovies(start + LISTSIZE);
		else if(input == 'q') return 1;
		printf("input not valid. Try again\ninput: ");
	}
}

int showAll(){
	char input;
	system("cls");
	printf("MOVIES\n\nshow all...\n\n1. movies\n2. directors\n3. actors\n\nh: home, q: quit\ninput: ");
	while(1){
		while(getchar() != '\n');
		input = getchar();
		if(input == 'h') return 0;
		else if(input == 'q') return 1;
		else if(input == '1') return allMovies(0);
		printf("input not valid. Try again\ninput: ");
	}
}

int search(){
	int row = -1, end = 0;
	char input, sInput[STRINGSIZE];
	for(int i = 0; i < STRINGSIZE; i++) sInput[i] = 0;
	system("cls");
	printf("MOVIES\n\nsearch: ");
	while(getchar() != '\n');
	gets(sInput);
	do{
		row++;
		if(compareString(table[row][0], sInput) == 0){
			system("cls");
			printf("MOVIES\n\nTitle:\t\t%s\nYear:\t\t%s\nDirector:\t%s\nActor:\t\t%s",
				table[row][0], table[row][1], table[row][2], table[row][3]);
			end = 1;
		}else if(table[row][0][0] == 0){
			printf("\nno match found");
			end = 1;
		}
	}while(end == 0);
	printf("\n\nh: home, s: search, q: quit\ninput: ");
	while(1){
		while(getchar() != '\n');
		input = getchar();
		if(input == 'h') return 0;
		else if(input == 's') return(search());
		else if(input == 'q') return 1;
		printf("input not valid. Try again\ninput: ");
	}
}	
	
int main(){
	int end = 0;
	char input;
	clearTable();
	readTable();
	while(end == 0){
		system("cls");
		printf("MOVIES\n\nHome\n\na: show all..., s: search, q: quit\ninput: ");
		input = getchar();
		while(input != 'a' && input != 's' && input != 'q'){
			printf("input not valid. Try again\ninput: ");
			while(getchar() != '\n');
			input = getchar();
		}
		if(input == 'a' && showAll() == 1) end = 1;
		else if(input == 's' && search() == 1) end = 1;
		else if(input == 'q') end = 1;
		while(getchar() != '\n');
	}
    return 0;
}