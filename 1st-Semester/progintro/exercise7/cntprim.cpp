
//Write a program that reads a natural number N and prints the number of prime numbers not exceeding N.

#include <iostream>

using namespace std;

int main() {

    int N;
    cin >> N;

    bool isprime[5000001] = {false};

    // Sieve of Eratosthenes algorithm to mark non-prime numbers
    for (int i = 2; i * i <= N; ++i) {
        if (!isprime[i]) {
            for (int j = i * i; j <= N; j += i) {
                isprime[j] = true;
            }
        }
    }

    int countprimes = 0;
    for (int i = 2; i <= N; ++i) {
        if (!isprime[i]) {
            countprimes++;
        }
    }

    cout << countprimes << endl;

    return 0;
}
