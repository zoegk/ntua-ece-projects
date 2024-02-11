#include <iostream>
#include <string>

using namespace std;

bool isValidPermutation(const string& permutation) {
    if (permutation.size() != 26) {
        return false;
    }
    int count[26] = {0};
    for (char ch : permutation) {
        if (!islower(ch)) {
            return false;
        }
        if (count[ch - 'a'] == 1) {
            return false;
        }
        count[ch - 'a']++;
    }
    return true;
}

string calculateInversePermutation(const string& permutation) {
    string inversePermutation = permutation;
    for (int i = 0; i < 26; ++i) {
        inversePermutation[permutation[i] - 'a'] = 'a' + i;
    }
    return inversePermutation;
}

char encryptChar(char ch, const string& permutation) {
    if (islower(ch)) {
        return permutation[ch - 'a'];
    } else if (isupper(ch)) {
        char lower = tolower(ch);
        char encrypted = tolower(permutation[lower - 'a']);
        return toupper(encrypted);
    } else {
        return ch;
    }
}

int main() {
    string permutation;
    cin >> permutation;

    if (!isValidPermutation(permutation)) {
        cout << "error" << endl;
        return 0;
    }

    string operation;
    cin >> operation;

    cin.ignore(); 

    string inputText;
    getline(cin, inputText);

    string outputText;
    if (operation[0] == 'd') {
        string inversePermutation = calculateInversePermutation(permutation);
        for (char ch : inputText) {
            outputText += encryptChar(ch, inversePermutation);
        }
    } else {
        for (char ch : inputText) {
            outputText += encryptChar(ch, permutation);
    }
}


    cout << outputText << endl;

    return 0;
}
