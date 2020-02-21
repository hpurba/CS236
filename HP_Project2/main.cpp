// HP_Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "scanner.h"
#include "parser.h"

using namespace std;

int main(int argc, char *argv[]) {

	string fileName = argv[1];

	vector<Tokenizer> vectors;
	Scanner scan;
	
	// Scan to create vector of token objects
	vectors = scan.scan_Identify(fileName);
	
	/*
	// Print the Tokens
	for (unsigned int i = 0; i < vectors.size(); i++)
	{
		cout << vectors[i].printToken();
	} 
	cout << "Total Tokens = " << scan.getNumTokens() << "\n";
	*/

	// give the vector of tokens to the parser
	// parser will check if it is a valid grammer
	Parser parse;
	parse.parse(vectors);
	
	return 0;
}







// I've updated the trace that you are required to submit as part of project 2 so that you don't have to do as much. In fact, there is an error in the datalog program -- the fact in the datalog program isn't followed by a period. End your trace when you reach the error. Be sure to be able to show the TA how your code detects the error.
// https://mail.google.com/mail/u/0/#search/datalog/FMfcgxwDrRXKcfMSGbcDjDZrNXGRPjvX
