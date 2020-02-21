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
	vector<Schemes> schemes;
	vector<Relation> relations;

public:
	void setup(vector<Schemes> vectorOfSchemes);
	void addFacts(vector<Facts> vectorOfFacts);
	void printRelations();
	vector<Relation> returnDatabaseRelations() { return relations; }
};


void DataBase::setup(vector<Schemes> vectorOfSchemes) {
	vector<Schemes> schemes = vectorOfSchemes;

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

			}
		}
	}
}


// Prints all the relations	// This may not actually be used...
void DataBase::printRelations() {
	for (unsigned int i = 0; i < relations.size(); i++) {
		relations[i].printRelation();
	}
}
