#include <iostream>
using namespace std;

template<typename T>
struct Node{
    T data;
    Node<T> * prev = nullptr;
    Node<T> * next = nullptr;
};

template<typename T>
class Double_Linked_List{
private:
    Node<T>* front = nullptr;
    Node<T>* rear = nullptr;
    int size = 0;

public:
    T front_() {
        return front->data;
    }

    T rear_() {
        return rear->data;
    }

    bool empty() {
        return front == nullptr;
    }

    void push_back(T value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = rear;

        if (rear == nullptr) {
            front = newNode;
        } else {
            rear->next = newNode;
        }
        rear = newNode;
        size++;
    }

    void pop_front() {
        if (front == nullptr) {
            return;
        }
        Node<T>* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        } else {
            front->prev = nullptr;
        }
        delete temp;
        size--;
    }

    int getSize() const {
        return size;
    }
};

template<typename T>
class queue{
    Double_Linked_List<T> queue_;
    int max_size;

public:
    queue(int size){
        max_size = size;
    }

    bool isempty() {
        return queue_.empty();
    }

    bool isfull() const {
        return queue_.getSize() == max_size;
    }

    T front(){
        return queue_.front_();
    }

    void enqueue(T val) {
        if (isfull()) {
            return;
        }
        queue_.push_back(val);
    }

    void dequeue() {
        if (isempty()) {
            return;
        }
        queue_.pop_front();
    }

    int getSize() const {
        return queue_.getSize();
    }
};


int main() {


    return 0;
}

