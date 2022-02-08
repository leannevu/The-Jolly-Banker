#include "banker.h"
#include <iostream>

Banker::~Banker() {
}

void Banker::ReadFileTransactions(string file) {
	string readLine = "";
	vector<string> info;
	ifstream in_file;

	in_file.open(file);
	if (!in_file) {
		cout << "Cannot Open" << endl;
	}

	while (!in_file.eof()) {
		in_file >> readLine;
		info.push_back(readLine); //push the commands into a vector 
		if (info[0] == "O") { //separate elements based on char type
			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);
		} 
		else if (info[0] == "D") {
			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);
		}
		else if (info[0] == "W") {
			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);
		}
		else if (info[0] == "T") {
			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);
		}
		else if (info[0] == "F") {
			in_file >> readLine;
			info.push_back(readLine);

			in_file >> readLine;
			info.push_back(readLine);
		}
		else if (info[0] == "A") {
			in_file >> readLine;
			info.push_back(readLine);
		}

		transactions_list_.push(info); //input string vector into queue
		info.clear(); //clears the string vector 
	}
}

	void Banker::ExecuteFileTransactions() {
		vector<string> inputFile;

		while (!transactions_list_.empty()) //FIFO - calls methods according to queue
		{
			inputFile = transactions_list_.front();
			if (inputFile[0] == "O") { //opens if O is present 
				trans_.OpenAccount(stoi(inputFile[1]), inputFile[2], (inputFile[3]));
			}
			else if (inputFile[0] == "D") { //deposits if D is present 
				trans_.Deposit(stoi(inputFile[1]), stoi(inputFile[2]), stoi(inputFile[3]));
			}
			else if (inputFile[0] == "W") { //withdraws if W is present 
				trans_.Withdraw(stoi(inputFile[1]), stoi(inputFile[2]), stoi(inputFile[3]));
			}
			else if (inputFile[0] == "T") { //transfers if T is present 
				trans_.Transfer(stoi(inputFile[1]), stoi(inputFile[2]), stoi(inputFile[3]),
					stoi(inputFile[4]), stoi(inputFile[5]));
			}
			else if (inputFile[0] == "A") { //prints the history of all transactions of given account
				trans_.DisplayAll(stoi(inputFile[1]));
			}
			else if (inputFile[0] == "F") { //prints the history of a given fund
				trans_.Display(stoi(inputFile[1]), stoi(inputFile[2]));
			}

			transactions_list_.pop();
		}
	}

	void Banker::Display() {
		cout << "\nFINAL BALANCES" << endl;
		trans_.PrintAll(); //prints all accounts using PrintAll method 
	}
