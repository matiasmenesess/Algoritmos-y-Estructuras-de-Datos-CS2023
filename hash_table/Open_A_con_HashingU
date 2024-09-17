#include <iostream>
#include <random>
#include <cmath>
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
    return (int)log2(key) + 1;
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
int hash_function(T key, int m) {
    int P = generarRandomPrimo(m);
    uniform_int_distribution<> dist(1, P - 1);
    int a = dist(gen);
    int b = dist(gen);
    int k = calcularBits(key);
    int index = ((a * k + b) % P) % m;
    return index;
}

template <typename T1, typename T2>
struct key_value {
    T1 key = T1();
    T2 value =T2();
};

template <typename T1, typename T2>
class Hash_Table {
    int current_size;
    int element_count;
    key_value<T1,T2>* table;

public:
    Hash_Table(int initial_size) {
        table = new key_value<T1,T2>[initial_size];
        current_size = initial_size;
        element_count = 0;
    }

    ~Hash_Table() {
        delete[] table;
    }

    void insert(T1 key, T2 value) {
        if (element_count >= current_size * 0.8) {
            resize();
        }
        int index = hash_function(key, current_size);
        while (table[index].key != T1()) {
            index = (index + 1) % current_size;
        }
        table[index].key = key;
        table[index].value = value;
        element_count++;
    }

    void resize() {
        int new_size = current_size * 2;
        key_value<T1, T2>* new_table = new key_value<T1, T2>[new_size];
        for (int i = 0; i < current_size; i++) {
            if (table[i].key != T1()) {
                int index = hash_function(table[i].key, new_size);
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

    T2* search_lineal(T1 key) { //O(n) peor caso, cambiaria si cambiasemos la hf
        for (int i = 0; i < current_size; i++) {
            if (table[i].key == key) {
                return &table[i].value;
            }
        }
        return nullptr;
    }

    void eliminate_lineal(T1 key) {
        for (int i = 0; i < current_size; i++) {
            if (table[i].key == key) {
                table[i].key = T1();
                table[i].value = T2();
                element_count--;
            }
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
};
int main() {
    Hash_Table<string, int> hashTable(10);

    hashTable.insert("key1", 10);
    hashTable.insert("key2", 20);
    hashTable.insert("key3", 30);

    hashTable.display();

    int* result = hashTable.search_lineal("key9");
    if (result) {
        cout << "Valor encontrado para 'key9': " << *result << endl;
    }
    else {
        cout << "'key2' no encontrado." << endl;
    }


    return 0;
}
