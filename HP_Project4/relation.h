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

class Tuble : public vector<int> {};

class Relation {
private:
	// Object specific
	
	string name;
	vector<string> schemes;	// vector of headers
	set<Tuple> myTupleSet;

	vector<string> getSchemes() {
		return schemes;
	}


	bool isJoinable(Tuple thisTuple, Tuple otherTuple, set<Tuble> matchingColumns) {
		bool ret = true;
		for (Tuble tuble : matchingColumns) {
			if (thisTuple.at(tuble.at(0)) != otherTuple.at(tuble.at(1))) {
				ret = false;
			}
		}
		return ret;
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
	void printRelationContentsOnly();


	// SELECT PROJECT RENAME
	Relation select(string selectConstant, int column, Relation copyRelation);
	Relation select(int column, int nextColumn);
	Relation project(vector<int> positon);	// you want all the columns for the projection.
	Relation rename(vector<string> variable);
	Relation renameRelation(string newRelationName);

	// JOIN
	Relation join(Relation relationToJoin);

	// Unionize
	Relation unionize(Relation resultingRelation);

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

Relation Relation::renameRelation(string newRelationName) {
	this->name = newRelationName;
	return *this;
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


Relation Relation::join(Relation relationToJoin) {
	
	// Tuples to keep from the join.
	set<Tuple> tupleSetToKeep;

	/*cout << "Join is called!\n";*/

	// This containts the relationToJoin (schemes) and (tuples)
	vector<string> vectorOfSchemesToJoin = relationToJoin.getSchemes();
	set<Tuple> joiningTupleSet = relationToJoin.returnTuples();

	// Keeps track of which columns match.
	set<Tuble> matchingColumns;	// (resultingRelation/schemes (j), relationToJoin (i))



	// If there are not matching schemes. Just join it all.
	bool noMatchingSchemes = true;



	// Find matching columns between resultRelation and relationToJoin
	for (unsigned int i = 0; i < vectorOfSchemesToJoin.size(); i++) {
		bool matchNotFound = true;

		for (unsigned int j = 0; j < schemes.size(); j++) {
			// If a match is found
			if (schemes[j] == vectorOfSchemesToJoin[i]) {

				// Matched relation. THIS CAN BE DELETED
				noMatchingSchemes = false;
				/*cout << "Matched Relation! (resultingRelation, relationToJoin) :" << schemes[j] << " & " << vectorOfSchemesToJoin[i] << "\n";*/
				
				// Add the matching column indexes (resultingRelation/schemes (j), relationToJoin (i))
				Tuble tempTuble;
				tempTuble.push_back(j);
				tempTuble.push_back(i);
				matchingColumns.insert(tempTuble);
				tempTuble.clear();
				matchNotFound = false;
			}
		}
		// add unique schemes to resultingRelation (schemes)
		if (matchNotFound) {
			schemes.push_back(vectorOfSchemesToJoin[i]);
		}
	}


	// If there are no matching schemes, we need to put all the tuples together.
	if (noMatchingSchemes) {
		// put all the tuples together.

		for (Tuple tuple1 : myTupleSet) {
			for (Tuple tuple2 : joiningTupleSet) {
				
				// We need to combine the tuples here.
				Tuple newRow;

				// add the entire row for the original Relation 'myTupleSet'
				for (unsigned int i = 0; i < tuple1.size(); i++) {
					newRow.push_back(tuple1[i]);
				}

				// Add all the columns of the second relation, that are not a matching column.
				for (unsigned int i = 0; i < tuple2.size(); i++) {
					newRow.push_back(tuple2[i]);
				}

				// add the row into a set of tuples to keep
				tupleSetToKeep.insert(newRow);
			}
		}
	}


	// combine tuples that match.
	for (Tuple tuple1 : myTupleSet) {
		for (Tuple tuple2 : joiningTupleSet) {
			bool allColumnsMatch = false;
			
			
			if (matchingColumns.empty()) {
				// set is empty.
			}
			else {


				if (isJoinable(tuple1, tuple2, matchingColumns)) {
					allColumnsMatch = true;
				}
				else {
					allColumnsMatch = false;
				}


				//for (Tuble tuble : matchingColumns) {


				//	if (isJoinable(tuple1, tuple2, matchingColumns))

				//	if (tuple1.at(tuble.at(0)) == tuple2.at(tuble.at(1))) {

				//		// cout << tuple1.at(tuble.at(0)) << '\n';						
				//		// cout << tuple2.at(tuble.at(1)) << '\n';


				//		allColumnsMatch = true;
				//	}
				//	else {
				//		allColumnsMatch = false;
				//	}

				//}
				// add tuple1 and tuple2 together for appropriate columns
				if (allColumnsMatch) {
					// cout << "matching columns, adding possible.\n";
					// We need to combine the tuples here.
					Tuple newRow;

					// add the entire row for the original Relation 'myTupleSet'
					for (unsigned int i = 0; i < tuple1.size(); i++) {
						newRow.push_back(tuple1[i]);

					}

					// Add all the columns of the second relation, that are not a matching column.
					for (unsigned int i = 0; i < tuple2.size(); i++) {
						bool columnUnique = true;
						for (Tuble tuble : matchingColumns) {
							unsigned int tubleAtValue = tuble[1];
							if (tubleAtValue == i) {
								columnUnique = false;
							}
						}

						// if it is not one of the matching columns, dont add it.
						if (columnUnique) {
							newRow.push_back(tuple2[i]);
						}
					}

					// add the row into a set of tuples to keep
					tupleSetToKeep.insert(newRow);

					// CAN BE DELETED
					/*cout << "Inserting new row!: ";
					for (unsigned int i = 0; i < newRow.size(); i++) {
						cout << newRow[i] << ", ";
					}
					cout << ".\n";*/

				}
			}


			
		}
	}
	// cout << "\n\n";

	// Copy the tuples over (rows)
	// cout << "Modify result relation by inserting all the tuples as appropriate.\n\n";
	myTupleSet = tupleSetToKeep;

	// INSTRUCTIONS
	// Iterate through: myTupleSet
		// Iterate through: joiningTupleSet
			// Go through set of Tuble for matches.
			// If matches all columns, add it: tupleSetToKeep
			// If not, do nothing

	return *this;
}

// INSERTION OF DUPLICATE DETECTION MAY NOT BE WORKING!!!!
Relation Relation::unionize(Relation resultingRelation) {

	for (unsigned int i = 0; i < resultingRelation.returnSchemes().size(); i++) {
		set<Tuple> tuplesToAdd = resultingRelation.returnTuples();

		for (Tuple tuple : tuplesToAdd) {
			if (myTupleSet.insert(tuple).second == true) {
				// cout << "Insertion without duplicate.\n";

				for (unsigned int i = 0; i < schemes.size(); i++) {
					if (i == 0) {
						cout << "  ";
					}

					if (i < (schemes.size() - 1)) {
						cout << schemes[i] << "=" << tuple[i] << ", ";
					}
					else {
						cout << schemes[i] << "=" << tuple[i] << "\n";
					}
				}


			}
			else {
				// cout << "Duplicate insertion attempted.\n";
			}
		}
	}
	return *this;
}


void Relation::printRelationContentsOnly() {

	for (Tuple tuple : myTupleSet) {
		cout << "  ";
		for (unsigned int i = 0; i < schemes.size(); i++) {
			if (i < (schemes.size() - 1)) {
				cout << schemes[i] << "=" << tuple[i] << ", ";
			}
			else {
				cout << schemes[i] << "=" << tuple[i] << "\n";
			}
		}
	}
}

