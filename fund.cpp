#include "fund.h"
#include <string>

Fund::Fund() {
	amount_ = 0;
	name_ = "";
}

Fund::~Fund() {
}

int Fund::getBalance() const {
	return amount_;
}

string Fund::getName() const {
	return name_;
}

bool Fund::setName(string name) {
	name_ = name;
	return true;
}

bool Fund::Deposit(int num) {
	amount_ += num;
	return true;
}

bool Fund::Withdraw(int num) {
	if (num > amount_) { //check if amount wanted to withdraw is too large
		return false;
	} else {
		amount_ -= num;
		return true;
	}
}

bool Fund::recordTrans(string record) {
	history_.push_back(record);
	return true;
}

void Fund::printHistory() {
	if (history_.size() == 0) {
		return;
	}
	else {
		cout << name_ << ": $" << amount_ << endl; //include the name of the chosen fund
		for (int i = 0; i < history_.size(); i++) { //print history records of fund
			cout << history_[i];
		}
	}
}

void Fund::printHistoryFund() {
	if (history_.size() == 0) {
		return;
	}
	else {
		for (int i = 0; i < history_.size(); i++) { 
			cout << history_[i]; //print history records of fund
		}
	}
}
