
//We often want to distribute items fairly. A criterion of fairness is to minimize 
//the value of the items that the most favored person will get from the distribution.

//So we have a sequence of N coupons worth V_1, V_2, ..., V_Ν and we want to divide it 
//into three parts so that the total value of the coupons in the best part (i.e. the part with the highest total value) 
//is the smallest possible . Splitting must be done without reordering tokens, segments must contain consecutive tokens, 
//and each token must belong to exactly one segment.

#include <iostream>

using namespace std;

int getMax(int array[], int size) {
    int max = array[0];
    for (int i = 0; i < size; i++)
        if (max < array[i])
            max = array[i];
    return max;
}

int getMin(int array[], int size) {
    int min = array[0];
    for (int i = 0; i < size; i++)
        if (min > array[i])
            min = array[i];
    return min;
}

int getParts(int array[], int size, int checkValue) {
    int shares = 1;
    int tmpSum = 0;
    for (int i = 0; i < size; i++) {
        tmpSum += array[i];
        if (tmpSum > checkValue) {
            tmpSum = array[i];
            shares++;
        }
    }
    return shares;
}

int main() {
    int N, parts;
    parts = 3;

    cin >> N;
    int arr[N];
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    int lo = getMin(arr, N);
    int hi = getMax(arr, N) * N;

    while (lo < hi) {
        int mid = (lo + hi) / 2;
        int shares = getParts(arr, N, mid);
        if (shares <= parts) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << lo << endl;

    return 0;
}
