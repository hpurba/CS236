#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Facts {

	// individual object specific variables
	string factID;
	vector<string> stringListVector;

public:
	// Creates the object
	Facts(string factID, vector<string> stringListVector) : factID(factID), stringListVector(stringListVector) {}

	// prints object
	void printFact();
};

void Facts::printFact() {
	cout << "  " << factID << "(";
	for (unsigned int i = 0; i < stringListVector.size(); i++)
	{
		if (i < stringListVector.size() - 1) {
			cout << stringListVector[i] << ",";
		}
		else {
			cout << stringListVector[i];
		}
	}
	cout << ").\n";
}