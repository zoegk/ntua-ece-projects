
//Given a sequence consisting of N positive integers. 
//It is asked to find the smallest number in the sequence 
//which exactly divides all the numbers preceding it in the sequence.

//Obviously the number that appears first in the sequence exactly divides 
//all its predecessors (because it has no predecessor). 
//So if the sequence is not empty, there is always a solution to the problem.

#include <iostream>

using namespace std;

int main() {
    int size;
    cin >> size;

    int arr[size];
    
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    int sum = 0, smallest_divisor = arr[0];

    for (int i = 0; i < size - 1; ++i) {
        sum += arr[i] % arr[i + 1];
        if ((sum % arr[i + 1] == 0) && (arr[i] % arr[i + 1] == 0)) {
            smallest_divisor = arr[i + 1];
        }
    }

    cout << smallest_divisor << endl;

    return 0;
}
