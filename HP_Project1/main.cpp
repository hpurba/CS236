// HP_Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "scanner.h"

using namespace std;

int main(int argc, char *argv[]) {

	string fileName = argv[1];

	vector<Tokenizer> vectors;
	Scanner scan;
	
	// Scan to create vector of token objects
	vectors = scan.scan_Identify(fileName);
	
	for (unsigned int i = 0; i < vectors.size(); i++)
	{
		cout << vectors[i].printToken();
	} 
	cout << "Total Tokens = " << scan.getNumTokens() << "\n";
	return 0;
}
