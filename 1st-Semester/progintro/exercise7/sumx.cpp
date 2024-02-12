
//Given a sequence of n distinct positive integers a_1, a_2, ..., a_n, 
//with values between 1 and 1,000,000. An integer x is also given. 
//Write a program that finds the number of pairs (a_i, a_j), where 1 ≤ i < j ≤ n and a_i + a_j = x.

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    int count = 0;
    int arr[n];

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    sort(arr, arr + n);

    int left = 0, right = n - 1;

    while (left < right) {
        if (arr[left] + arr[right] == x) {
            count++;
            left++;
            right--;
        } else if (arr[left] + arr[right] < x) {
            left++;
        } else {
            right--;
        }
    }

    cout << count << endl;

    return 0;
}
