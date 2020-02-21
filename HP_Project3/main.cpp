// HP_Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser.h"
#include "scanner.h"
#include "interpreter.h"
#include "database.h"

using namespace std;

int main(int argc, char *argv[]) {
	string fileName = argv[1];

	vector<Tokenizer> vectorOfTokens;
	Scanner scan;

	// Scan to create vector of token objects
	vectorOfTokens = scan.scan_Identify(fileName);

	Parser parse;	// Checks the grammar
	parse.parse(vectorOfTokens);



	DataBase database;
	database.setup(parse.getSchemes());	// sets up the database from all the vectors from the parser
	database.addFacts(parse.getFacts());
	// database.printRelations();


	// attempt
	// vector<Predicates> queries = parse.getQueries();
	// Interpreter interpret;
	// interpret = Interpreter(database, queries);

	// THIS WAS WORKING
	Interpreter queries;
	queries.setupQuery(parse.getQueries());
	queries.process(database.returnDatabaseRelations());	// database.returnDatabaseRelations()




	return 0;
}
