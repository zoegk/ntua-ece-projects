
//Write a program that reads a natural number N > 0 
//and prints the largest natural number whose factorial does not exceed N.

#include <iostream>

using namespace std;

int main() {
    unsigned int N;
    cin >> N;

    unsigned int factorial = 1;
    unsigned int largest = 1;

    while (factorial <= N) {
        largest++;
        factorial *= largest;
    }

    cout << largest - 1 << endl;

    return 0;
}
