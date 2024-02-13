
//Write a program that reads a natural number and finds if it has an even number of digits.

#include <iostream>
#include <string>

using namespace std;

int main() {
    string num;
    cin >> num;

    if (num.size() % 2 == 0) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
