#include <cmath>
#include <iostream>
using namespace std;

template <typename T>
struct NodoBT {
    T dato;
    int altura;
    NodoBT<T>* izquierdo;
    NodoBT<T>* derecho;
    NodoBT() : izquierdo(nullptr), derecho(nullptr), altura(0) {}
    explicit NodoBT(T valor) : dato(valor), altura(0) {
        izquierdo = derecho = nullptr;
    }
    void eliminar() {
        if (izquierdo != nullptr) { izquierdo->eliminar(); }
        if (derecho != nullptr) { derecho->eliminar(); }
        delete this;
    }
};

template <typename T>
class AVL {
    NodoBT<T>* raiz;
public:
    AVL() : raiz(nullptr) {}
    void insertar(T valor) {
        insertar(raiz, valor);
    }
    bool encontrar(T valor) {
        NodoBT<T>* nodo = encontrar(raiz, valor);
        if (nodo != nullptr) { return true; }
        return false;
    }
    int altura() {
        return altura(raiz);
    }
    T valorMinimo() {
        if (raiz) {
            return valorMinimo(raiz)->dato;
        }
    }
    T valorMaximo() {
        if (raiz) { return valorMaximo(raiz)->dato; }
    }
    bool estaBalanceado() {
        if (raiz) {
            return estaBalanceado(raiz);
        }
    }
    int tamaño();
    void eliminar(T valor) {
        if (raiz) {
            eliminar(raiz, valor);
        }
    }
    void mostrar() {
        if (raiz == nullptr) {
        }
        else {
            mostrar(raiz);
        }
    }
    void mostrarPreOrden() {
        if (raiz == nullptr) {
        }
        else {
            mostrarPreOrden(raiz);
        }
    }
    void limpiar() {
        if (raiz) {
            raiz->eliminar();
            raiz = nullptr;
        }
    }
    ~AVL() { limpiar(); }
private:
    void insertar(NodoBT<T>*& nodo, T valor) {
        if (nodo == nullptr) {
            nodo = new NodoBT<T>(valor);
        }
        else if (nodo->dato < valor) { insertar(nodo->derecho, valor); }
        else if (nodo->dato > valor) { insertar(nodo->izquierdo, valor); }
        actualizarAltura(nodo);
        balancear(nodo);
    }
    void eliminar(NodoBT<T>*& nodo, T valor) {
        if (nodo == nullptr) { return; }
        else if (nodo->dato < valor) { eliminar(nodo->derecho, valor); }
        else if (nodo->dato > valor) { eliminar(nodo->izquierdo, valor); }
        else {
            if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) { delete nodo; nodo = nullptr; }
            else if (nodo->izquierdo == nullptr) {
                NodoBT<T>* temp = nodo;
                nodo = nodo->derecho;
                delete temp;
            }
            else if (nodo->derecho == nullptr) {
                NodoBT<T>* temp = nodo;
                nodo = nodo->izquierdo;
                delete temp;
            }
            else {
                T temp = valorMaximo(nodo->izquierdo)->dato;
                nodo->dato = temp;
                eliminar(nodo->izquierdo, temp);
            }
        }
        if (nodo) {
            actualizarAltura(nodo);
            balancear(nodo);
        }
    }
    NodoBT<T>* encontrar(NodoBT<T>* nodo, T valor) {
        if (nodo == nullptr) {
            return nullptr;
        }
        if (nodo->dato == valor) {
            return nodo;
        }
        else if (nodo->dato < valor) {
            return encontrar(nodo->derecho, valor);
        }
        else {
            return encontrar(nodo->izquierdo, valor);
        }
    }
    int altura(NodoBT<T>* nodo) {
        if (nodo == nullptr) {
            return -1;
        }
        return max(altura(nodo->izquierdo), altura(nodo->derecho)) + 1;
    }
    void actualizarAltura(NodoBT<T>*& nodo) {
        nodo->altura = max(altura(nodo->izquierdo), altura(nodo->derecho)) + 1;
    }
    NodoBT<T>* valorMinimo(NodoBT<T>* nodo) {
        while (nodo->izquierdo != nullptr) {
            nodo = nodo->izquierdo;
        }
        return nodo;
    }
    NodoBT<T>* valorMaximo(NodoBT<T>* nodo) {
        while (nodo->derecho != nullptr) {
            nodo = nodo->derecho;
        }
        return nodo;
    }
    void mostrar(NodoBT<T>* nodo) {
        if (nodo == nullptr) { return; }
        mostrar(nodo->izquierdo);
        cout << nodo->dato << " ";
        mostrar(nodo->derecho);
    }
    void mostrarPreOrden(NodoBT<T>* nodo) {
        if (nodo == nullptr) { return; }
        cout << nodo->dato << " ";
        mostrarPreOrden(nodo->izquierdo);
        mostrarPreOrden(nodo->derecho);
    }
    bool estaBalanceado(NodoBT<T>* nodo) {
        if (nodo == nullptr) { return true; }

        int izquierda = altura(nodo->izquierdo);
        int derecha = altura(nodo->derecho);
        int diferencia = abs(izquierda - derecha);
        if (diferencia > 1) { return false; }

        return estaBalanceado(nodo->izquierdo) && estaBalanceado(nodo->derecho);
    }

    void rotarDerecha(NodoBT<T>*& nodo) {
        NodoBT<T>* hijoIzquierdo = nodo->izquierdo;
        nodo->izquierdo = hijoIzquierdo->derecho;
        hijoIzquierdo->derecho = nodo;
        actualizarAltura(nodo);
        actualizarAltura(hijoIzquierdo);
        nodo = hijoIzquierdo;
    }
    void rotarIzquierda(NodoBT<T>*& nodo) {
        NodoBT<T>* hijoDerecho = nodo->derecho; // hijo derecho de nodo
        nodo->derecho = hijoDerecho->izquierdo; // hijo derecho de nodo es ahora el hijo izquierdo del hijo derecho
        hijoDerecho->izquierdo = nodo;
        actualizarAltura(nodo);
        actualizarAltura(hijoDerecho);
        nodo = hijoDerecho; // con esto se conservan los enlaces con el padre de nodo
    }
    void balancear(NodoBT<T>*& nodo) {
        int hb = factorBalanceo(nodo);
        if (hb > 1) {
            if (factorBalanceo(nodo->izquierdo) < 0) {
                rotarIzquierda(nodo->izquierdo);
            }
            rotarDerecha(nodo);
        }
        else if (hb < -1) {
            if (factorBalanceo(nodo->derecho) > 0) {
                rotarDerecha(nodo->derecho);
            }
            rotarIzquierda(nodo);
        }
    }
    int factorBalanceo(NodoBT<T>* nodo) {
        return altura(nodo->izquierdo) - altura(nodo->derecho);
    }
};

int main() {

    return 0;
}
