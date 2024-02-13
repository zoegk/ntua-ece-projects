#include <iostream>

using namespace std;

const int n = 20;

void num_hello(int i) {
    cout << i << " hello world" << endl;
}

int main() {
    for (int i = 1; i <= n; i++) {
        num_hello(i);
    }
    return 0;
}
