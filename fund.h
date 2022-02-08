#ifndef FUND_H_
#define FUND_H_
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Fund {
public:
	//instantiate fund amount to 0
	Fund();
	~Fund();
	//Fund(string fund_name);
	
	int getBalance() const;
	string getName() const;

	bool setName(string name);

	//change fund amount
	bool Deposit(int num);
	bool Withdraw(int num);

	//keep track of history in given fund
	bool recordTrans(string record);
	//vector<string> getFundTrans() const;
	void printHistory();
	void printHistoryFund();
	//string DisplayHistory();

private:
	string name_;
	//int fund_id_;
	int amount_;
	vector<string> history_;
};

#endif

