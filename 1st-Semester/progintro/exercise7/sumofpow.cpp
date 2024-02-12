
//Write a program that reads a natural number N and prints the number of natural numbers 
//not exceeding N that can be written as the sum of a power of 2, a power of 3, and a power of 5 
//(eg 42 = 16 + 1 + 25 = 2^4 + 3^0 + 5^2).

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    const int MAX_N = 5000000; 
    int powers_of_2[23], powers_of_3[15], powers_of_5[10];
    int N, j, k, l, sum, count = 0;

    cin >> N;

    int sums[MAX_N + 1] = {0};

    for (int i = 0; i < 23; i++) {
        powers_of_2[i] = pow(2, i);
    }

    for (int i = 0; i < 15; i++) {
        powers_of_3[i] = pow(3, i);
    }

    for (int i = 0; i < 10; i++) {
        powers_of_5[i] = pow(5, i);
    }

    for (j = 0; j < 23; j++) {
        for (k = 0; k < 15; k++) {
            for (l = 0; l < 10; l++) {
                sum = powers_of_2[j] + powers_of_3[k] + powers_of_5[l];
                if (sum > N)
                    break;
                else if (sum <= N && sums[sum] == 0) {
                    sums[sum]++;
                    count++;
                }
            }
        }
    }

    cout << count << endl;

    return 0;
}
