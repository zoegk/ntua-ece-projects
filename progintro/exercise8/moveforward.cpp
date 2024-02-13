#include <iostream>

using namespace std;

class list {
public:
    list();
    bool empty();
    int size();
    void add(int k, int x);
    int get(int k);
    void remove(int k);
    int searchMF(int x); 

private:
    struct node {
        int data;
        node *next;
    };
    node *head;
    int length;
};

list::list() {
    head = nullptr;
    length = 0;
}

int list::size() {
    return length;
}

bool list::empty() {
    return head == nullptr;
}

void list::add(int k, int x) {
    length++;
    node *newNode = new node;
    newNode->data = x;
    newNode->next = nullptr;

    if (k == 1) {
        newNode->next = head;
        head = newNode;
        return;
    }

    node *current = head;
    for (int i = 0; i < k - 2; i++)
        current = current->next;

    newNode->next = current->next;
    current->next = newNode;
}

void list::remove(int k) {
    length--;
    node *temp = head;

    if (k == 1) {
        head = head->next;
        delete temp;
        return;
    }
    else {
        node *toDelete;
        for (int i = 1; i < k - 1; i++)
            temp = temp->next;

        toDelete = temp->next;

        temp->next = toDelete->next;

        delete toDelete;
    }
}

int list::get(int k) {
    node *current = head;

    for (int i = 1; i < k; i++)
        current = current->next;

    return current->data;
}

int list::searchMF(int x) {
    int position = 0;
    node *prev = nullptr;
    node *current = head;

    while (current != nullptr) {
        position++;
        if (current->data == x) {
            if (prev != nullptr) { 
                prev->next = current->next;
                current->next = head;
                head = current;
            }
            return position;
        }
        prev = current;
        current = current->next;
    }

    return 0; 
}

int main() {
    list myList;
    int numInputs, position, value, numSearches, sum = 0;

    cin >> numInputs;

    for (int i = 0; i < numInputs; i++) {
        cin >> position >> value;
        myList.add(position, value);
    }

    cin >> numSearches;

    for (int i = 0; i < numSearches; i++) {
        cin >> value;
        sum += myList.searchMF(value);
    }

    cout << sum << endl;

    return 0;
}
