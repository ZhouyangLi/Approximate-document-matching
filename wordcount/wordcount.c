#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

FILE *fp;
FILE *fp1;
FILE *fp2;
int row, col;

/* get roughly the number of words in the textfile */
int
getWN(FILE *fp) {
	char k;
	int count = 0;
	while ((k = getc(fp)) != EOF) {
		if (!isalnum(k)) {
			count ++;
		}
	}
	return count;
} 


/* transform the textfile into a 2D array, each row is one word */
void
text2words(char array[row][col]) {
	char cur;
	int i = 0;
	int j = 0;
	while ((cur = getc(fp2)) != EOF) {
		if (isalnum(cur)) {
			if (isupper(cur)) {
				cur = tolower(cur);
			}
			array[i][j] = cur;
			j++;
		}
		else {
			i++;
			cur = getc(fp2);
			
			while (!isalnum(cur)) {
				if (cur == EOF) 
					break;
				cur = getc(fp2);
			}

			if (cur == EOF) 
				break;

			j = 0;
			if (isupper(cur)) {
				cur = tolower(cur);
			}
			array[i][j] = cur;
			j++;

		}
	}
}

/* struct a occNode that contains both the word and its occurrence count */
typedef struct {
	char* word;
	int oc;
} occNode;

/* compare two string using the strcmp method */
int 
compare (const void *pa, const void *pb)
{
	return strcmp(pa, pb);
}

void
main (int argc, char **argv) 
{

	if(argc < 2) {
		printf("Not Enough Arguments! \n");
		return;
	} 

	else {
		fp = fopen(argv[1], "r");
		fp1 = fopen(argv[1], "r");
		fp2 = fopen(argv[1], "r");
		col = 20;
		row = getWN(fp1);
		char arr[row][col];
		/* initialize the array of words to null */
		for (int i=0; i<row; i++) {
			for (int j=0; j<col; j++) {
				arr[i][j] = NULL;
			}
		}

		text2words(arr);

		/* sort the array to make same words cluster */
		qsort(arr, row, col, compare);

		/* count the occurrence of each word and store the word and its occurrence
		in an array of occNode */
		occNode list[row];
		int curI = 0;
		list[0].word = arr[0];
		list[0].oc=1;
		for (int i=1; i<row; i++) {
			if (strcmp(list[curI].word, arr[i])==0) {
				list[curI].oc++;
			}
			else {
				curI++;
				list[curI].word=arr[i];
				list[curI].oc=1;
			}
		}
		
		/* store the 10 most frequent words and its occurrence in an array of occNode
		in the order requested. */
		occNode list_t[10];
		occNode max;
		max.word = "";
		max.oc = 0;
		occNode temp;

		for (int u = 9; u >= 0; u--) {
			for (int l = 1; l < curI+1; l++) {
					if (list[l].oc > max.oc) {
						temp = list[l];
						list[l] = max;
						max = temp;
						//printf("%s \n", temp.word);
					 } else if (list[l].oc == max.oc) {
						if (strcmp (list[l].word, max.word) > 0) {
							temp = list[l];
							list[l] = max;
							max = temp;
						} 
					}
				 
			}			

			list_t[u] = max;

			max.word = "";
			max.oc = 0;
			

		} 
		
		/* print 10 most frequent words and their occurrence */
		
		for (int k = 0; k<10; k++) {
			printf("%d %s \n",list_t[k].oc, list_t[k].word);
		} 

		
	}

}