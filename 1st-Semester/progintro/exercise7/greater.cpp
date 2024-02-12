
//Write a program that reads two natural numbers and prints the larger one.

#include <iostream>

using namespace std;

int main() {

    int M, N;
    cin >> M >> N;

    cout << (M > N ? M : N) << endl;

    return 0;
}
