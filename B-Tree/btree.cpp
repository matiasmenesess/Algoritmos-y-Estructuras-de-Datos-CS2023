//Integrantes:
//1. Olivares Sarmiento, Javier Ignacio Leon
//2. Silva Reyes, Santiago Miguel
//3. Meneses Roncal, Matias Alonso
// C++ program for B-Tree insertion
#include<iostream>
using namespace std;

// A BTree node
class BTreeNode
{
    int *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int _t, bool _leaf);   // Constructor

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k);

    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A function to search a key in the subtree rooted with this node.
    BTreeNode *search(int k);   // returns NULL if k is not present.

// Make BTree friend of this so that we can access private members of this
// class in BTree functions
    friend class BTree;
};

// A BTree
class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum degree
public:
    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {  root = NULL;  t = _t; }

    // function to traverse the tree
    void traverse()
    {  if (root != NULL) root->traverse(); }

    // function to search a key in this tree
    BTreeNode* search(int k)
    {  return (root == NULL)? NULL : root->search(k); }

    // The main function that inserts a new key in this B-Tree
    void insert(int k);
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1)
{

    t = t1;
    leaf = leaf1;


    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];


    n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{

    int i;
    for (i = 0; i < n; i++)
    {

        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }


    if (leaf == false)
        C[i]->traverse();
}


BTreeNode *BTreeNode::search(int k)
{

    int i = 0;
    while (i < n && k > keys[i])
        i++;


    if (keys[i] == k)
        return this;


    if (leaf == true)
        return NULL;


    return C[i]->search(k);
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(int k)
{
    if(root ==NULL){
        auto* NewNode = new BTreeNode(t, true);
        NewNode->keys[0] = k;
        NewNode->n = NewNode->n + 1;
        root = NewNode;
    }
    else{
        if(2*t-1 == root->n){
            auto* NewNode = new BTreeNode(t, false);
            int index=0;
            NewNode->C[index] = root;
            NewNode->splitChild(index,root);
            if(NewNode->keys[0]<k){
                index++;
            }
            NewNode->C[index]->insertNonFull(k);
            root=NewNode;
    
        }
        else{
            root->insertNonFull(k);
        }
    }
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(int k)
{

    int i = n-1;


    if (leaf == true)
    {

        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }


        keys[i+1] = k;
        n = n+1;
    }
    else
    {

        while (i >= 0 && keys[i] > k)
            i--;


        if (C[i+1]->n == 2*t-1)
        {

            splitChild(i+1, C[i+1]);

            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{

    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;


    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];


    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }


    y->n = t - 1;


    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];


    C[i+1] = z;


    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];


    keys[i] = y->keys[t-1];


    n = n + 1;
}

// Driver program to test above functions
int main()
{
    BTree t(3); // A B-Tree with minimum degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed tree is ";
    t.traverse();

    int k = 6;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";

    k = 15;
    (t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present";

    return 0;
}
