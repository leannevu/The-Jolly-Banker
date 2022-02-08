#ifndef BANKER_H_
#define BANKER_H_
#include "transactions.h"
#include<queue>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

class Banker {
public:
	~Banker();
	//read in a string of transactions from a file into an in-memory queue; check for errors
	void ReadFileTransactions(string file);

	void ExecuteFileTransactions();

	void Display();

private:
	queue<vector<string>> transactions_list_;
	Transactions trans_;
};

#endif

