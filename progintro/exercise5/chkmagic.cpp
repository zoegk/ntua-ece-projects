#include <iostream>
#include <cstring>

using namespace std;

void checkMemory(void* address) {
    if (address == nullptr) {
        cerr << "Error: Unable to allocate memory!" << endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    int N;
    cin >> N;

    int** matrix = new int*[N];
    int* rowSums = new int[N];
    int* colSums = new int[N];
    int* occurrenceCount = new int[N * N];
    memset(occurrenceCount, 0, N * N * sizeof(int));

    long int diagonalSum1 = 0, diagonalSum2 = 0;

    for (int i = 0; i < N; ++i) {
        matrix[i] = new int[N];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> matrix[i][j];
            occurrenceCount[matrix[i][j]] += 1;
            
            if (i == j)
                diagonalSum1 += matrix[i][j];

            if (i + j == N - 1)
                diagonalSum2 += matrix[i][j];

            rowSums[i] += matrix[i][j];
            colSums[j] += matrix[i][j];
        }
    }

    for (int i = 0; i < N * N; ++i) {
        if (occurrenceCount[i] != 1) {
            cout << "no" << endl;
            //cout << "The number " << i << " is not present exactly once in the matrix." << endl;
            goto cleanup;
        }
    }

    if (diagonalSum1 != diagonalSum2) {
        cout << "no" << endl;
        //cout << "The sum of the main diagonal is not equal to the sum of the secondary diagonal." << endl;
        goto cleanup;
    }

    for (int i = 0; i < N; ++i) {
        if (rowSums[i] != diagonalSum1) {
            cout << "no" << endl;
            //cout << "The sum of row " << i << " is not equal to the sum of the main diagonal." << endl;
            goto cleanup;
        }

        if (colSums[i] != diagonalSum1) {
            cout << "no" << endl;
            //cout << "The sum of column " << i << " is not equal to the sum of the main diagonal." << endl;
            goto cleanup;
        }
    }

    cout << "yes" << endl;

cleanup:

    for (int i = 0; i < N; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] rowSums;
    delete[] colSums;
    delete[] occurrenceCount;

    return 0;
}
