#include <iostream>
#include <cstdio>
#include <cstdlib> 

using namespace std;

struct node {
  int data;
  node *next;
};

class queue {
public:
  queue();
  bool empty();
  void enqueue (int newData);
  int dequeue();
  int peek();

private:
  node *head, *tail;
};

queue::queue() {
  head=tail=nullptr;
}

bool queue::empty(){
  return (head==nullptr);
}

void queue::enqueue(int newData) {
  node *newNode = new node;
  newNode->data = newData;
  newNode->next = nullptr;

  if (head == nullptr) {
    head = newNode;
  }
  else {
    tail->next = newNode;
  }
  tail=newNode;
}

int queue::dequeue() {

  node *newNode = head;
  int result = head->data;

  if (head == tail) {
    tail = nullptr;
  }

  head = head->next;
  delete newNode;
  return result;
}

int queue::peek() {
  return head->data;
}

int main() {
    queue posQueue, negQueue;
    int posCount = 0, negCount = 0, num;
    bool flag = true;

    while (scanf("%d", &num) == 1) {
        if (num > 0) {
            posQueue.enqueue(num);
            posCount++;
        } else if (num < 0) {
            negQueue.enqueue(num);
            negCount++;
        }
    }

    if (posCount != negCount) {
        flag = false;
    } else {
        while (posCount > 0) {
            if (posQueue.dequeue() + negQueue.dequeue() != 0) {
                flag = false;
                break;
            }
            posCount--;
        }
    }

    if (flag) {
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }

    return 0;
}