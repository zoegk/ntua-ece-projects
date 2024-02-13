#include <iostream>
#include <cmath>

using namespace std;

int sumOfFourthPowers(int num) {
    int sum = 0;
    while (num > 0) {
        int digit = num % 10;
        sum += pow(digit, 4);
        num /= 10;
    }
    return sum;
}

int main() {
    cout << "Four-digit integers equal to the sum of their digits raised to the fourth power:" << endl;
    
    for (int i = 1000; i < 10000; ++i) {
        if (i == sumOfFourthPowers(i)) {
            cout << i << " ";
        }
    }
    
    cout << endl;

    return 0;
}
