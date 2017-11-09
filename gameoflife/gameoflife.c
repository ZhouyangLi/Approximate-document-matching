#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
FILE *fp1;
int row, col; 


/* tick once and return the array of life after tick */
void
tick(char array[row][col], char arrayc[row][col]){
	for (int i=0; i<row; i++) {
			for (int j=0; j<col; j++) {
				arrayc[i][j]=array[i][j];
			}
		}
	
	for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			int count = 0;
			if (array[(i+1)%row][j]=='x') {
				count ++;
			}
			if (array[(i-1)%row][j]=='x') {
				count ++;
			}
			if (array[i][(j+1)%col]=='x') {
				count ++;
			}
			if (array[i][(j-1)%col]=='x') {
				count ++;
			}
			if (array[(i+1)%row][(j+1)%col]=='x') {
				count ++;
			}
			if (array[(i-1)%row][(j+1)%col]=='x') {
				count ++;
			}
			if (array[(i+1)%row][(j-1)%col]=='x') {
				count ++;
			}
			if (array[(i-1)%row][(j-1)%col]=='x') {
				count ++;
			}

			if (array[i][j]=='x' && (count<2 || count>3)) {
				arrayc[i][j]='.';
			}
			else if (array[i][j]=='.' && count==3) {
				arrayc[i][j]='x';
			}
		}
	}
	
	for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			array[i][j]=arrayc[i][j];
		}
	}

}

/* Get the number of row and number of column of the array */
void
getArrayD(FILE *fp) {
	char i;
	while ((i = getc(fp)) != '\n') {
			col++;
		}
	row++;
	while ((i = getc(fp)) != EOF) {
		if (i=='\n') {
			row++;
		}
	}
}

/* Transform the universe of life into a 2d array */
void
createArray(FILE *fp, char arr[row][col]) {
	//getArrayD(fp1);
	//array = (char**) malloc(row*col*sizeof(char));
	//array[row][col] = {{0}};
	//char** arr = (char **) malloc(row*col*sizeof(char));=
	for (int i=0; i<row; i++) {
		for (int j=0; j<col; j++) {
			char k = getc(fp);
			//printf("%c", k);
			if (i!=0&&j==0) {
				k = getc(fp);
			}
		
				arr[i][j]=k;
			
				//printf("i is: %d, j is:%d, sign is:%c \n", i, j, arr[i][j]);
			
		}
	}
}

void
main(int argc, char **argv)
{

	if(argc < 3) {
		printf("Not Enough Arguments! \n");
		return;
	} 

	else {
		fp = fopen(argv[1], "r");
		fp1 = fopen(argv[1], "r");
		getArrayD(fp1);
		char array[row][col]; //added
		createArray(fp, array);
		char arrayc[row][col];
		int play = atoi(argv[2]);
		for (int k = 0; k<play; k++) {
			tick(array, arrayc);
		}
		/* print the array when the tick is finished */
		for (int i=0; i<row; i++) {
			for (int j=0; j<col; j++) {
				printf("%c", array[i][j]);
			}
			printf("\n");
		}
	}

}



