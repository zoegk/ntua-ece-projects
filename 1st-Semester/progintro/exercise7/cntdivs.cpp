
//Write a program that reads a natural number N
//and print the number of positive natural numbers not exceeding N 
//that have non-trivial common divisors with N. (Non-trivial divisors are greater than 1.)

#include <iostream>

using namespace std;

int calculate_gcd(int num1, int num2) {
    while (num1 > 0 && num2 > 0) {
        if (num1 > num2)
            num1 = num1 % num2;
        else
            num2 = num2 % num1;
    }
    return num1 + num2;
}

int main() {
    int N, i, j, temp1, temp2, count;
    count = 0;

    cin >> N;

    int array[N + 1];

    for (i = 0; i <= N; i++) {
        array[i] = i;
    }

    for (j = 2; j <= N; j++) {
        temp1 = array[j];
        temp2 = calculate_gcd(temp1, N);
        if (temp2 > 1)
            count++;
    }
    cout << count << endl;

    return 0;
}
