#include "bstree.h"
#include <iostream>
using namespace std;

BSTree::BSTree() {
    this->root = NULL;
}

BSTree::BSTree(const BSTree& sourceList) {
     root = nullptr;
    *this = sourceList;
}

BSTree::~BSTree() {
    Empty(root); //empty BST; delete accs
}

bool BSTree::Insert(Account* acc) {
    if (root == NULL) {
        root = new Node;
        root->pAcct = acc;
        root->left = NULL;
        root->right = NULL;
        return true;
    }
    else {
        Node* curr = root;
        insertRecur(curr, acc); //helper method 
    }
    return true;
}

//retrives account
bool BSTree::Retrieve(const int& account_id, Account*& acc) const {
    Node* curr = root;
    bool found = false;
    while (!found) {
        if (curr != NULL && account_id == curr->pAcct->getID()) {
            found = true;
            acc = curr->pAcct;
            return found;
        }
        else if (curr != NULL && account_id > curr->pAcct->getID()) {
            curr = curr->right;
        }
        else if (curr != NULL && account_id < curr->pAcct->getID()) {
            curr = curr->left;
        }
        else {
            found = true;
        }

    }
    return false;
}

void BSTree::Display() {
    if (root == NULL) {
        cerr << "ERROR: ACCOUNT LIST IS EMPTY" << endl;
    }
    printRecur(root);
}

void BSTree::Empty(Node* root) {
    if (root->left != NULL)Empty(root->left);
    if (root->right != NULL)Empty(root->right);
    delete root->pAcct;
    delete root;
    root = NULL;
}

//checks to see if the tree is empty 
bool BSTree::isEmpty() const {
    if (root->left == NULL && root->right == NULL) {
        return true;
    }
    else {
        return false;
    }
}

//inserts the account using recursion 
bool BSTree::insertRecur(Node*& curr, Account* acc) {
    if (acc->getID() > curr->pAcct->getID()) {
        if (curr->right == NULL) {
            Node* insInTree = new Node();
            insInTree->pAcct = acc;
            insInTree->left = NULL;
            insInTree->right = NULL;
            curr->right = insInTree;
            return true;
        }
        else {
            return insertRecur(curr->right, acc);
        }

    }
    else if (acc->getID() < curr->pAcct->getID()) {
        if (curr->left == NULL) {
            Node* insInTree = new Node();
            insInTree->pAcct = acc;
            insInTree->left = NULL;
            insInTree->right = NULL;
            curr->left = insInTree;
            return true;
        }
        else {
            return insertRecur(curr->left, acc);
        }

    }
    else {
        cerr << "ERROR: Account " << acc->getID() << " is already open. Transaction refused." << endl;
        return false;
    }
}

//prints all the accounts in the tree 
bool BSTree::printRecur(Node* curr) {
    if (curr != NULL) {
        printRecur(curr->left);
        cout << *curr->pAcct << endl; //use ostream overload to print account (overloaded in both BST & Account class)
        printRecur(curr->right);
    }
    return true;
}

//prints the accounts in the tree 
void BSTree::Print() {
    printRecur(this->root); //prints using printRecurs method
}

//Node* FindMin(Node* node) {
//    Node* curr = node;
//
//    /* loop down to find the leftmost leaf */
//    while (curr->left != NULL)
//    {
//        curr = curr->left;
//    }
//    return(curr);
//}
//
//Node* BSTree::Remove(const int& account_id, Account*& acc) {
//    //if (root == NULL) return root;
//    //else if (data < root->pAcct->getID())  root->left = Remove(root->left, data);
//
//    Node* curr = root;
//    bool found = false;
//
//    if (curr->left == NULL && curr->right == NULL) {
//        delete curr;
//        root = NULL;
//    }
//    else if (curr->left == NULL) {
//        Node* temp = root;
//        root = root->right;
//        delete temp;
//    } 
//    else if (root -> right == NULL) {
//        Node* temp = root;
//        root = root->left;
//        delete temp;
//    }
//    else {
//        Node* temp = FindMin(root->right);
//        root->pAcct = temp->pAcct;
//        root->right->pAcct = Remove(root->right->pAcct->getID(), temp->pAcct);
//    }
//    return curr;
//}

BSTree& BSTree::operator=(const BSTree& list2)
{
    if (this == &list2)
    {
        return *this;
    }
    Empty(root);
    if (list2.root == nullptr)
    {
        return *this;
    }
    Node* copy = list2.root;
    CopyHelper(copy);
    return *this;
}

void BSTree::CopyHelper(Node* root)
{
    if (root != nullptr)
    {
        this->Insert(root->pAcct);
        CopyHelper(root->left);
        CopyHelper(root->right);
    }
}


//operator overload for binary search tree 
ostream& operator<<(ostream& output, const BSTree& myTree) {
    output << myTree.root->pAcct;
    return output;
}
