
//Given a sequence a_1, ..., a_N consisting of N positive integers. 
//It is requested to determine if there are positions i, j, with i < j, 
//such that a_i + a_j = a_{i+1} + ... + a_{j-1}, i.e. the sum of the numbers 
//in positions i and j of sequence to be equal to the sum of the numbers 
//in positions from i+1 to j-1. If there are many such pairs of positions i, j in the sequence, 
//it is requested to calculate the maximum position j for which the above relation is valid.

#include <iostream>

using namespace std;

int main() {
    int num_elements;
    cin >> num_elements;

    int sequence[100000];
    for (int index = 0; index < num_elements; index++) {
        cin >> sequence[index];
    }

    int max_position = 0;
    for (int j = 0; j < num_elements - 2; j++) {
        int k = j + 1;
        int sum = 0;
        while (k < num_elements) {
            sum += sequence[k];
            k++;
            if (sum == sequence[k] + sequence[j] && k + 1 > max_position) {
                max_position = k + 1;
                break;
            } else if (sum == sequence[k] + sequence[j]) {
                break;
            }
        }
    }

    cout << max_position << endl;

    return 0;
}
