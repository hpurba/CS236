/*
Relation
- interprates the relational database

// FUNCTIONS
- select (grabs rows/tuples where the select matches for that column)
- project (grabs only the columns asked for)
- rename (Rename the columns)

*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<set>
#include<vector>
#include <map>
#include "database.h"

using namespace std;

class Interpreter {
private:
	// vector of queries
	vector<Predicates> vectorOfQueries;

	vector<Relation> databaseRelations;

	vector<Relation> queriesRelations;


public:
	/*
	Interpreter(Parser parse) {
		this->parse = parse;
	};
	*/

	void setupQuery(vector<Predicates> vectorOfQueries);

	void process(vector<Relation> databaseRelations);
	Relation interpretQuery(Relation queryRelation, vector<Relation> databaseRelations);
};

// GETS ALL THE QUERIES AND PUTS THEM INTO A RELATION
void Interpreter::setupQuery(vector<Predicates> vctrQueries) {
	vectorOfQueries = vctrQueries;

	// PRINTING STUFF TO SEE
	/*cout << "Number of Queries: " << vectorOfQueries.size() << "\n";
	for (unsigned int i = 0; i < vectorOfQueries.size(); i++) {
		cout << "The Querie Relation Name (aka the name of the table): " << vectorOfQueries[i].returnQuerieRelationName() << "\n";

		cout << "The parameters of the query are: ";
		vector<string> tempParametersVctr = vectorOfQueries[i].returnQuerieParametersVector();
		for (unsigned int j = 0; j < tempParametersVctr.size(); j++) {
			cout << tempParametersVctr[j] << ", ";
		}
		cout << "\n";
	}*/

	//	THIS IS WHAT ACTUALLY BUILDS THE TABLE OF QUERIES
	for (unsigned int i = 0; i < vectorOfQueries.size(); i++) {
		Relation relation = Relation(vectorOfQueries[i].returnQuerieRelationName(), vectorOfQueries[i].returnQuerieParametersVector());
		queriesRelations.push_back(relation);
	}
}





// PROCESS - BREAKS UP THE VECTOR OF RELATIONS INTO INDIVIDUAL RELATION QUERIES TO BE PROCESSED
void Interpreter::process(vector<Relation> databaseRelations) {
	// unsigned int numberOfQueries = queriesRelations.size();

	// Just for fun to know.
	// cout << "The number of queries we will process is: " << numberOfQueries << "\n\n";

	// This will process one query at a time!
	for (unsigned int i = 0; i < vectorOfQueries.size(); i++) {
		Relation relation = interpretQuery(queriesRelations[i], databaseRelations);
		vectorOfQueries.at(i).printPredicate();
		cout << "? " << relation.toString();
	}
}



// INTERPRETS INDIVIDUAL QUERY
Relation Interpreter::interpretQuery(Relation queryRelation, vector<Relation> databaseRelations) {
	// PRINTING STUFF (can be deleted)
	// cout << "The query relation we will process is (table): " << queryRelation.returnSchemeName() << "\n";
	// cout << "The query variables and constants we need to match (the things we need to match): ";
	vector<string> querySchemesVctr = queryRelation.returnSchemes();
	// Prints each query parameter
	for (unsigned int i = 0; i < querySchemesVctr.size(); i++) {
		// cout << querySchemesVctr[i] << ", ";
	}
	// cout << "\n";


	// TEMPORARY RELATION, copy of database
	Relation copyRelation;

	// SERIOUS STUFF
	for (unsigned int i = 0; i < databaseRelations.size(); i++) {	// size of columns

		// Find a match between query table name and database name
		if (queryRelation.returnSchemeName() == databaseRelations[i].returnSchemeName()) {
			// cout << "Found a relation (table) match!\n";


			map<string, int> duplicateMap;
			copyRelation = databaseRelations[i];
			vector<int> position;
			vector<string> variable;


			// THIS MIGHT NEED A DEEPER COPY

			// Work on each query parameter (column)
			for (unsigned int j = 0; j < queryRelation.returnSchemes().size(); j++) {
				// bool isConstant;
				if ((queryRelation.returnSchemes()[j]).front() == '\'') {
					// cout << "We found a parameter in the query that is a Constant (in quotes""): " << queryRelation.returnSchemes()[j] << ".\n";
					// isConstant = true;
					
					int column = j;
					string selectConstant = queryRelation.returnSchemes()[j];
					// copyRelation = copyRelation.select(selectConstant, column);
					copyRelation = copyRelation.select(selectConstant, column, copyRelation);
				}
				else {
					// cout << "We found a parameter in the query that is a Variable (no quotes): " << queryRelation.returnSchemes()[j] << ".\n";
					// isConstant = false;

					if (duplicateMap.find(queryRelation.returnSchemes()[j]) != duplicateMap.end()) {
						// No duplicate
						int column = j;
						string selectConstant = queryRelation.returnSchemes()[j];
						// copyRelation = copyRelation.select(selectConstant, column);
						copyRelation = copyRelation.select(column, duplicateMap.find(selectConstant)->second);
					}
					else {
						string selectConstant = queryRelation.returnSchemes()[j];
						duplicateMap.insert(pair<string, int> (selectConstant, j));
						position.push_back(j);
						variable.push_back(selectConstant);
					}
				}
				
			}
			copyRelation = copyRelation.project(position);
			copyRelation = copyRelation.rename(variable);


		}
		
		
	}

	return copyRelation;

}

