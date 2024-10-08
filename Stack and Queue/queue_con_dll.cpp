#include <iostream>
#include <vector>
using namespace std;

#include <iostream>
using namespace std;

template<typename T>
struct NodeDLL{
    T data;
    NodeDLL<T> * prev = nullptr;
    NodeDLL<T> * next = nullptr;
};

template<typename T>
class Double_Linked_List{
private:
    NodeDLL<T>* front = nullptr;
    NodeDLL<T>* rear = nullptr;
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
        NodeDLL<T>* newNode = new NodeDLL<T>;
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
        NodeDLL<T>* temp = front;
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
class Queue{
    Double_Linked_List<T> queue_;
    int max_size;

public:
    Queue(int size){
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


