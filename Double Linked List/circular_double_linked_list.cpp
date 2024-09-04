#include <iostream>
using namespace std;

template<typename T>
struct Node{
    T data;
    Node<T> * prev = nullptr;
    Node<T> * next = nullptr;
};

template<typename T>
class Circular_Double_Linked_List{
private:
    Node<T>* head = nullptr;


public:
    T front() {
        return head->data;
    }

    T back(){

        if(head->prev == nullptr){
            return head->data;
        }

        return head->prev->data;
    }

    bool empty() {
        return head == nullptr;
    }

    void push_front(T valor) {
        Node<T>* newNode = new Node<T>;
        newNode->data = valor;

        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            Node<T>* actual = head->prev;
            newNode->next = head;
            newNode->prev = actual;
            actual->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
    }

    void push_back(T valor) {
        Node<T>* newNode = new Node<T>;
        newNode->data = valor;

        if (head == nullptr) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            Node<T>* actual = head->prev;
            newNode->next = head;
            newNode->prev = actual;
            actual->next = newNode;
            head->prev = newNode;
        }
    }


    void insert(T value, int pos) {
        if (pos == 0) {
            push_front(value);
            return;
        }

        Node<T>* newNode = new Node<T>;
        newNode->data = value;

        Node<T>* temp = head;
        for (int i = 0; i < pos - 1 && temp->next != head; i++) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }

    void remove(int pos) {
        if (head == nullptr) return;

        Node<T>* temp = head;

        if (pos == 0) {
            if (head->next == head) {
                delete head;
                head = nullptr;
            } else {
                Node<T>* last = head->prev;
                head = head->next;
                last->next = head;
                head->prev = last;
                delete temp;
            }
            return;
        }

        for (int i = 0; i < pos && temp->next != head; i++) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }

    T operator[](int pos) {
        Node<T>* temp = head;
        for (int i = 0; i < pos && temp->next != head; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    int size() {
        if (head == nullptr) return 0;
        int count = 1;
        Node<T>* temp = head;
        while (temp->next != head) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void clear() {
        if (head == nullptr) return;

        Node<T>* temp = head;
        do {
            Node<T>* next = temp->next;
            delete temp;
            temp = next;
        } while (temp != head);

        head = nullptr;
    }

    T pop_front() {

        T valor = head->data;

        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* prev = head->prev;
            Node<T>* temp = head;

            head = head->next;
            head->prev = prev;
            prev->next = head;

            delete temp;
        }

        return valor;
    }

    T pop_back() {

        Node<T>* prev = head->prev;
        T valor = prev->data;

        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* new_ultimo = prev->prev;

            new_ultimo->next = head;
            head->prev = new_ultimo;

            delete prev;
        }

        return valor;
    }


    void reverse() {
        if (head == nullptr || head->next == head) return;

        Node<T>* actual = head;
        Node<T>* temp = nullptr;

        while (true) {
            temp = actual->prev;
            actual->prev = actual->next;
            actual->next = temp;
            actual = actual->prev;

            if (actual == head) {
                break;
            }
        }

        head = temp->prev;
    }

};

int main() {



    return 0;
}
