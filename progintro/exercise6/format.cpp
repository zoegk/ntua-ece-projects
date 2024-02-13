#include <iostream>
#include <cstring>

using namespace std;

const int MAX_LINE = 60;
const int MAX_WORD = 20;

void formatText(char line[], int& wordCount, int index) {
    int spacesToFill = MAX_LINE - index;
    int blanks = wordCount - 1;
    int modBlanks = spacesToFill % blanks;
    int totalSpaces = spacesToFill / blanks;

    for (int j = 0; j < index; j++) {
        int runner = totalSpaces;
        if (line[j] == ' ') {
            do {
                cout << ' ';
            } while (runner-- > 0);

            if (modBlanks >= wordCount - 1)
                cout << ' ';

            wordCount -= 1;
        }
        else {
            cout << line[j];
        }
    }
    cout << endl;
}

int main() {
    char line[MAX_LINE + 1];
    char word[MAX_WORD + 1];

    int wordCount = 0;
    int index = 0;

    cin >> word;
    while (word[index] != '\0') {
        line[index] = word[index];
        index += 1;
    }
    wordCount = 1;

    while (cin >> word) {
        int wordLength = strlen(word);
        if (index + wordLength < MAX_LINE) {
            line[index++] = ' ';
            wordCount += 1;
            int j = 0;
            while (word[j] != '\0') {
                line[index++] = word[j++];
            }
        }
        else {
            formatText(line, wordCount, index);

            wordCount = 1;
            index = 0;

            int j = 0;
            while (word[j] != '\0') {
                line[index++] = word[j++];
            }
        }
    }

    for (int j = 0; j < index; j++) {
        cout << line[j];
    }
    cout << endl;

    return 0;
}
