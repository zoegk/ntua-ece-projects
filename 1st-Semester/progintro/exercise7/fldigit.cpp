
//Write a program that reads a six-digit natural number N and a digit D, 
//and finds whether the first and last digits of N are equal to D.

#include <iostream>

using namespace std;

int main() {

    int N, D;
    cin >> N >> D;

    int firstDigit = N / 100000;
    int lastDigit = N % 10;

    if (firstDigit == D && lastDigit == D) {
        cout << "yes" << std::endl;
    } else {
        cout << "no" << std::endl;
    }

    return 0;
}
