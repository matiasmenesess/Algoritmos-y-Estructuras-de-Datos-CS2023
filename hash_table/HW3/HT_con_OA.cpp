#include <iostream>
#include <random>
#include <vector>
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
struct key_value {
    T1 key = T1();
    T2 value = T2();
};

template <typename T1, typename T2>
class Hash_Table {
    int current_size;
    int element_count;
    int a;
    int b;
    int P;
    key_value<T1, T2>* table;

    int encontrarIndex(T1 key, int m) {
        int index = hash_function(key, m, a, b, P);
        int original_index = index;

        while (table[index].key != T1()) {
            if (table[index].key == key) {
                return index;
            }
            index = (index + 1) % m;
            if (index == original_index) break;
        }

        return index;
    }

public:
    Hash_Table(int initial_size) {
        table = new key_value<T1, T2>[initial_size];
        current_size = initial_size;
        element_count = 0;

        P = generarRandomPrimo(initial_size);
        uniform_int_distribution<> dist(1, P - 1);
        a = dist(gen);
        b = dist(gen);
    }

    ~Hash_Table() {
        delete[] table;
    }

    void insert(T1 key, T2 value) {
        if (element_count >= current_size * 0.8) {
            resize();
        }

        int index = encontrarIndex(key, current_size);

        if (table[index].key == T1()) {
            table[index].key = key;
            table[index].value = value;
            element_count++;
        }
    }


    void resize() {
        int new_size = current_size * 2;

        P = generarRandomPrimo(new_size);

        uniform_int_distribution<> dist(1, P - 1);
        a = dist(gen);
        b = dist(gen);

        key_value<T1, T2>* new_table = new key_value<T1, T2>[new_size];
        for (int i = 0; i < new_size; ++i) {
            new_table[i] = key_value<T1, T2>();
        }

        for (int i = 0; i < current_size; i++) {
            if (table[i].key != T1()) {
                int index = hash_function(table[i].key, new_size, a, b, P);
                while (new_table[index].key != T1()) {
                    index = (index + 1) % new_size;
                }
                new_table[index].key = table[i].key;
                new_table[index].value = table[i].value;
            }
        }

        delete[] table;
        table = new_table;
        current_size = new_size;
    }

    T2* search(T1 key) {
        int index = encontrarIndex(key, current_size);
        if (table[index].key == key) {
            return &table[index].value;
        }
        return nullptr;
    }

    void eliminate(T1 key) {
        int index = encontrarIndex(key, current_size);
        if (table[index].key == key) {
            table[index].key = T1();
            table[index].value = T2();
            element_count--;
        }
    }

    bool isEmpty() const {
        return element_count == 0;
    }

    void display() {
        for (int i = 0; i < current_size; i++) {
            if (table[i].key != T1()) {
                cout << "Index: " << i << " | Key: " << table[i].key << " | Value: " << table[i].value << endl;
            }
        }
    }

    int getElementCount() const {
        return element_count;
    }
};
