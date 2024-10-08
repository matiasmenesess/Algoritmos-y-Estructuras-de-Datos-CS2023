#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct Node {
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    int index;
    T val;

    Node(int index, T val): index(index), val(val) {}
};

template<typename T>
class Heap {
    string type;
    vector<T> elements;

    void heapify_down(int i) {
        int left = 2 * i + 1; //hijo izquierdo
        int right = 2 * i + 2; // hijo derecho
        int largest = i; //padre (se pone largest pero podria ser menor en un min_heap)

        if (type == "MAX_HEAP") {
            if (left < elements.size() && elements[left] > elements[largest]) { //si existe el hijo y es mayor que el padre
                largest = left; //el indice del mas grande es el del hijo izq
            }
            if (right < elements.size() && elements[right] > elements[largest]) {
                largest = right; //el indice del mas grande es el del hijo der
            }
        } else if (type == "MIN_HEAP") {
            if (left < elements.size() && elements[left] < elements[largest]) {
                largest = left;
            }
            if (right < elements.size() && elements[right] < elements[largest]) {
                largest = right;
            }
        }

        if (largest != i) { //si el largest no es el padre
            swap(elements[i], elements[largest]); // intercambia el valor del padre con el del mas grande (o mas chiquito)
            heapify_down(largest); // como no sabemos si la propiedad del heap se sigue cumpliendo después del
            // intercambio, aplicamos recursividad en el nuevo índice
        }
    }

    void heapify_up(int i) {
        int parent = (i - 1) / 2; // indidce del padre

        // mientras no hayamos llegado a la raíz y la propiedad del heap no se cumpla, intercambiamos con el padre
        if (i && ((type == "MAX_HEAP" && elements[i] > elements[parent]) ||
                  (type == "MIN_HEAP" && elements[i] < elements[parent]))) {
            swap(elements[i], elements[parent]);
            heapify_up(parent); //repetimos el proceso hacia arriba
        }
    }

public:
    Heap(string heapType) : type(heapType) {}



    void insert(T val) {
        elements.push_back(val);
        heapify_up(elements.size() - 1);
    }

    void display() {
        for (const auto& el : elements) {
            cout << el << " ";
        }
        cout << endl;
    }

    void pop() {
        if (elements.size() == 0) {
            cout << "Heap vacio" << endl;
            return;
        }

        swap(elements[0], elements[elements.size() - 1]);
        elements.pop_back();
        heapify_down(0);
    }

    void build(T* arr, int n) { //se le pasa el array con elementos
        elements.assign(arr, arr + n); //copia los elementos del array al vector
        buildHeap();
    }

    void buildHeap() {
        int index = (elements.size() / 2) - 1; //nos da el ultimo nodo no hoja
        while (index >= 0) {
            heapify_down(index);
            index--;
        }
    }
};

int main() {

  //ejemplo 
    int arr[] = {3, 19, 1, 14, 8, 7};
    int n = sizeof(arr) / sizeof(arr[0]); //sizeof da el size de algo

    Heap<int> maxHeap("MAX_HEAP");
    maxHeap.build(arr, n);

    cout << "mostrar : ";
    maxHeap.display();

    maxHeap.insert(25);
    cout << "Heap despues de insertar 25: ";
    maxHeap.display();

    maxHeap.pop();
    cout << "Heap despues de hacer pop: ";
    maxHeap.display();

    return 0;
}
