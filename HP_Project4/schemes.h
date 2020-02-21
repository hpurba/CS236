#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Schemes {

	// individual object specific variables
	string schemeID;
	vector<string> idListVector;

public:
	// Creates the object
	Schemes(string schemeID, vector<string> idListVector) : schemeID(schemeID), idListVector(idListVector) {}

	// prints object
	void printScheme();
	string returnSchemeID();
	vector<string> returnIdListVector();
};

void Schemes::printScheme() {
	cout << "  " << schemeID << "(";
	for (unsigned int i = 0; i < idListVector.size(); i++)
	{
		if (i < idListVector.size() - 1) {
			cout << idListVector[i] << ",";
		}
		else {
			cout << idListVector[i];
		}
	}
	cout << ")\n";
}


string Schemes::returnSchemeID() {
	return schemeID;
}

vector<string> Schemes::returnIdListVector() {
	return idListVector;
}
