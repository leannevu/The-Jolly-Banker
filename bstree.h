#include "account.h"
#ifndef BSTREE_H_
#define BSTREE_H_

struct Node
{
	Account* pAcct;
	Node* right;
	Node* left;
};

class BSTree {

public:
	//constructor & destructor
	BSTree();
	BSTree(const BSTree& sourceList);
	~BSTree();

	//action
	bool Insert(Account*);
	bool Retrieve(const int& account_id, Account*& account) const;
	void Display();
	void Empty(Node* root);
	bool isEmpty() const;
	void Print();
	//Node* Remove(const int& account_id, Account*& acc);
	//Node* FindMin(Node* node); //used to find the minimum node to replace a removen node

	BSTree& operator=(const BSTree& list2);
	void CopyHelper(Node* root);
	friend ostream& operator<<(ostream& output, const BSTree& myTree);

private:
	//helper methods using recursion
	//Account* searchRecur(Node* input, const Account& toFind) const;
	bool insertRecur(Node*& input, Account* toFind);
	bool printRecur(Node* input);
	Node* root;

	
};

#endif