#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template<typename T>
struct NodeBT {
    T data;
    NodeBT *left = nullptr;
    NodeBT *right = nullptr;
};

template<typename T>
class Stack {

    vector<T> stack_;
    int max_size;

public:

    Stack(int size) : max_size(size) {}

    void push(T val) {
        if (stack_.size() != max_size) {
            stack_.push_back(val);
        } else {
            cout << "Stack is full!" << endl;
        }
    }

    void pop() {
        if (!stack_.empty()) {
            stack_.pop_back();
        } else {
            cout << "Stack is empty!" << endl;
        }
    }

    bool isempty() {
        return stack_.size() == 0;
    }

    bool isfull() {
        return stack_.size() == max_size;
    }

    T top() {
        return stack_.back();
    }
};

template<typename T>
struct Node {
    T data;
    Node<T> *prev = nullptr;
    Node<T> *next = nullptr;
};

template<typename T>
class Double_Linked_List {
private:
    Node<T>* front = nullptr;
    Node<T>* rear = nullptr;
    int size = 0;

public:
    T front_() {
        return front->data;
    }

    T rear_() {
        return rear->data;
    }

    bool empty() {
        return front == nullptr;
    }

    void push_back(T value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = rear;

        if (rear == nullptr) {
            front = newNode;
        } else {
            rear->next = newNode;
        }
        rear = newNode;
        size++;
    }

    void pop_front() {
        if (front == nullptr) {
            return;
        }
        Node<T>* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        } else {
            front->prev = nullptr;
        }
        delete temp;
        size--;
    }

    int getSize() const {
        return size;
    }
};

template<typename T>
class Queue {
    Double_Linked_List<T> queue_;
    int max_size;

public:
    Queue(int size) : max_size(size) {}

    bool isempty() {
        return queue_.empty();
    }

    bool isfull() const {
        return queue_.getSize() == max_size;
    }

    T front() {
        return queue_.front_();
    }

    void enqueue(T val) {
        if (isfull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        queue_.push_back(val);
    }

    void dequeue() {
        if (isempty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        queue_.pop_front();
    }

    int getSize() const {
        return queue_.getSize();
    }
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

    void insert(T value) {
        insert_funcion(root, value);
        contador_de_elementos++;
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

    vector<T> getInOrder() {
        vector<T> vec;
        inOrder(root, vec);
        return vec;
    }

    void eliminar(T value) {
        Borrar(root, value);
    }

    bool balanceadooooo(){
        return balanceado(root);
    }

    void BreadthFirstSearch() {
        Queue<NodeBT<T>*> queue(100); //maxsize100 pq si
        queue.enqueue(root);
        while (!queue.isempty()) {
            NodeBT<T>* node = queue.front();
            queue.dequeue();
            cout << node->data << " ";
            if (node->left != nullptr)
                queue.enqueue(node->left);
            if (node->right != nullptr)
                queue.enqueue(node->right);
        }
        cout << endl;
    }

    template<typename F>
    void DepthFirstSearch(F process) {
        Stack<NodeBT<T>*> stack(100);
        stack.push(this->root);
        while (!stack.isempty()) {
            NodeBT<T>* node = stack.top();
            stack.pop();
            process(node->data);
            if (node->right != nullptr)
                stack.push(node->right);
            if (node->left != nullptr)
                stack.push(node->left);
        }
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
    cout << node->data << " ";
    PreOrder(node->left);
    PreOrder(node->right);
}

template <typename T>
void PostOrder(NodeBT<T>* node) {
    if (node == nullptr) return;
    PostOrder(node->left);
    PostOrder(node->right);
    cout << node->data << " ";
}

template <typename T>
void InOrder(NodeBT<T>* node) {
    if (node == nullptr) return;
    InOrder(node->left);
    cout << node->data << " ";
    InOrder(node->right);
}

template <typename T>
void inOrder(NodeBT<T>* node, vector<T>& vec) {
    if (node == nullptr) return;
    inOrder(node->left, vec);
    vec.push_back(node->data);
    inOrder(node->right, vec);
}

template <typename T>
void clear(NodeBT<T>* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
int height(NodeBT<T>* root) {
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
bool CompararSiEsMismoArbol(NodeBT<T>* A1, NodeBT<T>* A2) {
    if (A1 == nullptr && A2 == nullptr) return true;
    if (A1 == nullptr || A2 == nullptr) return false;
    if (A1->data != A2->data) return false;
    return CompararSiEsMismoArbol(A1->left, A2->left) && CompararSiEsMismoArbol(A1->right, A2->right);
}

template <typename T>
bool EsSubArbol(NodeBT<T>* root, NodeBT<T>* subRoot) {
    if (root == nullptr) return false;
    if (CompararSiEsMismoArbol(root, subRoot)) return true;
    return EsSubArbol(root->left, subRoot) || EsSubArbol(root->right, subRoot);
}

int main() {
    BSTree<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);

    cout << "In-Order traversal: ";
    bst.inOrder();

    cout << "Pre-Order traversal: ";
    bst.preOrder();

    cout << "Post-Order traversal: ";
    bst.postOrder();

    cout << "BFS traversal: ";
    bst.BreadthFirstSearch();

    return 0;
}
