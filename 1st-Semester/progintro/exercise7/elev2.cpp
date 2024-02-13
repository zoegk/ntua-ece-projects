
//A lift can hold a maximum of two people with a maximum weight of B kg (both together). 
//On the ground floor, N people are waiting to use the elevator to go up to the top floor. 
//Fortunately, we know the W_i weights of all of them.

//Write a program that reads this data and finds the minimum number of trips the elevator must make to carry all the people.

#include <iostream>

using namespace std;

int partition(int arr[], int first, int last) {
    int pivot = arr[(first + last) / 2];
    int i = first, j = last;
    while (true) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i >= j) break;
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    return j;
}

void quicksort(int arr[], int first, int last) {
    if (first >= last) return;
    int pivot = partition(arr, first, last);
    quicksort(arr, first, pivot);
    quicksort(arr, pivot + 1, last);
}

int main() {
    int N, B, count = 0;
    cin >> N >> B;
    int numbers[N];
    for (int i = 0; i < N; i++) {
        cin >> numbers[i];
    }
    quicksort(numbers, 0, N - 1);
    int left = 0, right = N - 1;
    while (left <= right) {
        if (numbers[left] + numbers[right] <= B) {
            left++;
        }
        right--;
        count++;
    }
    cout << count << std::endl;
    return 0;
}
