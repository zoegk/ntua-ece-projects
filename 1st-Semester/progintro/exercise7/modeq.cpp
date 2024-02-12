
//Write a program that accepts three natural numbers and checks if the remainder of their division by 42 is equal.

#include <iostream>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    if (a % 42 == b % 42 && b % 42 == c % 42) {
        cout << a % 42 << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
