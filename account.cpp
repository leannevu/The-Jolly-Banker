#include "account.h"
#include <iostream>

Account::Account(int ID, string first, string last) {
    //initalize data values
    first_ = first;
    last_ = last;
    id_ = ID;

    //put funds names into the array 
    funds_[0].setName("Money Market");
    funds_[1].setName("Prime Money Market");
    funds_[2].setName("Long-Term Bond");
    funds_[3].setName("Short-Term Bond");
    funds_[4].setName("500 Index Fund");
    funds_[5].setName("Capital Value Fund");
    funds_[6].setName("Growth Equity Fund");
    funds_[7].setName("Growth Index Fund");
}

Account::~Account() {
}

int Account::getID() const {
	return id_;
}

string Account::getFirst() const {
	return first_;
}

string Account::getLast() const {
	return last_;
}

int Account::getBalance(int fund_id) const {
    return funds_[fund_id].getBalance();
}

string Account::getFundName(int fund_id) const {
    return funds_[fund_id].getName();
}

void Account::setID(int num) {
    id_ = num;
}

void Account::setFirst(string name) {
    first_ = name;
}

void Account::setLast(string last) {
    last_ = last;
}

void Account::AddFund(int fund_id, int amount) {
    string toRecord = " D " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(amount) + "\n";
    funds_[fund_id].Deposit(amount);
    funds_[fund_id].recordTrans(toRecord);
}

void Account::SubtractFund(int fund_id, int amount) {
    string toRecord, partialToRecord;
    int remaining_amount_, partial_amount_;


    if (funds_[fund_id].Withdraw(amount)) { //withdraw successful - creates string for history
        toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(amount) + "\n";
    }
    else { //try withdrawing partial amounts if necessary
        if (fund_id == 0) {
            remaining_amount_ = (amount - funds_[0].getBalance());
            partial_amount_ = (amount - remaining_amount_);

                if (funds_[1].Withdraw(remaining_amount_)) { //try withdrawing using what the remaining amount would be
                    funds_[fund_id].Withdraw(partial_amount_); //continue withdrawing the given partial amount
                    partialToRecord = " W " + to_string(id_) + " " + to_string(1) + " " + to_string(remaining_amount_) +
                        "\n"; //record partial into the correct fund class
                    funds_[1].recordTrans(partialToRecord);
                    toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(partial_amount_) + "\n";

                }
                else { //record failed transaction if withdrawing from other fund is still too much
                    toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(amount) + " (Failed)\n";
                }
        }
        else if (fund_id == 1) { //repeat method based on appropriate fund
            remaining_amount_ = (amount - funds_[1].getBalance());
            partial_amount_ = (amount - remaining_amount_);
            if (funds_[0].Withdraw(remaining_amount_)) {
                funds_[fund_id].Withdraw(partial_amount_);
                partialToRecord = " W " + to_string(id_) + " " + to_string(0) + " " + to_string(remaining_amount_) +
                    "\n";
                funds_[0].recordTrans(partialToRecord);
                toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(partial_amount_) + "\n";

            }
            else {
                toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(amount) + " (Failed)\n";
            }
        }
        else if (fund_id == 2) {
            remaining_amount_ = (amount - funds_[2].getBalance());
            partial_amount_ = (amount - remaining_amount_);
            if (funds_[3].Withdraw(remaining_amount_)) {
                funds_[fund_id].Withdraw(partial_amount_);
                partialToRecord = " W " + to_string(id_) + " " + to_string(3) + " " + to_string(remaining_amount_) +
                    "\n";
                funds_[3].recordTrans(partialToRecord);
                toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(partial_amount_) + "\n";

            }
            else {
                toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(amount) + " (Failed)\n";
            }
        }
        else if (fund_id == 3) {
            remaining_amount_ = (amount - funds_[3].getBalance());
            partial_amount_ = (amount - remaining_amount_);
            if (funds_[2].Withdraw(remaining_amount_)) {
                funds_[fund_id].Withdraw(partial_amount_);
                partialToRecord = " W " + to_string(id_) + " " + to_string(2) + " " + to_string(remaining_amount_) +
                    "\n";
                funds_[2].recordTrans(partialToRecord);
                toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(partial_amount_) + "\n";

            }
            else {
                toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(amount) + " (Failed)\n";
            }
        }
        else { //funds 4-7 don't have linked funds; skip to failed transaction record
            toRecord = " W " + to_string(id_) + " " + to_string(fund_id) + " " + to_string(amount) + " (Failed)\n";
            cerr << "ERROR: Not Enough funds to withdraw " << amount << " from " << first_ << " " << last_ << " " << (funds_[fund_id].getName()) << " fund" << endl; //error statement if account is not found 

        }
    }
    funds_[fund_id].recordTrans(toRecord);

}

//comment 
void Account::DisplayTrans(int fund_id) {
    cout << "Transaction History for " << first_ << " " << last_ << " " << funds_[fund_id].getName() << ": $" << getBalance(fund_id) << endl;
    funds_[fund_id].printHistoryFund();
}

void Account::DisplayAllTrans() {
    cout << "Transaction History for " << first_ << " " << last_ << " " << "By Fund." << endl;
    for (int i = 0; i < 8; i++) {
        funds_[i].printHistory();
    }
}

bool Account::SendTransaction(int from_fund_id, int to_acc_id, int to_fund_id, int amount) {
    string toRecord, remainingRecord;
    int remaining_amount_, partial_amount_;
    if (funds_[from_fund_id].Withdraw(amount)) { //withdraw successful - creates string for history
         toRecord = " T " + to_string(id_) + " " + to_string(from_fund_id) + " " + to_string(to_acc_id) + " " + to_string(to_fund_id)
            	+ " " + to_string(amount) + "\n";
         funds_[from_fund_id].recordTrans(toRecord);
         return true;

    } else { //try other linked funds first
        if (from_fund_id == 0) {
            remaining_amount_ = (amount - funds_[0].getBalance());
            partial_amount_ = (amount - remaining_amount_);
            if (funds_[1].Withdraw(remaining_amount_)) { //try withdrawing using what the remaining amount would be
                funds_[from_fund_id].Withdraw(partial_amount_); //continue withdrawing the given partial amount
                remainingRecord = " T " + to_string(id_) + " " + to_string(from_fund_id) + " " + to_string(to_acc_id) + " " + to_string(to_fund_id)
                    + " " + to_string(remaining_amount_) + "\n"; //record partial into the correct fund class
                toRecord = " T " + to_string(id_) + " " + to_string(from_fund_id) + " " + to_string(to_acc_id) + " " + to_string(to_fund_id)
                    + " " + to_string(partial_amount_) + "\n";
                funds_[1].recordTrans(remainingRecord);
            }
            else { //record failed transaction if withdrawing from other fund is still too much
                cerr << "ERROR: Not Enough funds to transfer " << amount << " from " << first_ << " " << last_ << " " << (funds_[from_fund_id].getName()) << " fund" << endl; //error statement if account is not found 
                return false;
            }
        }
        else if (from_fund_id == 1) {
            remaining_amount_ = (amount - funds_[1].getBalance());
            partial_amount_ = (amount - remaining_amount_);
            if (funds_[0].Withdraw(remaining_amount_)) { //try withdrawing using what the remaining amount would be
                funds_[from_fund_id].Withdraw(partial_amount_); //continue withdrawing the given partial amount
                remainingRecord = " T " + to_string(id_) + " " + to_string(0) + " " + to_string(to_acc_id) + " " + to_string(to_fund_id)
                    + " " + to_string(remaining_amount_) + "\n"; //record partial into the correct fund class
                toRecord = " T " + to_string(id_) + " " + to_string(from_fund_id) + " " + to_string(to_acc_id) + " " + to_string(to_fund_id)
                    + " " + to_string(partial_amount_) + "\n";
                funds_[0].recordTrans(remainingRecord);
            }
            else { //record failed transaction if withdrawing from other fund is still too much
                cerr << "ERROR: Not Enough funds to transfer " << amount << " from " << first_ << " " << last_ << " " << (funds_[from_fund_id].getName()) << " fund" << endl; //error statement if account is not found 
                return false;
            }
        }
        else if (from_fund_id == 3) {
            remaining_amount_ = (amount - funds_[3].getBalance());
            partial_amount_ = (amount - remaining_amount_);
            if (funds_[2].Withdraw(remaining_amount_)) { //try withdrawing using what the remaining amount would be
                funds_[from_fund_id].Withdraw(partial_amount_); //continue withdrawing the given partial amount
                remainingRecord = " T " + to_string(id_) + " " + to_string(from_fund_id) + " " + to_string(to_acc_id) + " " + to_string(to_fund_id)
                    + " " + to_string(remaining_amount_) + "\n"; //record partial into the correct fund class
                toRecord = " T " + to_string(id_) + " " + to_string(from_fund_id) + " " + to_string(to_acc_id) + " " + to_string(to_fund_id)
                    + " " + to_string(partial_amount_) + "\n";
                funds_[2].recordTrans(remainingRecord);
            }
            else { //record failed transaction if withdrawing from other fund is still too much
                cerr << "ERROR: Not Enough funds to transfer " << amount << " from " << first_ << " " << last_ << " " << (funds_[from_fund_id].getName()) << " fund" << endl; //error statement if account is not found 
                return false;
            }
        }
        else if (from_fund_id == 2) {
            remaining_amount_ = (amount - funds_[2].getBalance());
            partial_amount_ = (amount - remaining_amount_);
            if (funds_[3].Withdraw(remaining_amount_)) { //try withdrawing using what the remaining amount would be
                funds_[from_fund_id].Withdraw(partial_amount_); //continue withdrawing the given partial amount
                remainingRecord = " T " + to_string(id_) + " " + to_string(from_fund_id) + " " + to_string(to_acc_id) + " " + to_string(to_fund_id)
                    + " " + to_string(remaining_amount_) + "\n"; //record partial into the correct fund class
                toRecord = " T " + to_string(id_) + " " + to_string(from_fund_id) + " " + to_string(to_acc_id) + " " + to_string(to_fund_id)
                    + " " + to_string(partial_amount_) + "\n";
                funds_[3].recordTrans(remainingRecord);
            }
            else { //record failed transaction if withdrawing from other fund is still too much
                cerr << "ERROR: Not Enough funds to transfer " << amount << " from " << first_ << " " << last_ << " " << (funds_[from_fund_id].getName()) << " fund" << endl; //error statement if account is not found 
                return false;

            }
        }
        else {
            cerr << "ERROR: Not Enough funds to transfer " << amount << " from " << first_ << " " << last_ << " " << (funds_[from_fund_id].getName()) << " fund" << endl; //error statement if account is not found 
            return false;
        }
        funds_[from_fund_id].recordTrans(toRecord);
        return true;
    }
}

bool Account::GetTransaction(int to_fund_id, int from_acc_id, int from_fund_id, int amount) {
    if (funds_[to_fund_id].Deposit(amount)) { //Deposit amount to the fund id receiving
        return true;
    }
    else {
        return false;
    }
}

void Account::RecordTransfer(string record, int fund_id) {
    funds_[fund_id].recordTrans(record);

}

ostream& operator<<(ostream& out, const Account& account) {
	out << account.getFirst() << " " << account.getLast() << " ID: " << account.getID() << endl;
	for (int i = 0; i < 8; i++)
	{
		out << " " << account.getFundName(i) << ": $" << account.getBalance(i);
		out << endl;
	}
	return out;
}