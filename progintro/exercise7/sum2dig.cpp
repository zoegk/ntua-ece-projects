
//Write a program that reads a natural number N >= 10 and prints the sum of its last two digits.

//For example, if N=4217, the number 8 should be printed (because 1+7=8).

#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    int last_digit = N % 10;
    int second_last_digit = (N / 10) % 10;

    int sum = last_digit + second_last_digit;

    cout << sum << endl;

    return 0;
}
