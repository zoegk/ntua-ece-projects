#include <iostream>
#include <string>

using namespace std;

bool isRecursive(const string& str) {
    int left = 0, right = str.length() - 1;
    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {
    int N;
    cin >> N; 

    cin.ignore(10000, '\n');
    
    int recursiveCount = 0;

    for (int i = 0; i < N; ++i) {
        string str;
        char ch;
        
        while (cin.get(ch) && ch != '\n') {
            str += ch;
        }

        if (str.empty()) {
            cout << "empty" << endl;
            continue;
        }

        if (str.length() > 20) {
            cout << "error" << endl;
            continue;
        }

        if (isRecursive(str)) {
            cout << "yes" << endl;
            recursiveCount++;
        } else {
            cout << "no" << endl;
        }
    }

    if (N > 0) {
        cout << (recursiveCount * 100 / N) << ".000" << endl;
    }

    return 0;
}
