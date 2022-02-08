#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
using namespace std;
#include "fund.h"

class Account {
public:
	Account(int id, string first, string last);
	~Account();

	int getID() const;
	string getFirst() const;
	string getLast() const;
	int getBalance(int fundNumber) const;
	string getFundName(int fundNumber) const;

	void setID(int num);
	void setFirst(string name);
	void setLast(string last);

	//access chosen fund class; use Fund[i].Deposit method and Fund[i].recordTrans method
	void AddFund(int fund_id, int amount);
	//access chosen fund class; use Fund[i].Withdraw method and Fund[i].recordTrans method
	void SubtractFund(int fund_id, int amount);

	//access chosen fund class; use Fund[i].PrintHistory method
	void DisplayTrans(int fund_id);
	//access all fund class; use Fund[0-7].PrintHistory method
	void DisplayAllTrans();	
	//access chosen fund class; use Fund[0-7].Withdraw method and Fund[i].recordTrans method
	bool SendTransaction(int from_fund_id, int to_acc_id, int to_fund_id, int amount);
	//access chosen fund class; use Fund[0-7].Deposit method and Fund[i].recordTrans method
	bool GetTransaction(int to_fund_id, int from_acc_id, int from_fund_id, int amount);

	void RecordTransfer(string record, int fund_id);

	//overload operator; print fund balances of account
	friend ostream& operator<<(ostream& out, const Account& account);

private:
	int id_;
	string first_;
	string last_;
	int fund_id_;
	Fund funds_[8];
};

#endif