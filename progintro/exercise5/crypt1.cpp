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

    cin.ignore(); 

    string plaintext;
    getline(cin, plaintext);

    string ciphertext;
    for (char ch : plaintext) {
        ciphertext += encryptChar(ch, permutation);
    }

    cout << ciphertext << endl;

    return 0;
}
