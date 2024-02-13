
//Given a sequence of N positive integers. I pick two of them and calculate their 
//sum plus their distance within the sequence. For example, let N=6 and the numbers in the sequence are:

//7 3 9 8 2 7
//If I choose 3 and 8, their distance is 2 (because 3 is the second term of the 
//sequence and 8 is the fourth, so 4-2=2), so the sum I calculate is 3+8+2= 13.

//Write a program that, given such a sequence, finds the maximum possible value of this sum.

//Attention: I must select two different terms of the sequence, not the same term twice. 
//This does not preclude choosing the same number if it appears twice in the sequence.

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int N, input, a, b, i, ptr = 0, max = 0;

	scanf("%d", &N);

	scanf("%d %d", &a, &b);
	max = a + b + 1;

	for (i = 2; i < N; i++) {
		scanf("%d", &input);

		if ((input + b + 1) > (input + a + i - ptr)) {

			if (max < input + b + 1)
				max = input + b + 1;

			a = b;
			b = input;
			ptr = i-1;
		}

		else {
			if (max < input + a + i - ptr)
				max = input + a + i - ptr;

			b = input;

		}


	}

	printf("%d\n", max);


	return 0;
}