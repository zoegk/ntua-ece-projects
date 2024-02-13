
//Write a program that reads two natural numbers and checks whether their product is a four-digit number or not.

#include <iostream>

using namespace std;

int main() {
    int M, N;
    cin >> M >> N;
    
    int product = M * N;
    
    if (product >= 1000 && product <= 9999) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    
    return 0;
}
