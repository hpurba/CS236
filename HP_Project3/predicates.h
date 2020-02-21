#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Rules // rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
// headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
// predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
// parameter->STRING | ID | expression

class Predicates {

	// individual object specific variables
	string predicateID;
	vector<string> parametersVector;

public:
	// Creates the Rules object
	Predicates(string predicateID, vector<string> parametersVector) : predicateID(predicateID), parametersVector(parametersVector) {}

	void printPredicate();


	string returnQuerieRelationName();
	vector<string> returnQuerieParametersVector();
};


void Predicates::printPredicate() {

	cout << predicateID << "(";
	for (unsigned int i = 0; i < parametersVector.size(); i++)
	{
		if (i < parametersVector.size() - 1) {
			cout << parametersVector[i] << ",";
		}
		else {
			cout << parametersVector[i];
		}
	}
	cout << ")";


}


string Predicates::returnQuerieRelationName() {
	return predicateID;
}

vector<string> Predicates::returnQuerieParametersVector() {
	return parametersVector;
}
