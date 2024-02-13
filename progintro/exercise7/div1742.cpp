
//Write a program that reads two natural numbers, A and B, and finds 
//if one of them is divisible by 17 and at the same time the other is divisible by 42

#include <iostream>

using namespace std;

int main() {
    int A, B;
    cin >> A >> B;

    if ((A % 17 == 0 && B % 42 == 0) || (A % 42 == 0 && B % 17 == 0)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
