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

public:
    BSTree() : root(nullptr), contador_de_elementos(0) {}

    ~BSTree() {
        clear(root);
    }

    NodeBT<T> *getRoot() const {
        return root;
    }

    void setRoot(NodeBT<T> *root) {
        BSTree::root = root;
    }

    bool balanceadooooo(){
        return balanceado(root);
    }

    void insert(T value) {
        insert_funcion(root, value);
        contador_de_elementos++;
    }

    bool find(T value) {
        return find_funcion(root, value);
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


template <typename T>
void insert_funcion(NodeBT<T>*& node, T value) {
    if (node == nullptr) {
        node = new NodeBT<T>{value};
    } else if (value < node->data) {
        insert_funcion(node->left, value);
    } else if (value > node->data) {
        insert_funcion(node->right, value);
    }
}

template <typename T>
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

template <typename T>
NodeBT<T>* predecesor_funcion(NodeBT<T>*& node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template <typename T>
void PreOrder(NodeBT<T>* node) {
    if (node == nullptr) return;
    cout << node->data << " "; // IMPRIME - IZQUIERDA - DERECHA
    PreOrder(node->left);
    PreOrder(node->right);
}


template <typename T>
void PostOrder(NodeBT<T>* node) {
    if (node == nullptr) return;
    PostOrder(node->left); //IZQ - DERECHA - IMPRIME
    PostOrder(node->right);
    cout << node->data << " ";
}

template <typename T>
void clear(NodeBT<T>* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
int height(NodeBT<T>* root)
{
    if (root == nullptr) {
        return 0;
    }

    return 1 + max(height(root->left), height(root->right));
}

template <typename T>
bool balanceado(NodeBT<T>* node){

    if(node== nullptr){
        return true;
    }

    if((abs(height(node->right) - height(node->left)))<=1){
        return (balanceado(node->left) && balanceado(node->right));
    }
    else{
        return false;
    }
}

template <typename T>
bool find_funcion(NodeBT<T>* node, T value) {
    if (node == nullptr) {
        return false;
    } else if (node->data == value) {
        return true;
    } else if (value < node->data) {
        return find_funcion(node->left, value);
    } else {
        return find_funcion(node->right, value);
    }
}


template <typename T>
void InOrder(NodeBT<T>* node) {
    if (node == nullptr) return;
    InOrder(node->left); //IZQ - IMPRIME - DERECHA
    cout << node->data << " ";
    InOrder(node->right);
}

int main() {
    BSTree<int> bst;

    bst.insert(5);
    bst.insert(6);
    bst.insert(7);
    bst.insert(8);
    bst.insert(9);

    return 0;
}
