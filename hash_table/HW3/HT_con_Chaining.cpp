#include <iostream>
#include <random>
using namespace std;

random_device rd;
mt19937 gen(rd());

int calcularBits(const string& key) {
    return key.length() * 8;
}

int calcularBits(const char& key) {
    return 8;
}

int calcularBits(const int& key) {
    if (key == 0) return 1;
    int bits = 0;
    int value = key;
    while (value > 0) {
        bits++;
        value >>= 1;
    }
    return bits;
}

bool esPrimo(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int generarRandomPrimo(int m) {
    uniform_int_distribution<> dist(m * 2, m * 10);
    int primo;
    do {
        primo = dist(gen);
    } while (!esPrimo(primo));

    return primo;
}

template <typename T>
int hash_function(T key, int m, int a, int b, int P) {
    int k = calcularBits(key);
    return ((a * k + b) % P) % m;
}

template <typename T1, typename T2>
struct Node {
    pair<T1, T2> data;
    Node<T1, T2>* prev = nullptr;
    Node<T1, T2>* next = nullptr;
};

template <typename T1, typename T2>
class Double_Linked_List {
private:
    Node<T1, T2>* head = nullptr;
    Node<T1, T2>* tail = nullptr;

public:
    bool empty() const {
        return head == nullptr;
    }

    Node<T1, T2> *getHead() const {
        return head;
    }

    void push_back(T1 key, T2 value) {
        Node<T1, T2>* newNode = new Node<T1, T2>;
        newNode->data = make_pair(key, value);
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail == nullptr) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    void remove(T1 key) {
        if (empty()) return;

        Node<T1, T2>* temp = head;
        while (temp != nullptr) {
            if (temp->data.first == key) {
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
                return;
            }
            temp = temp->next;
        }
    }

    T2* search(T1 key) {
        Node<T1, T2>* temp = head;
        while (temp != nullptr) {
            if (temp->data.first == key) {
                return &temp->data.second;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void display() const {
        Node<T1, T2>* temp = head;
        while (temp != nullptr) {
            cout << "(" << temp->data.first << ", " << temp->data.second << ") ";
            temp = temp->next;
        }
        cout << endl;
    }
};

template <typename T1, typename T2>
class Hash_Table {
    int current_size;
    int a, b, P, element_count;
    Double_Linked_List<T1, T2>* table;

public:
    Hash_Table(int size) {
        current_size = size;
        table = new Double_Linked_List<T1, T2>[current_size];
        element_count = 0;
        P = generarRandomPrimo(current_size);
        uniform_int_distribution<> dist(1, P - 1);
        a = dist(gen);
        b = dist(gen);
    }

    ~Hash_Table() {
        delete[] table;
    }

    void insert(T1 key, T2 value) {
        double fillFactor = (double) element_count / (current_size * 3); // k es 3 como en la diapo maxColision

        if (fillFactor >= 0.5) {
            resize();
        }

        int index = hash_function(key, current_size, a, b, P);
        table[index].push_back(key, value);
        element_count++;
    }

    void resize() {
        int new_size = current_size * 2;
        Double_Linked_List<T1, T2>* new_table = new Double_Linked_List<T1, T2>[new_size];

        P = generarRandomPrimo(new_size);
        uniform_int_distribution<> dist(1, P - 1);
        a = dist(gen);
        b = dist(gen);

        for (int i = 0; i < current_size; ++i) {
            Node<T1, T2>* temp = table[i].getHead();
            while (temp != nullptr) {
                int new_index = hash_function(temp->data.first, new_size, a, b, P);
                new_table[new_index].push_back(temp->data.first, temp->data.second);
                temp = temp->next;
            }
        }

        delete[] table;

        table = new_table;
        current_size = new_size;
    }

    T2* search(T1 key) {
        int index = hash_function(key, current_size, a, b, P);
        return table[index].search(key);
    }

    void eliminate(T1 key) {
        int index = hash_function(key, current_size, a, b, P);
        if (!table[index].empty()) {
            table[index].remove(key);
            element_count--;
        }
    }

    void display() {
        for (int i = 0; i < current_size; ++i) {
            if (!table[i].empty()) {
                cout << "Index " << i << ": ";
                table[i].display();
            }
        }
    }
};

int main(){


  return 0;
}
