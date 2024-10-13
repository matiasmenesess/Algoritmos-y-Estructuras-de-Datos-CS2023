#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Heap {
    string type;
    vector<T> elements;

    void heapify_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (type == "MAX_HEAP") {
            if (left < elements.size() && elements[left] > elements[largest]) {
                largest = left;
            }
            if (right < elements.size() && elements[right] > elements[largest]) {
                largest = right;
            }
        } else if (type == "MIN_HEAP") {
            if (left < elements.size() && elements[left] < elements[largest]) {
                largest = left;
            }
            if (right < elements.size() && elements[right] < elements[largest]) {
                largest = right;
            }
        }

        if (largest != i) {
            swap(elements[i], elements[largest]);
            heapify_down(largest);
        }
    }

    void heapify_up(int i) {
        int parent = (i - 1) / 2;
        if (i && ((type == "MAX_HEAP" && elements[i] > elements[parent]) ||
                  (type == "MIN_HEAP" && elements[i] < elements[parent]))) {
            swap(elements[i], elements[parent]);
            heapify_up(parent);
        }
    }

public:
    Heap(string heapType) : type(heapType) {}

    void insert(T val) {
        elements.push_back(val);
        heapify_up(elements.size() - 1);
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

    T top() {
        if (elements.size() == 0) {
            throw out_of_range("Heap vacio");
        }
        return elements[0];
    }

    int size() {
        return elements.size();
    }
};
