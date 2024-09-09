#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;
};

template<typename T>
class Circular_Double_Linked_List {
private:
    Node<T>* front = nullptr;
    Node<T>* rear = nullptr;
    int max_size;
    int current_size = 0;

public:
    Circular_Double_Linked_List(int max_size) {
        this->max_size = max_size;
    }

    T front_() {
        if (front != nullptr)
            return front->data;
    }

    T rear_() {
        if (rear != nullptr)
            return rear->data;
    }

    bool empty() {
        return current_size == 0;
    }

    bool full() {
        return current_size == max_size;
    }

    void enqueue(T value) {
        if (full()) {
            cout << "Queue is full" << endl;
            return;
        }

        Node<T>* newNode = new Node<T>;
        newNode->data = value;

        if (empty()) {
            front = rear = newNode;
            front->next = front;
            front->prev = front;
        } else {
            newNode->prev = rear;
            newNode->next = front;
            rear->next = newNode;
            front->prev = newNode;
            rear = newNode;
        }
        current_size++;
    }

    void dequeue() {
        if (empty()) {
            cout << "Queue is empty" << endl;
            return;
        }

        Node<T>* temp = front;

        if (front == rear) {
            front = rear = nullptr;
        } else {
            front = front->next;
            front->prev = rear;
            rear->next = front;
        }
        delete temp;
        current_size--;
    }

    int size() const {
        return current_size;
    }
};

template<typename T>
class circular_queue {
private:
    Circular_Double_Linked_List<T> queue_;

public:
    circular_queue(int size) : queue_(size) {}

    bool isempty() const {
        return queue_.empty();
    }

    bool isfull() const {
        return queue_.full();
    }

    T front() {
        return queue_.front_();
    }

    T rear() {
        return queue_.rear_();
    }

    void enqueue(T val) {
        queue_.enqueue(val);
    }

    void dequeue() {
        queue_.dequeue();
    }
};



int main() {


    return 0;
}



