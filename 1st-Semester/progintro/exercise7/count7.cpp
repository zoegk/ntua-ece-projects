
//Write a program that accepts a two-digit natural number and finds how many of its digits are equal to 7.

#include <iostream>
using namespace std;

int main() {
    int number;
    cin >> number;

    int count = 0;
    if (number / 10 == 7) {
        count++;
    }
    if (number % 10 == 7) {
        count++;
    }

    cout << count << endl;

    return 0;
}
