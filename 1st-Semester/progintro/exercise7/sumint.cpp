
//Given a sequence a_1, ..., a_N consisting of N positive integers and a positive integer K. 
//We are asked to calculate the number of intervals a_i, ..., a_j of the sequence, 
//with 1<=i<=j<=N, for which the sum of the terms does not exceed K, i.e. we have that \sum_{p=i}^j a_p <= K.

#include <iostream>

using namespace std;

int main() {
    int numElements;
    long long int threshold;
    cin >> numElements >> threshold;

    long long int prefixSum[numElements + 1], count = 0;
    prefixSum[0] = 0;

    for (int i = 1; i <= numElements; i++) {
        int x;
        cin >> x;
        prefixSum[i] = prefixSum[i - 1] + x;
    }

    int left = 1, right = 1;
    for (left = 1; left <= numElements; left++) {
        while (right <= numElements && prefixSum[right] - prefixSum[left - 1] <= threshold) {
            right++;
        }
        count += right - left;
    }

    cout << count << endl;

    return 0;
}
