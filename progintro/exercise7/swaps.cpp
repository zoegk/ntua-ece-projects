
//Given a sequence consisting of N non-zero integers. We start playing the following game:
// At each step of the game, we find all pairs of adjacent numbers in the sequence, 
//for which the left number is positive and the right number is negative. 
//For each such pair, we transpose the two numbers. Then we proceed to the next step. 
//We repeat with as many steps as necessary, until no more permutations can be made.

Write a program that calculates: how many permutations will happen throughout the game, what will be the first and what will be the last number of the sequence after the last step.
#include <iostream>

using namespace std;

void playgame(int num_elements, int array[], int& counter, int& min_value, int& max_value, int& neg) {
    min_value = 100000;
    bool flag = true;
    neg = 0;

    for (int i = 0; i < num_elements; i++) {
        cin >> array[i];
        if (flag && array[i] < 0) {
            min_value = array[i];
            flag = false;
        }
        if (array[i] > 0)
            max_value = array[i];
        if (array[i] < 0)
            neg++;
    }

    counter = 0;
    for (int i = 0; i < num_elements - 1; i++) {
        if (array[i] > 0) {
            counter += neg;
        }
        if (array[i] < 0)
            neg--;
    }
}

int main() {
    int num_elements;
    cin >> num_elements;
    int *array = new int[num_elements];
    int counter, min_value, max_value, neg;

    playgame(num_elements, array, counter, min_value, max_value, neg);

    cout << counter << endl;
    cout << min_value << endl;
    cout << max_value << endl;

    delete[] array;

    return 0;
}
