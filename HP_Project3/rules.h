#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "headPredicate.h"
#include "predicates.h"

using namespace std;

// Rules // rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
// headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
// predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
// parameter->STRING | ID | expression

class Rules {

	// individual object specific variables
	vector<HeadPredicate> headPredicateObj;
	vector<Predicates> vectorOfPredicates; // holds vector of Predicate


public:
	// Creates the Rules object
	Rules(vector<HeadPredicate> headPredicateObj, vector<Predicates> vectorOfPredicates) : headPredicateObj(headPredicateObj), vectorOfPredicates(vectorOfPredicates) {}

	// prints object
	void printRule();
};

void Rules::printRule() {
	headPredicateObj[0].printHeadPredicate();
	cout << " :- ";
	for (unsigned int i = 0; i < vectorOfPredicates.size(); i++) {
		if (i < vectorOfPredicates.size() - 1) {
			vectorOfPredicates[i].printPredicate();
			cout << ",";
		}
		else {
			vectorOfPredicates[i].printPredicate();
		}

	}
}

