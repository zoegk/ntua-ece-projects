#include <iostream>

using namespace std;

void hello() {
    cout << "hello world" << endl;
}

int main() {
    for (int i = 1; i <= 20; i++) {
        hello();
    }
    return 0;
}
