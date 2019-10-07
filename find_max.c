/*
 * Created By: Thomas Osgood
 *
 * Print out max value in an unsorted array.
 *
 * to compile: gcc -o Question4 Question4.c
 */

#include <stdio.h>

int arrMax (int *arr, size_t arr_size);

int main(int argc, char *argv[]) {
	int tstArr[] = { 10 , 20 , 5 , 26 };
	size_t tstArr_s = sizeof(tstArr) / sizeof(tstArr[0]);
	printf("Max Val: %d\n", arrMax(tstArr, tstArr_s));
	return 0;
}

int arrMax (int *arr, size_t arr_size) {
	int max_val = 0;
	int i = 0;

	max_val = arr[0];
	for (i=0 ; i<(int)arr_size ; i++) {
		if ( arr[i] > max_val )
			max_val = arr[i];
	}

	return max_val;
}

