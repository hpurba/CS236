#pragma once
/*
RELATION

// Think of a single table. This is what this class makes an object of

// name							// nameOfTable = name;
// scheme (column headers)
// tuples (each entry/row)	// this should be a set data type // set<Tuples> rows

// include tuples class
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;


// tuple
class Tuple : public vector<string> {};


class Relation {
private:
	// Object specific
	
	string name;
	vector<string> schemes;	// vector of headers
	set<Tuple> myTupleSet;

	vector<string> getSchemes() {
		return schemes;
	}

public:

	// functions
	Relation() {}
	Relation(string schName, vector<string> schemz): name(schName), schemes(schemz) {}
	// void add(set<Tuple> tuple_row);
	void addToTuple(vector<string> factList);
	string returnSchemeName();
	vector<string> returnSchemes();
	set<Tuple> returnTuples();	// Basically return the line

	void printRelation();

	// SELECT PROJECT RENAME
	Relation select(string selectConstant, int column, Relation copyRelation);
	Relation select(int column, int nextColumn);
	Relation project(vector<int> positon);	// you want all the columns for the projection.
	Relation rename(vector<string> variable);

	string toString();
};


Relation Relation::project(vector<int> positon) {

	vector<string> newSchemes;
	Relation newRelation(name, newSchemes);
	
	for (Tuple tuple : myTupleSet) {
		Tuple newTuple;
		for (size_t i = 0; i < positon.size(); i++) {
			newTuple.push_back(tuple.at(positon.at(i)));
			newRelation.getSchemes().push_back(schemes.at(positon.at(i)));	// maybe dont need
		}
		newRelation.addToTuple(newTuple);
	}
	
	return newRelation;
}



Relation Relation::rename(vector<string> variable) {
	this->schemes = variable;
	return *this;
}

string Relation::toString() {
	stringstream ss;
	if (myTupleSet.empty()) {
		ss << "No\n";
	}
	else {
		ss << "Yes(" << myTupleSet.size() << ")\n";
		for (Tuple tuple : myTupleSet) {
			for (size_t i = 0; i < tuple.size(); i++) {
				if (i == 0) {
					ss << "  ";
				}
				ss << schemes.at(i) << "=" << tuple.at(i);
				if (i == schemes.size() - 1) {
					ss << endl;
				}
				else {
					ss << ", ";
				}
			}
		}
	}

	return ss.str();

}

Relation Relation::select(string selectConstant, int column, Relation copyRelation) {

	Relation newRelation(name, schemes);

	// Go through each tuple in set
	for (auto it = myTupleSet.begin(); it != myTupleSet.end(); ++it) {
		Tuple tempVect = *it;

		// go through each tuple
		for (unsigned int i = 0; i < tempVect.size(); i++) {
			if (tempVect[column] == selectConstant) {
				// keep
				newRelation.addToTuple(tempVect);
			}
			else {
				// Does not add to set
			}
		}
	}

	return newRelation;
}


Relation Relation::select(int column, int nextColumn) {

	Relation newRelation(name, schemes);

	for (Tuple tuple : myTupleSet) {
		for (size_t i = 0; i < tuple.size(); i++) {
			if (tuple.at(column) == tuple.at(nextColumn)) {
				newRelation.addToTuple(tuple);
			}
		}
	}

	return newRelation;
}


void Relation::addToTuple(vector<string> factList) {
	Tuple tup;
	for (unsigned int i = 0; i < factList.size(); i++) {
		tup.push_back(factList[i]);
	}

	myTupleSet.insert(tup);
}

// GET VARIABLES OF RELATION
string Relation::returnSchemeName() {
	return name;
}

vector<string> Relation::returnSchemes() {
	return schemes;
}

set<Tuple> Relation::returnTuples() {
	return myTupleSet;
}

void Relation::printRelation() {
	cout << "Printing Relation:\n";
	cout << "Scheme Name: " << name << "\n";

	cout << "Schemes: ";
	for (unsigned int i = 0; i < schemes.size(); i++) {
		cout << schemes[i] << ", ";
	}
	cout << "\n";

	cout << "Tuples: ";
	for (auto it = myTupleSet.begin(); it != myTupleSet.end(); ++it) {
		vector<string> tempVect = *it;
		for (unsigned int i = 0; i < tempVect.size(); i++) {
			cout << tempVect[i] << ", ";
		}
		cout << "\n";
	}
		

}
