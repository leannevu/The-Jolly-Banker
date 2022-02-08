#include "banker.h"

int main(int argc, char* argv[]) {
	
	Banker bank;
	bank.ReadFileTransactions(argv[1]);
	bank.ExecuteFileTransactions();
	bank.Display();
}