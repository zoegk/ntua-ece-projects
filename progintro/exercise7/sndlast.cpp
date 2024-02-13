
//Write a program that reads a natural number N > 10 and prints the second to last digit.

#include <iostream>
using namespace std;

int main() {
 
    int N;
    cin >> N;

    int digit = (N / 10) % 10;

    cout << digit << endl;

    return 0;
}