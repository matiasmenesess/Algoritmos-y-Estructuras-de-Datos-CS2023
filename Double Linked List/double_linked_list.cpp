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
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;

public:
    T front() {
        return head->data;
    }

    T back() {
        return tail->data;
    }

    bool empty() {
        return head == nullptr;
    }

    void push_front(T value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = head;
        newNode->prev = nullptr;

        if (head == nullptr) {
            tail = newNode;
        } else {
            head->prev = newNode;
        }
        head = newNode;
    }

    void push_back(T value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail == nullptr) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    void insert(T value, int pos) {
        if (pos == 0) {
            push_front(value);
            return;
        }

        Node<T>* newNode = new Node<T>;
        newNode->data = value;

        Node<T>* temp = head;
        for (int i = 0; i < pos - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr) {
            push_back(value);
        } else {
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
        }
    }

    void remove(int pos) {
        if (head == nullptr) return;

        Node<T>* temp = head;
        for (int i = 0; i < pos && temp != nullptr; i++) {
            temp = temp->next;
        }

        if (temp == nullptr) return;

        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }

        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev;
        }

        delete temp;
    }

    T operator[](int pos) {
        Node<T>* temp = head;
        for (int i = 0; i < pos && temp != nullptr; i++) {
            temp = temp->next;
        }
        return temp ? temp->data : T();
    }

    int size() {
        int size = 0;
        Node<T>* temp = head;

        while (temp != nullptr) {
            size++;
            temp = temp->next;
        }
        return size;
    }

    void clear() {
        Node<T>* temp = head;

        while (temp != nullptr) {
            Node<T>* next = temp->next;
            delete temp;
            temp = next;
        }

        head = nullptr;
        tail = nullptr;
    }

void reverse() {
    if (head == nullptr || head == tail) return;

    Node<T>* actual = head;
    Node<T>* temp = nullptr;

    while (actual != nullptr) {
        temp = actual->prev;
        actual->prev = actual->next;
        actual->next = temp;
        actual = actual->prev;
    }

    if (temp != nullptr) {
        tail = head; 
        head = temp->prev; 
    }
}

};

int main() {



    return 0;
}
