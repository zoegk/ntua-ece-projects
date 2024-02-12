
//Write a program that reads a natural number N and checks if it is a multiple of 7 but not a multiple of 6.

#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    if (N % 7 == 0 && N % 6 != 0) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}
