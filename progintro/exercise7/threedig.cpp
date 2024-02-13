
// Write a program that reads a natural number N and checks whether it is a three-digit number or not.

#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    if (N >= 100 && N <= 999) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}
