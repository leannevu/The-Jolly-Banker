#ifndef TRANSACTIONS_H_
#define TRANSACTIONS_H_
#include "account.h"
#include "bstree.h"

class Transactions {
public:
	~Transactions();

	void OpenAccount(int id, string last, string first); //opens a new account object & insert into BST

	void Deposit(int account_id, int fund_id, int amount); //figure out what specific account and fund to deposit

	void Withdraw(int account_id, int fund_id, int amount); //figure out what specifc account and fund to withdraw

	//Uses deposit and withdraw from fund class , also figures out what specific account and fund. Goes through a
	//number of test cases for linked funds, non linked funds, same acc ID
	void Transfer(int from_id, int from_fund_number, int to_id, int to_fund_number, int amount); 

	void Display(int account_id, int fund_id); //individual fund history

	void DisplayAll(int account_id); //add up all fund history

	void PrintAll(); //prints the transactions 

private:
	BSTree accounts;  //tree that holds all the variables 
};

#endif

