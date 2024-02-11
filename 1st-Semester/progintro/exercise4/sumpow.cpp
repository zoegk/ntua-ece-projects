#include <iostream>
#include <cmath>

using namespace std;

unsigned long long calculatePower(int digit, int power) {
    unsigned long long result = 1;
    for (int i = 0; i < power; i++) {
        result *= digit;
    }
    return result;
}

int main() {
    int N;

    cin >> N;

    unsigned long long powers[10];
    for (int i = 0; i < 10; i++) {
        powers[i] = calculatePower(i, N);
    }

    for (int a = 0; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            for (int c = 0; c <= 9; c++) {
                for (int d = 0; d <= 9; d++) {
                    for (int e = 0; e <= 9; e++) {
                        for (int f = 0; f <= 9; f++) {
                            for (int g = 0; g <= 9; g++) {
                                for (int h = 0; h <= 9; h++) {
                                    unsigned long long num = (a * 10000000ULL) + (b * 1000000ULL) + (c * 100000ULL) +
                                                              (d * 10000ULL) + (e * 1000ULL) + (f * 100ULL) +
                                                              (g * 10ULL) + h;

                                    unsigned long long sum = powers[a] + powers[b] + powers[c] + powers[d] +
                                                              powers[e] + powers[f] + powers[g] + powers[h];

                                    if (num == sum)
                                        cout << num << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
