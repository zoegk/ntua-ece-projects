#include <iostream>

using namespace std;

void printMagicSquare(int n) {
    int magicSquare[20][20] = {0}; 
    int row = 0;
    int col = n / 2;
    int num = 1;
    int maxNum = n * n;

    while (num <= maxNum) {
        magicSquare[row][col] = num;
        num++;
        int nextRow = (row - 1 + n) % n;
        int nextCol = (col + 1) % n;
        if (magicSquare[nextRow][nextCol] != 0) {
            row = (row + 1) % n;
        } else {
            row = nextRow;
            col = nextCol;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << magicSquare[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    char choice;
    do {
        int sideLength;
        cout << "Enter an odd side length (3 to 19): ";
        cin >> sideLength;

        if (sideLength % 2 == 0 || sideLength < 3 || sideLength > 19) {
            cout << "Invalid side length. Please enter an odd integer between 3 and 19." << endl;
        } else {
            cout << "Magic Square with side length " << sideLength << ":" << endl;
            printMagicSquare(sideLength);
        }

        cout << "Do you want to enter another side length? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
