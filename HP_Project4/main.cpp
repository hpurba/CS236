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

	// ORIGINAL CODE

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

	Interpreter interpreter;
	// Evaluate rules
	// database.addRules(parse.getRules());	// what I originally had
	interpreter.addDatabase(database.returnDatabaseRelations());
	interpreter.addRules(parse.getRules());

	// Process queries
	cout << "Query Evaluation\n";
	// Interpreter interpreter;
	interpreter.setupQuery(parse.getQueries());
	interpreter.processQuery();	// database.returnDatabaseRelations());







	//// FOR TESTING PUPOSES

	//DataBase database;

	//vector<Schemes> vectorOfSchemes;
	//vector<Facts> vectorOfFacts;
	//// Set up Relation Name and Schemes
	//
	//// alpha
	//vector<string> columnNames0 = { "cat", "dog", "fish"}; // "fish", "bird", "bunny"
	//Schemes scheme1("alpha", columnNames0);
	//// fill scheme with tuples
	//// Row 1
	//string factID1 = "alpha";      // name of table it belongs to
	//vector<string> stringListVector1 = { "1", "2", "5" };
	//Facts fact1(factID1, stringListVector1);
	//vectorOfFacts.push_back(fact1);
	//// Row 2
	//stringListVector1 = { "1", "4", "1" };
	//Facts fact2(factID1, stringListVector1);
	//vectorOfFacts.push_back(fact2);
	//// Row 3
	//stringListVector1 = { "6", "7", "4" };
	//Facts fact3(factID1, stringListVector1);
	//vectorOfFacts.push_back(fact3);
	//vectorOfSchemes.push_back(scheme1);	// Add Scheme
	//
	//// beta
	//vector<string> columnNames1 = { "cat", "fish", "bird", "bunny" };
	//Schemes scheme2("beta", columnNames1);
	//// fill scheme with tuples
	//// Row 1
	//factID1 = "beta";      // name of table it belongs to
	//stringListVector1 = { "1", "5", "2", "4" };
	//Facts fact4(factID1, stringListVector1);
	//vectorOfFacts.push_back(fact4);
	//// Row 2
	//stringListVector1 = { "4", "3", "2", "7" };
	//Facts fact5(factID1, stringListVector1);
	//vectorOfFacts.push_back(fact5);
	//// Row 3
	//stringListVector1 = { "1", "5", "8", "3" };
	//Facts fact6(factID1, stringListVector1);
	//vectorOfFacts.push_back(fact6);
	//// Row 4
	//stringListVector1 = { "6", "4", "9", "2" };
	//Facts fact7(factID1, stringListVector1);
	//vectorOfFacts.push_back(fact7);
	//vectorOfSchemes.push_back(scheme2);	// Add Scheme
	//// add facts to database
	//

	//// EMPTY
	//vector<string> columnNames = { "cat", "dog", "fish", "bird", "bunny" };
	//Schemes scheme3("gamma", columnNames);
	//// no tuples
	//vectorOfSchemes.push_back(scheme3);

	//// Add all the schemes into database.
	//database.setup(vectorOfSchemes);
	//database.addFacts(vectorOfFacts);
	//


	//// BUILDING RULES
	//vector<Rules> vectorOfRules;
	//// individual object specific variables
	//vector<HeadPredicate> headPredicateObj;
	//vector<Predicates> vectorOfPredicates; // holds vector of Predicate
	//string headPredicateID = "gamma";
	//vector<string> idList = { "cat", "dog", "fish", "bird", "bunny" };
	//HeadPredicate headPredicate( headPredicateID, idList);
	//headPredicateObj.push_back(headPredicate);
	//// alpha
	//string predicateID = "alpha";
	//vector<string> parametersVector0 = { "cat", "dog", "fish" };
	//Predicates firstPredicate(predicateID, parametersVector0);
	//vectorOfPredicates.push_back(firstPredicate);
	//// beta
	//predicateID = "beta";
	//vector<string> parametersVector1 = { "cat", "fish", "bird", "bunny" };
	//Predicates secondPredicate(predicateID, parametersVector1);
	//vectorOfPredicates.push_back(secondPredicate);
	//
	//Rules rule1( headPredicateObj, vectorOfPredicates);
	//vectorOfRules.push_back(rule1);

	//Interpreter interpreter;
	//interpreter.addDatabase(database.returnDatabaseRelations());
	//interpreter.addRules(vectorOfRules);


	return 0;
}
