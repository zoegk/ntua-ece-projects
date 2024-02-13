
//Write a program that reads a natural number N and prints the highest power of 2 that divides N.

#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;

    int power = 0;
    while (N % 2 == 0) {
        N /= 2;
        power++;
    }

    cout << power << endl;

    return 0;
}
