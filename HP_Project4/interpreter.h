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
	vector<Rules> vectorOfRules;

public:
	void setupQuery(vector<Predicates> vectorOfQueries);
	void processQuery();
	Relation interpretQuery(Relation queryRelation, vector<Relation> databaseRelations);

	void addRules(vector<Rules> vectorOfRules);
	Relation returnMatchingRelation(string relationName);

	void addDatabase(vector<Relation> databaseRelations);
};

// GETS ALL THE QUERIES AND PUTS THEM INTO A RELATION
void Interpreter::setupQuery(vector<Predicates> vctrQueries) {
	vectorOfQueries = vctrQueries;

	//	THIS IS WHAT ACTUALLY BUILDS THE TABLE OF QUERIES
	for (unsigned int i = 0; i < vectorOfQueries.size(); i++) {
		Relation relation = Relation(vectorOfQueries[i].returnQuerieRelationName(), vectorOfQueries[i].returnQuerieParametersVector());
		queriesRelations.push_back(relation);
	}
}

// PROCESS - BREAKS UP THE VECTOR OF RELATIONS INTO INDIVIDUAL RELATION QUERIES TO BE PROCESSED
void Interpreter::processQuery() {
	// This will process one query at a time!
	for (unsigned int i = 0; i < vectorOfQueries.size(); i++) {
		Relation relation = interpretQuery(queriesRelations[i], databaseRelations);
		vectorOfQueries.at(i).printPredicate();
		cout << "? " << relation.toString();
	}
}

void Interpreter::addDatabase(vector<Relation> databaseRelationz) {
	databaseRelations = databaseRelationz;
}

// INTERPRETS INDIVIDUAL QUERY
Relation Interpreter::interpretQuery(Relation queryRelation, vector<Relation> databaseRelations) {
	vector<string> querySchemesVctr = queryRelation.returnSchemes();
	
	// TEMPORARY RELATION, copy of database
	Relation copyRelation;

	// SERIOUS STUFF
	for (unsigned int i = 0; i < databaseRelations.size(); i++) {	// size of columns

		// Find a match between query table name and database name
		if (queryRelation.returnSchemeName() == databaseRelations[i].returnSchemeName()) {
			
			map<string, int> duplicateMap;
			copyRelation = databaseRelations[i];
			vector<int> position;
			vector<string> variable;

			// Work on each query parameter (column)
			for (unsigned int j = 0; j < queryRelation.returnSchemes().size(); j++) {
				if ((queryRelation.returnSchemes()[j]).front() == '\'') {

					int column = j;
					string selectConstant = queryRelation.returnSchemes()[j];
					copyRelation = copyRelation.select(selectConstant, column, copyRelation);
				}
				else {
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



// Evaluate a Rule!
// call join or union on Relation.
void Interpreter::addRules(vector<Rules> vectorOfRules) {
	cout << "Rule Evaluation\n";

	vector<int> relationsThatChanged;
	// also keep track of the size of all the relations
	vector<int> sizeOfRelations;
	for (unsigned int i = 0; i < databaseRelations.size(); i++) {
		sizeOfRelations.push_back(databaseRelations[i].returnTuples().size());
	}
	bool sizeOfRelationsChanged = true;	// set to false if not changed, means we finished our passes
	int numPassesThroughRules = 0;

	while (sizeOfRelationsChanged)
	{
		// Go through each rule
		for (unsigned int i = 0; i < vectorOfRules.size(); i++) {

			vectorOfRules[i].printRule();
			cout << ".\n";

			// Get each Rule
			HeadPredicate ruleHeadPredicate = vectorOfRules[i].returnHeadPredicateObj()[0];	// This is the relation that we finish with (after a join or union). only care about the first in the vector
			vector<Predicates> vectorOfPredicates = vectorOfRules[i].returnVectorOfPredicates();	// These are the relations that need to be joined

			// The relation we want to finish the union with. (call join, union the resulting relation with this one in the database)
			string ruleRelationName = ruleHeadPredicate.returnHeadPredicateID();
			// columns to keep after join is completed, so we can do the union
			vector<string> columnsToKeep = ruleHeadPredicate.returnIDList();

			
			// Relations to Join, put into a vector of relations
			vector<Relation> vectorOfRelations;
			for (unsigned int k = 0; k < vectorOfPredicates.size(); k++) {
				string relationID = vectorOfPredicates[k].returnPredicateID();
				vector<string> relationColumns = vectorOfPredicates[k].returnParametersVector();

				Relation relationToJoin = returnMatchingRelation(relationID);
				Relation queryRelation(relationID, relationColumns);

				relationToJoin = interpretQuery(queryRelation, databaseRelations); // interpret as query.

				// relationToJoin.rename(relationColumns);		//	THIS CAUSED ME SO MUCH GRIEF

				vectorOfRelations.push_back(relationToJoin);
			}


			// Temporary relation to be the result of a join.
			Relation resultingRelation = vectorOfRelations[0];
			for (unsigned int i = 1; i < vectorOfRelations.size(); i++) {
				resultingRelation = resultingRelation.join(vectorOfRelations[i]);
			}


			// Figure out which columns need to be projected.
			vector<int> columnsToProject;
			for (unsigned int i = 0; i < columnsToKeep.size(); i++) {
				for (unsigned int k = 0; k < resultingRelation.returnSchemes().size(); k++) {
					if (columnsToKeep[i] == resultingRelation.returnSchemes()[k]) {
						columnsToProject.push_back(k);
					}
				}
			}
			resultingRelation = resultingRelation.project(columnsToProject);
			resultingRelation = resultingRelation.renameRelation(ruleRelationName);	// name of relation
			resultingRelation = resultingRelation.rename(columnsToKeep); // Schemes

			// insert Tuples into correct Relation.
			for (unsigned int i = 0; i < databaseRelations.size(); i++) {
				if (databaseRelations[i].returnSchemeName() == resultingRelation.returnSchemeName()) {
					// This is the Relation in the vector: relations. That we want to insert our tuples.
					databaseRelations[i] = databaseRelations[i].unionize(resultingRelation);
					relationsThatChanged.push_back(i);
				}
			}
		}


		// Increment number of passes through Rules
		numPassesThroughRules++;

		bool loopAgain = false;
		// check if relations sizes changed.
		for (unsigned int i = 0; i < databaseRelations.size(); i++) {
			int sizeOfOriginalRelation = sizeOfRelations[i];
			int newSizeOfRelation = databaseRelations[i].returnTuples().size();

			if (sizeOfOriginalRelation == newSizeOfRelation) {
				// unchanged size
			}
			else
			{
				// size changed
				loopAgain = true;
				sizeOfRelations[i] = (databaseRelations[i].returnTuples().size());
			}
		}
		// Determined if another loop through again is necessary.
		sizeOfRelationsChanged = loopAgain;
	}
	// FigureOut how many passes were necessary!
	cout << "\n" << "Schemes populated after " << numPassesThroughRules << " passes through the Rules.\n\n";
}


Relation Interpreter::returnMatchingRelation(string relationName) {
	Relation relationToReturn;

	for (unsigned int i = 0; i < databaseRelations.size(); i++) {
		if (databaseRelations[i].returnSchemeName() == relationName) {
			relationToReturn = databaseRelations[i];
		}
	}
	return relationToReturn;
}