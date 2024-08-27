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

    void Invertir(){ //O(n)

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

template<typename T>
ostream& operator<< (ostream& os, List<T>* L){
    auto* temp = L->getHead();
    os<<"[";
    while(temp != nullptr){
        os<<temp->data<<" ";
        temp = temp->next;
    }
    os<<"]";
    return os;
}

template<typename T>
void Invertir_Como_Funcion(List<T> lista){ //O(n)

    Node<T>* anterior = nullptr;
    auto *actual =lista.head;
    Node<T>* posterior = nullptr;
    while(actual!= nullptr){
        posterior = actual->next;
        actual->next = anterior;
        anterior = actual;
        actual = posterior;
    }
    return;
};

template<typename T>
T Nueva_Lista_Ordenada(List<T> lista1, List<T> lista2){

}

template<typename T>
T interseccion(List<T> lista1, List<T> lista2){

}







