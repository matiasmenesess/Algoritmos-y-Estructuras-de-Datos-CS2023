#include <iostream>
using namespace std;

template<typename T>
struct Node{
    T data;
    Node * next= nullptr;
};

template<typename T>
class List{
    Node<T> * head = nullptr;

public:

    T front(){
        return head->data; //O(1)
    }

    T back(){ //O(n)
        auto temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        return temp->data;
    }

    void push_front(T data_nodo){
        Node<T> newNode = new Node<T>();
        newNode.data= data_nodo;
        newNode.next = head;
        head = newNode;
    }

    void push_back(T data_nodo) {
        Node<T>* newNode = new Node<T>();
        newNode->data = data_nodo;
        if (!head) {
            head = newNode;
        } else {
            auto temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }


    T pop_front(){ //O(1)
        if(head == nullptr){
            return;
        }
        else{
            auto temp = head;
            head = temp->next;
            T tempData = temp->data;
            delete temp;
            return tempData;
        }
    }

    T pop_back() { //O(n)
        if (head== nullptr) {
            return;
        }
        if (!head->next) {
            T tempData = head->data;
            delete head;
            head = nullptr;
            return tempData;
        }
        auto temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        auto temp2 = temp->next;
        T tempData = temp2->data;
        temp->next = nullptr;
        delete temp2;
        return tempData;
    }

    T operator[](int pos) {
        auto temp = head;
        for (int i = 0; i < pos && temp != nullptr; i++) {
            temp = temp->next;
        }
        if (!temp) {
            return;
        }
        return temp->data;
    }

    bool empty(){
        if(head == nullptr){
            return true;
        }
        return false;
    }

    int size(){
        int contador = 0;
        auto temp = head;
        while(temp != nullptr){
            temp = temp->next;
            contador++;
        }
        return contador;
    }

    void clear(){
        while (head != nullptr) {
            auto temp = head;
            head = head->next;
            delete temp;
        }
    }

    void sort() {
        if (head == nullptr || head->next == nullptr) return;

        Node<T>* actual = head;
        Node<T>* prev = nullptr;

        bool sorted = false;
        while (!sorted) {
            sorted = true;

            while (actual != nullptr && actual->next != nullptr) {
                Node<T>* posterior = actual->next;

                if (actual->data > posterior->data) {
                    if (prev == nullptr) {
                        head = posterior;
                    } else {
                        prev->next = posterior;
                    }
                    actual->next = posterior->next;
                    posterior->next = actual;

                    prev = posterior;
                    sorted = false;
                } else {
                    prev = actual;
                    actual = actual->next;
                }
            }

            actual = head;
            prev = nullptr;
        }
    }

    void reverse(){ //O(n)

        Node<T>* anterior = nullptr;
        auto *actual =head;
        Node<T>* posterior = nullptr;
        while(actual!= nullptr){
            posterior = actual->next;
            actual->next = anterior;
            anterior = actual;
            actual = posterior;
        }
    }

};

int main(){
    return 0;
}
