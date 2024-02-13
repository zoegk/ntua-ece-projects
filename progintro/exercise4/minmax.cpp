#include <iostream>

using namespace std;

typedef int list[100]; 

int minimum(list a, int size) {
    int min = a[0];
    for (int i = 1; i < size; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

int maximum(list a, int size) {
    int max = a[0];
    for (int i = 1; i < size; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

int main() {
    int N, M;
    cin >> N >> M; 

    list columnMax, rowMin;

    for (int i = 0; i < N; ++i) {
        list row;
        for (int j = 0; j < M; ++j) {
            cin >> row[j];
            if (i == 0) {
                columnMax[j] = row[j];
            } else {
                if (row[j] > columnMax[j]) {
                    columnMax[j] = row[j];
                }
            }
            if (j == 0) {
                rowMin[i] = row[j];
            } else {
                if (row[j] < rowMin[i]) {
                    rowMin[i] = row[j];
                }
            }
        }
    }

    int smallestColumnMax = minimum(columnMax, M);

    int largestRowMin = maximum(rowMin, N);

    cout << smallestColumnMax << endl;

    cout << largestRowMin << endl;

    return 0;
}
