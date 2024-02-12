#include <iostream>
#include <cstdio>

using namespace std;

class list {
public:
    list();
    bool empty();
    int size();
    void add(int k, int x);
    int get(int k);
    void remove(int k);

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
    node *newnode = new node;
    newnode->data = x;
    newnode->next = nullptr;

    if (k == 1) {
        newnode->next = head;
        head = newnode;
        return;
    }

    node *current = head;
    for (int i = 0; i < k - 2; i++)
        current = current->next;

    newnode->next = current->next;
    current->next = newnode;
}

void list::remove(int k) {
    length--;
    node *temp = head;

    if (k == 1) {
        head = head->next;
        delete temp;
        return;
    }
    else{
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

int main() {
    list mylist;
    int numInputs, position, value, numDeletions;

    cin >> numInputs;

    for (int i = 0; i < numInputs; i++) {
        cin >> position >> value;
        mylist.add(position, value);
    }

    cin >> numDeletions;

    for (int i = 0; i < numDeletions; i++) {
        cin >> position;
        mylist.remove(position);
    }

    cin >> position; // This will be used as k to get the size and data at position K
    cout << mylist.size() << " " << mylist.get(position) << endl;

    return 0;
}
