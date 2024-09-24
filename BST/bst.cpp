#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct NodeBT {
    T data;
    NodeBT *left = nullptr;
    NodeBT *right = nullptr;
};

template <typename T>
class BSTree {

    NodeBT<T> *root;
    int contador_de_elementos;

    void insert_funcion(NodeBT<T>*& node, T value) {
        if (node == nullptr) {
            node = new NodeBT<T>{value};
        } else if (value < node->data) {
            insert_funcion(node->left, value);
        } else if (value > node->data) {
            insert_funcion(node->right, value);
        }
    }

    void Borrar(NodeBT<T>*& node, T value) {
        if (node == nullptr) return;

        if (value < node->data) {
            Borrar(node->left, value);
        }
        else if (value > node->data) {
            Borrar(node->right, value);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr) {
                NodeBT<T>* temp = node;
                node = node->right;
                delete temp;
            }
            else if (node->right == nullptr) {
                NodeBT<T>* temp = node;
                node = node->left;
                delete temp;
            } else {
                NodeBT<T>* pred = predecesor_funcion(node->left);
                node->data = pred->data;
                Borrar(node->left, pred->data);
            }
        }
    }

    NodeBT<T>* predecesor_funcion(NodeBT<T>*& node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    void PreOrder(NodeBT<T>* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        PreOrder(node->left);
        PreOrder(node->right);
    }

    void InOrder(NodeBT<T>* node) {
        if (node == nullptr) return;
        InOrder(node->left);
        cout << node->data << " ";
        InOrder(node->right);
    }

    void PostOrder(NodeBT<T>* node) {
        if (node == nullptr) return;
        PostOrder(node->left);
        PostOrder(node->right);
        cout << node->data << " ";
    }

    // clear
    void clear(NodeBT<T>* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BSTree() : root(nullptr), contador_de_elementos(0) {}

    ~BSTree() {
        clear(root);
    }

    void insert(T value) {
        insert_funcion(root, value);
        contador_de_elementos++;
    }

    bool find(T value) {
        return find(root, value);
    }

    NodeBT<T>* predecesor() {
        return predecesor_funcion(root->left);
    }

    void preOrder() {
        PreOrder(root);
        cout << endl;
    }

    void inOrder() {
        InOrder(root);
        cout << endl;
    }

    void postOrder() {
        PostOrder(root);
        cout << endl;
    }

    void eliminar(T value) {
        Borrar(root, value);
    }
};

int main() {
    BSTree<int> bst;

    bst.insert(5);
    bst.insert(3);
    bst.insert(9);
    bst.insert(1);
    bst.insert(4);
    bst.insert(12);
    bst.insert(11);

    cout << "arbol antes de eliminar: ";
    bst.inOrder();

    bst.eliminar(3);

    cout << "arbol despues de eliminar: ";
    bst.inOrder();

    return 0;
}
