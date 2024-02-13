#include <iostream>

using namespace std;

void hello() {
    cout << "hello world" << endl;
}

int main() {
    int n, i;
    cout << "Give number of greetings, then press <enter>: ";
    cin >> n;
    for (i = 1; i <= n; i++) {
        hello();
    }
    return 0;
}

