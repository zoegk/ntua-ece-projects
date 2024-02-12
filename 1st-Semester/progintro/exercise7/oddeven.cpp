
//Given a sequence a_1, ..., a_N consisting of N positive integers. 
//It is requested to calculate the range of the longest interval in the sequence 
//in which the number of even numbers is equal to the number of odd numbers.

#include <iostream>

using namespace std;

const int MAXN = 1e6 + 5;

int main() {
    int num_elements;
    cin >> num_elements;

    int sequence[MAXN], prefix_sum[MAXN + 1], first_occurrence[2 * MAXN]; // first_occurrence[i + MAXN] -> first occurrence of i, initialized to 0
    first_occurrence[MAXN] = 0;
    int longest_interval = 0;

    for (int i = 1; i <= num_elements; i++) {
        int temp;
        cin >> temp; // Read input without array
        if (temp % 2 == 0) sequence[i] = 1;
        else sequence[i] = -1;
        prefix_sum[i] = prefix_sum[i - 1] + sequence[i]; // Create prefix sum array for modified array
        if (first_occurrence[prefix_sum[i] + MAXN] == 0 && prefix_sum[i] != 0) { // if I haven't seen prefix_sum[i] before
            first_occurrence[prefix_sum[i] + MAXN] = i; // first occurrence of prefix_sum[i] is i
        }
        else { // if I have seen prefix_sum[i] before
            longest_interval = max(longest_interval, i - first_occurrence[prefix_sum[i] + MAXN]); // take largest possible subarray with same prefix sum
        }
    }

    cout << longest_interval << endl;

    return 0;
}
