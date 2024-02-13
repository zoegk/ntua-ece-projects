
//A business is to open two stores on a major shopping street. 
//The street consists of N blocks and each block i yields the firm cedar a_i (where a_i is a positive integer) 
//if block i is covered by a shop. Each store covers K consecutive blocks. If a square i is covered by both stores, 
//the profit it brings to the business remains a_i. We are asked to calculate the maximum profit the company can make by 
//opening two stores each covering K consecutive blocks.

#include <iostream>
using namespace std;

int main() {

    int N, K, i, maxSum = 0;

    cin >> N >> K;

    int prices[N];
    int sum[N + 1 - K];
    int max[N - K];

    for (i = 0; i < N; i++) {
        cin >> prices[i];
    }

    for (i = 0; i < N + 1 - K; i++) {
        sum[i] = 0;
    }

    for (i = 0; i < K; i++) {
        sum[0] += prices[i];
    }
    for (i = 1; i < N - K + 2; i++) {
        sum[i] = sum[i - 1] - prices[i - 1] + prices[i + K - 1];
    }

    max[0] = sum[0];
    for (i = 1; i < N - K; i++) {
        if (max[i - 1] < sum[i])
            max[i] = sum[i];
        else
            max[i] = max[i - 1];
    }

    for (i = K; i < N - K + 1; i++) {
        int tmp = sum[i] + max[i - K];
        if (tmp > maxSum) {
            maxSum = tmp;
        }
    }

    cout << maxSum << endl;

    return 0;
}
