
//Write a program that reads a positive natural number N 
//and checks if its square ends in 24 (written in the decimal number system).

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int N;
    cin >> N;
    int square = N * N;
    if (square % 100 == 24) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}
