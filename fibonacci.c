/*
 * Created By: Thomas Osgood
 *
 * Print out 'n' fibonacci numbers iteratively.
 *
 * to compile: gcc -o fibonacci fibonacci.c
 */

#include <stdio.h>

void fibGen(int n);

int main(int argc, char*argv[]) {
	fibGen(7);
	return 0;
}

void fibGen(int n) {
	if (n < 0) {
		printf("Invalid Input To Function\n");
		return;
	}

	int f_new = 0;
	int f_old1 = 0;
	int f_old2 = 0;
	int i = 0;

	for (i=0 ; i<n ; i++) {
		if ( i == 0 )
			f_new = 0;
		else if ( i == 1 ) {
			f_new = 1;
			f_old1 = f_new;
		} else {
			f_new = f_old1 + f_old2;
			f_old2 = f_old1;
			f_old1 = f_new;
		}
		printf("%d ", f_new);
	}
	printf("\n");
}
