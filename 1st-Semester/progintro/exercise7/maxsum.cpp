
//Given a sequence of N integers (which can be negative, positive or even zero). 
//Write a program that will calculate the maximum sum of (any) consecutive terms of the sequence.

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int maxSubarraySum(const vector<int>& arr) {
    int max_sum = INT_MIN;
    int current_sum = 0;
    
    for (int num : arr) {
        current_sum = max(num, current_sum + num);
        max_sum = max(max_sum, current_sum);
    }
    
    return max_sum;
}

int main() {
    int N;
    cin >> N;
    
    vector<int> sequence(N);
    for (int i = 0; i < N; ++i) {
        cin >> sequence[i];
    }
    
    cout << maxSubarraySum(sequence) << endl;
    
    return 0;
}
