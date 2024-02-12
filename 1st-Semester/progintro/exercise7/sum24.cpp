
//Write a program that reads two natural numbers and checks if their sum ends in 42 (written in the decimal number system).

#include <iostream>

using namespace std;

int main() {
    int M, N;
    cin >> M >> N;

    int sum = M + N;

    if (sum % 100 == 42) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
