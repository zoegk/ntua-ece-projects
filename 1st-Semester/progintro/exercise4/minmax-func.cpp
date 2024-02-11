#include <iostream>

using namespace std;

typedef int list[20]; 

int minimum(list a) {
    int min = a[0];
    for (int i = 1; i < 20; ++i) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

int maximum(list a) {
    int max = a[0];
    for (int i = 1; i < 20; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    return max;
}

int main() {
    list arr = {10, 5, 20, 15, 25, 30, 35, 40, 45, 50,
                55, 60, 65, 70, 75, 80, 85, 90, 95, 100};

    cout << "Minimum number: " << minimum(arr) << endl;

    cout << "Maximum number: " << maximum(arr) << endl;

    return 0;
}
