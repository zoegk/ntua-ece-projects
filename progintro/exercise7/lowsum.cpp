
//Given a sequence of N different integers (negative and positive) in ascending order, 
//write a program that will find two different numbers in the sequence whose sum is as close to 0 as possible.

#include <iostream>
using namespace std;

int main() {
    int N, sum1, sum2, begin1, begin2, minSum, sum;
    int j = 0;

    cin >> N;

    int arr[N];

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    sum1 = arr[0];
    sum2 = arr[N - 1];
    begin1 = 0;
    begin2 = N - 1;
    minSum = sum1 + sum2;

    while (j < N) {
        sum = sum1 + sum2;
        if (abs(sum) < abs(minSum)) {
            minSum = sum;
        }
        if (sum > 0) {
            begin2--;
            if (begin2 == begin1) {
                begin2--;
            }
            sum2 = arr[begin2];
        }
        else if (sum < 0) {
            begin1++;
            if (begin1 == begin2) {
                begin1++;
            }
            sum1 = arr[begin1];
        }
        else {
            break;
        }
        j++;
    }

    cout << minSum << endl;

    return 0;
}
