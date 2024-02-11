#include <iostream>
#include <climits>

using namespace std;

bool contains(int arr[], int size, int num) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == num) {
            return true;
        }
    }
    return false;
}

int main() {
    const int MAX_N = 50000;
    int N;
    cin >> N;

    int A[MAX_N], B[MAX_N];
    bool sameElements = true;
    int minMissingA = INT_MAX, maxMissingA = INT_MIN;
    int minMissingB = INT_MAX, maxMissingB = INT_MIN;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    for (int i = 0; i < N; ++i) {
        cin >> B[i];
    }

    for (int i = 0; i < N; ++i) {
        if (!contains(B, N, A[i])) {
            sameElements = false;
            minMissingB = min(minMissingB, A[i]);
            maxMissingB = max(maxMissingB, A[i]);
        }
    }

    for (int i = 0; i < N; ++i) {
        if (!contains(A, N, B[i])) {
            sameElements = false;
            minMissingA = min(minMissingA, B[i]);
            maxMissingA = max(maxMissingA, B[i]);
        }
    }

    if (sameElements) {
        cout << "yes" << endl;
    } else {
        cout << "no " << min(minMissingA, minMissingB) << " " << max(maxMissingA, maxMissingB) << endl;
    }

    return 0;
}
