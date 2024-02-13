
//Given a sequence of N positive integers. The largest possible number of S is required, such that:

//There must be X terms at the beginning of the sequence that have a sum of S.
//There must be Y terms at the end of the sequence that have a sum of S.
//Let X+Y <= N, i.e. the terms we add at the two ends do not overlap.
//Note that the problem always has a solution (for Σ=0 and X=Y=0).

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int f, l, i, n, result = 0, sumX, sumY;

	scanf("%d", &n);

	int array[n];

	for (i = 0; i < n; i++) {
		 scanf("%d", &array[i]);
	}

	f = 0;
	l = n - 1;
	sumX = array[f];
	sumY = array[l];

	while (f < l) {
		if (sumX == sumY)
			result = sumX;
		if (sumX <= sumY) {
			f++;
			sumX += array[f]; 
		}
		else {
			l--;
			sumY += array[l];
		}
	}

	printf("%d\n", result);
	return 0;
}