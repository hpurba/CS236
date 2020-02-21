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
	// string fileName = argv[1];

	//vector<Tokenizer> vectorOfTokens;
	//Scanner scan;

	//// Scan to create vector of token objects
	//vectorOfTokens = scan.scan_Identify(fileName);

	//Parser parse;	// Checks the grammar
	//parse.parse(vectorOfTokens);

	// SETS UP THE TABLE NAME AND THE HEADERS
	vector<Schemes> vectorOfSchemes;
	vector<string> idListVector = {"Dog", "Cat", "Sheep"};
	Schemes scheme("Animal", idListVector);	// "Animal" is the name of the table
	vectorOfSchemes.push_back(scheme);

	// FILLS THE TABLE!
	vector<Facts> vectorOfFacts;
	string factID1 = "Animal";	// name of table it belongs to
	vector<string> stringListVector1 = {"'Bill'", "'Joe'", "'Matt'"};
	Facts fact1(factID1, stringListVector1);
	vectorOfFacts.push_back(fact1);
	// ROW 2
	string factID2 = "Animal";	// name of table it belongs to
	vector<string> stringListVector2 = { "'Sam'", "'Sam'", "'James'"};
	Facts fact2(factID2, stringListVector2);
	vectorOfFacts.push_back(fact2);



	DataBase database;
	database.setup(vectorOfSchemes);
	database.addFacts(vectorOfFacts);
	database.printRelations();
	

	//DataBase database;
	//database.setup(parse.getSchemes());	// sets up the database from all the vectors from the parser
	//database.addFacts(parse.getFacts());
	

	// THIS WAS WORKING
	//Interpreter queries;
	//queries.setup(parse.getQueries());
	//queries.process(database.returnDatabaseRelations());	// database.returnDatabaseRelations()



	Interpreter queries;
	// QUERY 1	-	SELECT type 1 - where it is joe
	string predicateID = "Animal";	// name of table
	vector<string> parametersVector = {"A", "'Joe'", "B"};
	Predicates query1(predicateID, parametersVector);

	// QUERY 2	-	SELECT type 2	-	Two entries are the same
	string predicateID2 = "Animal";	// name of table
	vector<string> parametersVector2 = { "A", "A", "C"};
	Predicates query2(predicateID2, parametersVector2);

	// QUERY 3	-	SELECT - DOESNT EXIST (Greg)
	string predicateID3 = "Animal";	// name of table
	vector<string> parametersVector3 = { "'Greg'", "Z", "R" };
	Predicates query3(predicateID3, parametersVector3);

	// QUERY 4	-	PROJECT		-	gets columns . Dog, Cat, Sheep
	string predicateID4 = "Animal";	// name of table
	vector<string> parametersVector4 = { "Dog", "Cat"};
	Predicates query4(predicateID4, parametersVector4);

	// QUERY 5	 RENAME	-	Dog, Dog, Zebra
	string predicateID5 = "Animal";	// name of table
	vector<string> parametersVector5 = { "Dog", "Cat", "Zebra"};
	Predicates query5(predicateID5, parametersVector5);

	
	
	vector<Predicates> vectorOfQueries;
	vectorOfQueries.push_back(query1);
	vectorOfQueries.push_back(query2);
	vectorOfQueries.push_back(query3);
	vectorOfQueries.push_back(query4);
	vectorOfQueries.push_back(query5);


	queries.setupQuery(vectorOfQueries);
	queries.process(database.returnDatabaseRelations());
	






	return 0;
}
