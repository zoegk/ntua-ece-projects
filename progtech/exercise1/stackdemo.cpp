#include <iostream>
using namespace std;

template <typename T>
class stack {
public:
    stack(int size) {
        arr = new T[size];
        if (!arr) {
            perror("Out of memory");
            exit(1);
        }
        capacity = size;
        current = 0;
    }

    stack(const stack &s) {
        capacity = s.capacity;
        current = s.current;
        arr = new T[capacity];
        if (!arr) {
            perror("Out of memory");
            exit(1);
        }
        for (int i = 0; i < current; ++i) {
            arr[i] = s.arr[i];
        }
    }

    ~stack() {
        delete[] arr;
    }

    const stack & operator = (const stack &s) {
        delete[] arr;
        capacity = s.capacity;
        current = s.current;
        arr = new T[capacity];
        if (!arr) {
            perror("Out of memory");
            exit(1);
        }
        for (int i = 0; i < current; ++i) {
            arr[i] = s.arr[i];
        }
        return *this;
    }

    bool empty() { return (current == 0); }

    void push(const T &x) {
        if (current == capacity) {
            perror("Stack is full");
            exit(1);
        }
        arr[current] = x;
        ++current;
    }

    T pop() {
        if (current == 0) {
            perror("Stack is empty");
            exit(1);
        }
        --current;
        return arr[current];
    }

    int size() { return current; }

    friend ostream & operator << (ostream &out, const stack &s) {
        if (s.current == 0) {
            out << "[]";
        }
        else if (s.current == 1) {
            out << "[" << s.arr[0] << "]";
        }
        else {
            out << "[";
            for (int i = 0; i < s.current - 1; ++i) {
                out << s.arr[i] << ", ";
            }
            out << s.arr[s.current - 1] << "]";
        }
        return out;
    }

private:
    T* arr;
    int current;
    int capacity;
};



