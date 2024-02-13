
//Write a program that reads two natural numbers and prints how many of them are even.

#include <iostream>

using namespace std;

int main() {

    int num1, num2;
    cin >> num1 >> num2;


    int even_count = 0;
    if (num1 % 2 == 0)
        even_count++;
    if (num2 % 2 == 0)
        even_count++;


    cout << even_count << endl;

    return 0;
}
