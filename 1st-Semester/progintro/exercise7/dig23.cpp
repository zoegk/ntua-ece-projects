
//Write a program that reads two natural numbers A and B, calculates their product, and prints its two penultimate digits.

//For example, if A=4217 and B=1742, it is A*B=7346014 and the penultimate two digits should be printed: 01.

#include <iostream>

using namespace std;

int main() {
    int A, B;
    cin >> A >> B;

    long long product = A * B;

    int penultimateDigits = (product / 10) % 100;

    if (penultimateDigits < 10) {
        cout << '0';
    }
    cout << penultimateDigits << endl;

    return 0;
}
