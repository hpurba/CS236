/*
Token
- Creates tokens
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
enum Token_Type { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, E_OF };

class Tokenizer {
	int currentTokenType;
	string detectedString; 
	int lineNumber;
	string tokenEnumString;
public:
	Tokenizer(int tknType, string detcStr, int lnNum) :currentTokenType(tknType), detectedString(detcStr), lineNumber(lnNum) {}
	string printToken();
	string tknEnumToString(int currentTknType);
	string returnTokenType();
	string returnDetectedString();
};

string Tokenizer::tknEnumToString(int currentTokenType) {
	switch (currentTokenType) {
		case COMMA: return "COMMA";
			break;
		case PERIOD: return "PERIOD";
			break;
		case Q_MARK: return "Q_MARK";
			break;
		case LEFT_PAREN: return "LEFT_PAREN";
			break;
		case RIGHT_PAREN: return "RIGHT_PAREN";
			break;
		case COLON: return "COLON";
			break;
		case COLON_DASH: return "COLON_DASH";
			break;
		case MULTIPLY: return "MULTIPLY";
			break;
		case ADD: return "ADD";
			break;
		case SCHEMES: return "SCHEMES";
			break;
		case FACTS: return "FACTS";
			break;
		case RULES: return "RULES";
			break;
		case QUERIES: return "QUERIES";
			break;
		case ID: return "ID";
			break;
		case STRING: return "STRING";
			break;
		case COMMENT: return "COMMENT";
			break;
		case UNDEFINED: return "UNDEFINED";
			break;
		case E_OF: return "EOF";
			break;
	}
	return "ERROR"; // a string MUST be returned by the end
}

string Tokenizer::printToken() {
	string tokenEnumString = tknEnumToString(currentTokenType);
	string returnTokenString;
	returnTokenString = "(" + tokenEnumString + "," + "\"" + detectedString + "\"," + to_string(lineNumber) + ")"; // removed the \n from the original code
	return returnTokenString;
}

string Tokenizer::returnTokenType() {
	string tokenEnumString = tknEnumToString(currentTokenType);
	return tokenEnumString;
}

// added for project 2
string Tokenizer::returnDetectedString() {
	string tokenString = detectedString;
	return tokenString;
}
