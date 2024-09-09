Ejemplos de iteradores:

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    // Declaracion
    vector<int>::iterator it;

    for (it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";  // El valor al que apunta el iterador
    }

    // iterador para modificar los valores del vector
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        *it *= 2;  // Multiplicar cada valor por 2
    }

    // recorrer una lista con el iterador
    for (it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }

    // ejemplo con -- (Recordar ++var es mejor que var++)
    vector<int>::iterator it = vec.end();

    // Recorrer el vector al revés usando -- (it debe empezar en vec.end())
    while (it != vec.begin()) { // nos fijamos en que sea diferente porque si fuera igual no recorreriamos anda
        --it;  // es como ++it pero hacia atras 
        cout << *it << " ";
    }
    
    
    return 0;
}
