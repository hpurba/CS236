/*
Database
- creates a relational database

// Think a collection of relations
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<set>
#include<vector>
#include "parser.h"
#include "relation.h"

using namespace std;

class DataBase {
private:
	// Object specific
	// constructor
		
	vector<Schemes> schemes;
	
	// or should I make this a set?
	vector<Relation> relations;

public:
	// void setup(Parser parse);
	// { this->parse = parse; }
		
	// DataBase(Parser parse) { this->parse = parse; }
	// functions
	
	void setup(vector<Schemes> vectorOfSchemes);
	void addFacts(vector<Facts> vectorOfFacts);


	void printRelations();
	// QUERY SEARCH FUNCTIONS IN HERE!
	// void toString(); 
	// void add(Tuple);

	// Other functions for use to do queries
	// void setNameOfTables(vector<string> schemes);
	// void addTuples(vector<Tuple> tupleRows);

	vector<Relation> returnDatabaseRelations() { return relations; }
};


void DataBase::setup(vector<Schemes> vectorOfSchemes) {
	vector<Schemes> schemes = vectorOfSchemes;

	// PRINTING STUFF TO SEE
	/*cout << "SIZE OF SCHEMES: " << schemes.size() << "\n";
	for (unsigned int i = 0; i < schemes.size(); i++) {
		cout << "Scheme ID: " << schemes[i].returnSchemeID() << "\n";
	}*/
	
	for (unsigned int i = 0; i < schemes.size(); i++) {
		Relation relation = Relation(schemes[i].returnSchemeID(), schemes[i].returnIdListVector());
		relations.push_back(relation);
	}
}

void DataBase::addFacts(vector<Facts> vectorOfFacts) {
	for (unsigned int i = 0; i < vectorOfFacts.size(); i++) {
		string factID = vectorOfFacts[i].returnfactID();
		vector<string> factList = vectorOfFacts[i].returnFactList();

		for (unsigned int j = 0; j < relations.size(); j++) {
			if (relations[j].returnSchemeName() == factID) {
				relations[j].addToTuple(factList);

				// JUST TESTING STUFF / PRINTING STUFF TO SEE INSIDE.
				// cout << "Scheme Name: " << relations[j].returnSchemeName() << " And Facts: ";
				/*for (unsigned int k = 0; k < factList.size(); k++) {
					cout << factList[k] << ", ";
				}
				cout << "\n";*/


			}
		}
	}
}

// Prints all the relations
void DataBase::printRelations() {
	for (unsigned int i = 0; i < relations.size(); i++) {
		relations[i].printRelation();
	}
}
