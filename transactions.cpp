#include "transactions.h"
#include <iostream>

Transactions::~Transactions() {
}

void Transactions::OpenAccount(int id, string last, string first) {
	Account* account = new Account(id, first, last);
	if (accounts.Retrieve(id, account)) { //retrieves account 
		cerr << "ERROR: Account " << id << " is already open. Transaction Failed." << endl; //error statement if account is open 

	}
	else {
		accounts.Insert(account);
	}
}

void Transactions::Deposit(int account_id, int fund_id, int amount) {
	Account* account;
	if (accounts.Retrieve(account_id, account)) { //retrieves account
		account->AddFund(fund_id, amount); //adds to the fund if account exists 
	}
	else {
		cerr << "ERROR: Account " << account_id << " not found. Deposit Transaction Failed." << endl; //error statement if account is not found 
	}
}

void Transactions::Withdraw(int account_id, int fund_id, int amount) {
	Account* account;
	if (accounts.Retrieve(account_id, account)) {
		account->SubtractFund(fund_id, amount);
	}
	else {
		cerr << "ERROR: Account " << account_id << " not found. Withdraw Transaction Failed." << endl; //error statement if account is not found 
		//return false;
	}
}

void Transactions::Transfer(int from_id, int from_fund_number, int to_id, int to_fund_number, int amount) {
	Account* to, * from;
	string toRecord;
	if (accounts.Retrieve(from_id, from) && accounts.Retrieve(to_id, to))
	{
		//linked fund withdrawals
		if (from_id == to_id) { //check if same account
			if ((from_fund_number == 0 && to_fund_number == 1) || (from_fund_number == 1 && to_fund_number == 0) || (from_fund_number == 2 && to_fund_number == 3) || (from_fund_number == 3 && to_fund_number == 2)) { //check linked funds within same account
				if (from->getBalance(from_fund_number) >= amount) { //fund balance is greater than amount wanted to withdraw
					//continue with send and get transaction without having to worry about linked funds transfers in the same account because it will be failed anyways
					if (from->SendTransaction(from_fund_number, to_id, to_fund_number, amount)) { //Runs true for either partial or full amount 
						to->GetTransaction(to_fund_number, from_id, from_fund_number, amount); //deposit transaction 
						//record history for receiving end of transfer
						toRecord = " T " + to_string(from_id) + " " + to_string(from_fund_number) + " " + to_string(to_id)
							+ " " + to_string(to_fund_number) + " " + to_string(amount) + "\n";
						to->RecordTransfer(toRecord, to_fund_number); //record transfers to (the from are already recorded in SendTransaction & GetTransaction)
					}
				} else { //withdrawal does not go through for a linked fund; resort as failed transaction because no partial transfers can be created so res
					toRecord = " T " + to_string(from_id) + " " + to_string(from_fund_number) + " " + to_string(to_id)
						+ " " + to_string(to_fund_number) + " " + to_string(amount) + " (Failed)\n";
					from->RecordTransfer(toRecord, from_fund_number); //record transfer for failed attempt
					to->RecordTransfer(toRecord, to_fund_number); // record transfer for failed attempt
				}
			} 
			else if (from->SendTransaction(from_fund_number, to_id, to_fund_number, amount)) { //Runs true for either partial or full amount 
				to->GetTransaction(to_fund_number, from_id, from_fund_number, amount); //deposit transaction 
				//record history for receiving end of transfer
				toRecord = " T " + to_string(from_id) + " " + to_string(from_fund_number) + " " + to_string(to_id)
					+ " " + to_string(to_fund_number) + " " + to_string(amount) + "\n";
				to->RecordTransfer(toRecord, to_fund_number); //record transfers to (the from are already recorded in SendTransaction & GetTransaction)
			} else { //non linked fund withdrawal record failure
				toRecord = " T " + to_string(from_id) + " " + to_string(from_fund_number) + " " + to_string(to_id)
					+ " " + to_string(to_fund_number) + " " + to_string(amount) + " (Failed)\n";
				from->RecordTransfer(toRecord, from_fund_number); //record transfer for failed attempt
				to->RecordTransfer(toRecord, to_fund_number); // record transfer for failed attempt
			}
		}
			//non linked fund withdrawals
			else if (from->SendTransaction(from_fund_number, to_id, to_fund_number, amount)) { //Runs true for either partial or full amount 
				to->GetTransaction(to_fund_number, from_id, from_fund_number, amount); //deposit transaction 
				//record history for receiving end of transfer
				toRecord = " T " + to_string(from_id) + " " + to_string(from_fund_number) + " " + to_string(to_id)
					+ " " + to_string(to_fund_number) + " " + to_string(amount) + "\n";
				to->RecordTransfer(toRecord, to_fund_number); //record transfers to (the from are already recorded in SendTransaction & GetTransaction)
			}
			//non linked fund withdrawal record failure
			else {
				toRecord = " T " + to_string(from_id) + " " + to_string(from_fund_number) + " " + to_string(to_id)
					+ " " + to_string(to_fund_number) + " " + to_string(amount) + " (Failed)\n";
				from->RecordTransfer(toRecord, from_fund_number); //record transfer for failed attempt
				to->RecordTransfer(toRecord, to_fund_number); // record transfer for failed attempt
			}
		
		}
	else {
		if (accounts.Retrieve(from_id, from)) {
			cerr << "ERROR: Account " << to_id << " not found. Transfer Transaction Failed." << endl; //error statement if account is not found 
		}
		else {
			cerr << "ERROR: Account " << from_id << " not found. Transfer Transaction Failed." << endl; //error statement if account is not found
		}
	}
}

void Transactions::Display(int account_id, int fund_id) {
	Account* account;
	if (accounts.Retrieve(account_id, account)) {
		account->DisplayTrans(fund_id);
	}
	else {
		cerr << "ERROR: Account " << account_id << " not found. Transaction Failed." << endl; //error statement if account is not found
	}
}

void Transactions::DisplayAll(int account_id) {
	Account* account;
	if (accounts.Retrieve(account_id, account)) { //retrieves account 
		account->DisplayAllTrans(); //prints the history of each fund 
		cout << endl;
	}
	else {
		cerr << "ERROR: Account " << account_id << " not found. Transaction Failed." << endl;
	}
}

void Transactions::PrintAll() {
	accounts.Print(); //prints accounts using bstree print method
}





