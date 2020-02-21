#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Rules // rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
// headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
// predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
// parameter->STRING | ID | expression

class HeadPredicate {

	// individual object specific variables
	string headPredicateID;
	vector<string> idList;

public:
	// Creates the Rules object
	HeadPredicate(string headPredicateID, vector<string> idList) : headPredicateID(headPredicateID), idList(idList) {}

	// prints object
	void printHeadPredicate();

	string returnHeadPredicateID();
	vector<string> returnIDList();
};



void HeadPredicate::printHeadPredicate() {
	cout << headPredicateID << "(";
	for (unsigned int i = 0; i < idList.size(); i++)
	{
		if (i < idList.size() - 1) {
			cout << idList[i] << ",";
		}
		else {
			cout << idList[i];
		}
	}
	cout << ")";
}


string HeadPredicate::returnHeadPredicateID() {
	return headPredicateID;
}

vector<string> HeadPredicate::returnIDList() {
	return idList;
}