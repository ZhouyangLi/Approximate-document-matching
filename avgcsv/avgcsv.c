#include <stdio.h>
#include <stdlib.h>

FILE *fp;
FILE *fp1;

/* get the number of colomns in the file */
int
getColCount(FILE * fp) {
	int ccount = 0;
	char i;
	while ((i = getc(fp)) != '\n') {
		if (i == ';') {
			ccount++;
		}
	}
	ccount++;
	return ccount;
}


int col = 0;
int rowc = 0;

/*calculate the sum of each row and store the result in a int array */
int * 
sum(FILE * fp) {
	
	col = getColCount(fp);
	int * array = (int *) malloc(col);
	int c = 0;
	int result = 0;
	char cur;
	while ((cur = getc(fp1)) != EOF) {
		if (cur == ';') {
			array[c] += result;
			c++;
			result = 0;
		}
		else if (cur == '\n') {
			array[c] += result;
			c = 0;
			result = 0;
			rowc ++;
		}
		else {
			result = result*10 + (cur-48);
			
		}

	}

	return array;
}

void
main(int argc, char **argv)
{

	if(argc < 2) {
		printf("No File Given! \n");
		return;
	} 

	else {
		fp = fopen(argv[1], "r");
		fp1 = fopen(argv[1], "r");
		int * r = sum(fp);
		for (int l = 0; l < col-1; l++) {
			float f = (float) r[l]/rowc;
			printf("%.1f;", f);
		}
		float last = (float) r[col-1]/rowc;
		printf("%.1f \n", last);
	}

}