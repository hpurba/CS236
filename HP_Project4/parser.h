/*
Parser
- parses tokens to check for correct grammar
*/

#pragma once
#include "token.h"
#include "schemes.h"
#include "facts.h"
#include "rules.h"
#include "headPredicate.h"
#include "predicates.h"
#include "interpreter.h"
#include<set>
#include<vector>

using namespace std;

class Parser {
private:
	// object specific
	vector<Tokenizer> vectorOfTokens;

	int tokenNum;	// token # in vector we are looking at
	string currentToken;
	string nextToken;
	int tknVctrSize;
	set<string> domainStrings;

	vector<Schemes> vectorOfSchemes;
	vector<Facts> vectorOfFacts;
	vector<Rules> vectorOfRules;
	vector<string> idListVector;
	vector<string> vectorOfStrings;
	vector<Predicates> vectorOfPredicates;	// Queries?
	vector<HeadPredicate> vectorOfHeadPredicate;
	vector<string> vectorOfParameters;
	vector<string> vectorOfParameterZ;
	

public:
	// functions
	void toString(); // Prints everything out
	
	// Return vectors functions
	vector<Schemes> getSchemes();
	vector<Facts> getFacts();
	vector<Predicates> getQueries();
	vector<Rules> getRules();

	void parse(vector<Tokenizer> vectorOfTokens);
	void parseDatalogProgram();
	void COLON();
	void SCHEMES();
	void ID();
	void LEFT_PAREN();
	void RIGHT_PAREN();
	void COMMA();
	void FACTS();
	void RULES();
	void PERIOD();
	void STRING();
	void COLON_DASH();
	void QUERIES();
	void Q_MARK();
	void ADD();
	void MULTIPLY();

	// Terminals
	void scheme();
	void idList();
	void schemeList();
	void factList();
	void fact();
	void stringList();
	void ruleList();
	void rule();
	void headPredicate();
	void predicate();
	void predicateList();
	string parameter();	// vector<bool> constantsT_VariablesF ???
	void parameterList();
	void queryList();
	void query();
	string expression();
	void parse_operator();
};

// parse
void Parser::parse(vector<Tokenizer> vctrOfTokens) {

	// Variables
	vectorOfTokens = vctrOfTokens;
	tokenNum = 0;
	tknVctrSize = vectorOfTokens.size();

	// sets the current token and next Token
	currentToken = vectorOfTokens[tokenNum].returnTokenType();
	nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
	
	try {
		parseDatalogProgram();
		// cout << "Success!\n";

		// This is where we want to all the toString() function to print all the rest 
		// toString();	// THIS IS WHERE TO STRING IS ------------------------------------------------------------------------------------------------------------------------------
		
	}
	catch (string currentToken) {
		cout << "Failure!\n";
		cout << "  " << vectorOfTokens[tokenNum].printToken();
	}
}

// This holds the parseDatalogProgram Grammar!
void Parser::parseDatalogProgram() {
	try
	{
		// Below should be the datalog program grammar!
		SCHEMES();
		COLON();
		scheme();
		schemeList();
		FACTS();
		COLON();
		factList();
		RULES();
		COLON();
		ruleList();
		QUERIES();
		COLON();
		query();
		queryList();

	}
	catch (string currentToken)
	{
		throw currentToken;
	}
}

void Parser::toString() {
	// Print Schemes
	cout << "Schemes(" << vectorOfSchemes.size() << "):\n";
	for (unsigned int i = 0; i < vectorOfSchemes.size(); i++)
	{
		vectorOfSchemes[i].printScheme();
	}

	// Print Facts
	cout << "Facts(" << vectorOfFacts.size() << "):\n";
	for (unsigned int i = 0; i < vectorOfFacts.size(); i++)
	{
		vectorOfFacts[i].printFact();
	}

	// Print Rules
	cout << "Rules(" << vectorOfRules.size() << "):\n";
	for (unsigned int i = 0; i < vectorOfRules.size(); i++)
	{
		cout << "  ";
		vectorOfRules[i].printRule();
		cout << ".\n";
	}

	// Print Queries
	cout << "Queries(" << (vectorOfPredicates.size() - vectorOfHeadPredicate.size()) << "):\n";
	for (unsigned int i = (vectorOfHeadPredicate.size()); i < vectorOfPredicates.size(); i++)
	{
		cout << "  ";
		// Print head predicate at i
		vectorOfPredicates[i].printPredicate();
		cout << "?\n";
	}

	// Print Domain
	cout << "Domain(" << domainStrings.size() << "):";
	for (auto it = domainStrings.begin(); it != domainStrings.end(); it++) {
		cout << "\n  " << *it;
	}
}

// Return vectors (Schemes, Facts, Queries, Rules)
vector<Schemes> Parser::getSchemes(){
	return vectorOfSchemes;
}
vector<Facts> Parser::getFacts() {
	return vectorOfFacts;
}
vector<Predicates> Parser::getQueries() {
	return vectorOfPredicates;
}
vector<Rules> Parser::getRules() {
	return vectorOfRules;
}


// Checks if Token is SCHEMES
void Parser::SCHEMES() {
	try {
		// Token is SCHEMES
		if (currentToken == "SCHEMES") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		// Token is not SCHEMES
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is COLON
void Parser::COLON() {
	try {
		if (currentToken == "COLON") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is ID
void Parser::ID() {
	try {
		if (currentToken == "ID") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is LEFT_PAREN
void Parser::LEFT_PAREN() {
	try {
		if (currentToken == "LEFT_PAREN") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is LEFT_PAREN
void Parser::RIGHT_PAREN() {
	try {
		if (currentToken == "RIGHT_PAREN") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			// cout << "Unsuccessful. grammer fails\n";
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is COMMA
void Parser::COMMA() {
	try {
		if (currentToken == "COMMA") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is FACTS
void Parser::FACTS() {
	try {
		if (currentToken == "FACTS") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is RULES
void Parser::RULES() {
	try {
		if (currentToken == "RULES") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is PERIOD
void Parser::PERIOD() {
	try {
		if (currentToken == "PERIOD") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is STRING
void Parser::STRING() {
	try {
		if (currentToken == "STRING") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is COLON_DASH
void Parser::COLON_DASH() {
	try {
		if (currentToken == "COLON_DASH") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is QUERIES
void Parser::QUERIES() {
	try {
		if (currentToken == "QUERIES") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is Q_MARK
void Parser::Q_MARK() {
	try {
		if (currentToken == "Q_MARK") {
			currentToken = nextToken;
			tokenNum++;
			// EOF
			if (currentToken == "EOF") {
				// finish here
			}
			else {
				nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
			}
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is ADD
void Parser::ADD() {
	try {
		if (currentToken == "ADD") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// Checks if Token is ADD
void Parser::MULTIPLY() {
	try {
		if (currentToken == "MULTIPLY") {
			currentToken = nextToken;
			tokenNum++;
			nextToken = vectorOfTokens[(tokenNum + 1)].returnTokenType();
		}
		else {
			throw currentToken;
		}
	}
	catch (string currentToken) {
		throw currentToken;
	}
}

// ------------------------------------------------------------------------------RECURSIVE ONES-------------------------------------------

// Checks if Token is scheme
// scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::scheme() {
	try {
		// Grammar for scheme
		ID();

		// First ID is special
		string firstID = vectorOfTokens[tokenNum - 1].returnDetectedString();

		LEFT_PAREN();
		ID();
		// Add ID to vector of IDs
		string idString = vectorOfTokens[tokenNum - 1].returnDetectedString();
		idListVector.push_back(idString);

		idList();
		RIGHT_PAREN();

		Schemes Schemes(firstID, idListVector);
		vectorOfSchemes.push_back(Schemes);
		idListVector.clear();	// clears the idList
	}
	catch (string currentToken) {
		throw currentToken;
	}
}


// Checks if Token is idList
// idList  	-> 	COMMA ID idList | lambda
void Parser::idList() {

	if (currentToken == "COMMA") {
		try {

			COMMA();
			ID();

			// push_back ID to vector idListVector
			string idString = vectorOfTokens[tokenNum - 1].returnDetectedString();
			idListVector.push_back(idString);

			// Recursion
			idList();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is schemeList
// schemeList	->	scheme schemeList | lambda
void Parser::schemeList() {

	// ID is the first thing
	if (currentToken == "ID") {
		try {
			// Grammar
			scheme();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	if (currentToken == "FACTS")
	{
		// continue on, skips the recursion
	}
	else {
		schemeList();
		// ELSE CASE, do nothing
	}
}


// Checks if Token is factList
// factList	->	fact factList | lambda
void Parser::factList() {
	// ID is the first thing (inside fact();)
	if (currentToken == "ID") {
		try {
			// Grammar
			fact();
			factList();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is fact
// fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void Parser::fact() {
	// ID is the first thing (inside fact();)
	if (currentToken == "ID") {
		try {
			// Grammar
			ID();
			// First ID is special
			string firstID = vectorOfTokens[tokenNum - 1].returnDetectedString();

			LEFT_PAREN();
			STRING();

			// Add STRING to vector of STRINGs
			string stringString = vectorOfTokens[tokenNum - 1].returnDetectedString();
			vectorOfStrings.push_back(stringString);
			domainStrings.insert(stringString);

			stringList();
			RIGHT_PAREN();
			PERIOD();

			// Build a scheme object. and add it to a vector--------------------------------------------------------------------------------------
			Facts Facts(firstID, vectorOfStrings);
			vectorOfFacts.push_back(Facts);
			vectorOfStrings.clear();	// clears the vectorOfStrings
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is stringList
// stringList->COMMA STRING stringList | lambda
void Parser::stringList() {
	// ID is the first thing (inside fact();)
	if (currentToken == "COMMA") {
		try {

			// Grammar
			COMMA();
			STRING();

			// push_back STRING to vector vectorOfStrings
			string stringString = vectorOfTokens[tokenNum - 1].returnDetectedString();
			vectorOfStrings.push_back(stringString);
			domainStrings.insert(stringString);

			stringList();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is ruleList
// ruleList	->	rule ruleList | lambda
void Parser::ruleList() {
	// ID is the first thing (inside headPredicate();)
	if (currentToken == "ID") {
		try {
			// Grammar
			rule();
			ruleList();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is rule
// rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
void Parser::rule() {
	// ID is the first thing (inside headPredicate();)
	if (currentToken == "ID") {
		try {
			// Grammar
			headPredicate();
			COLON_DASH();
			predicate();
			predicateList();
			PERIOD();

			Rules Rule(vectorOfHeadPredicate, vectorOfPredicates);
			vectorOfRules.push_back(Rule);
			// put it to the rules object
			vectorOfHeadPredicate.clear();
			// May not need to do this
			vectorOfPredicates.clear();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is headPredicate
// headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::headPredicate() {
	// ID is the first thing (inside headPredicate();)
	if (currentToken == "ID") {
		try {
			// Make sure idList vector is empty
			idListVector.clear();

			// Grammar
			ID();
			string headPredicateID = vectorOfTokens[tokenNum - 1].returnDetectedString();

			LEFT_PAREN();
			ID();
			string firstID = vectorOfTokens[tokenNum - 1].returnDetectedString();
			idListVector.push_back(firstID);

			idList();
			RIGHT_PAREN();

			HeadPredicate HeadPredicate(headPredicateID, idListVector);
			vectorOfHeadPredicate.push_back(HeadPredicate);
			idListVector.clear();

		}
		catch (string currentToken) {
			throw currentToken;
		}

	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is predicate
// predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
void Parser::predicate() {

	// ID is the first thing (inside predicate();)
	if (currentToken == "ID") {
		try {
			vectorOfParameters.clear();
			
			// bool isConstant;
			// vector<bool> constantsT_VariablesF;

			// Grammar
			ID();
			string predicateId = vectorOfTokens[tokenNum - 1].returnDetectedString();

			LEFT_PAREN();
			string stringParameter = parameter();	// &constantsT_VariablesF	???
			vectorOfParameters.push_back(stringParameter);

			parameterList();
			RIGHT_PAREN();

			Predicates Predicate(predicateId, vectorOfParameters);
			vectorOfPredicates.push_back(Predicate);

			// May not need to do this
			vectorOfParameterZ.clear();

		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is predicateList
// predicateList	->	COMMA predicate predicateList | lambda
void Parser::predicateList() {
	// COMMA is the first thing (inside predicateList();)
	if (currentToken == "COMMA") {
		try {

			// Grammar
			COMMA();
			predicate();
			predicateList();

		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}

}


// Checks if Token is parameter
// parameter	->	STRING | ID | expression
string Parser::parameter() {
	// STRING is the first thing (inside parameter();)
	if (currentToken == "STRING") {
		try {
			// Grammar
			STRING();
			string stringParameter = vectorOfTokens[tokenNum - 1].returnDetectedString();
			
			// bool isConstant = false;	// ***************************************************************************************************************** STRING, not CONSTANT!!!!
			// constantsT_VariablesF.push_back(isConstant);

			return stringParameter;
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	// ID is the first thing (inside parameter();)
	else if (currentToken == "ID") {
		try {
			// Grammar
			ID();

			// IS A CONSTANAT
			// bool isConstant = true;
			
			string idParameter = vectorOfTokens[tokenNum - 1].returnDetectedString();
			return idParameter;
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	// expression is the first thing (inside parameter();)
	else if (currentToken == "LEFT_PAREN") {
		try {
			// Grammar
			string stringExpression = expression();
			return stringExpression;
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		throw currentToken;
	}
	return "";
}


// Checks if Token is parameterList
// parameterList	-> 	COMMA parameter parameterList | lambda
void Parser::parameterList() {
	// COMMA is the first thing (inside parameterList();)
	if (currentToken == "COMMA") {
		try {
			// Grammar
			COMMA();
			vectorOfParameters.push_back(parameter());
			// recursion
			parameterList();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is queryList
// queryList	->	query queryList | lambda
void Parser::queryList() {
	// ID is the first thing (inside predicate();)
	if (currentToken == "ID") {
		try {
			// Grammar
			query();
			// recursion
			queryList();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	if (currentToken == "ID" || currentToken == "EOF") {
		// Continue, next token is valid
	}
	else {
		throw currentToken;
	}
}


// Checks if Token is query
// query	        ->      predicate Q_MARK
void Parser::query() {
	// ID is the first thing (inside predicate();)
	if (currentToken == "ID") {
		try {
			// Grammar
			predicate();
			Q_MARK();

		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		// ELSE CASE, do nothing
	}
}


// Checks if Token is expression
// expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
string Parser::expression() {
	// ID is the first thing (inside predicate();)
	if (currentToken == "LEFT_PAREN") {
		try {
			// Grammar
			LEFT_PAREN();

			string leftParen = vectorOfTokens[tokenNum - 1].returnDetectedString();
			string expressionStringParameter = leftParen;

			expressionStringParameter = expressionStringParameter + parameter();
			parse_operator();

			string operatorParameter = vectorOfTokens[tokenNum - 1].returnDetectedString();
			expressionStringParameter = expressionStringParameter + operatorParameter;

			expressionStringParameter = expressionStringParameter + parameter();
			RIGHT_PAREN();

			string rightParen = vectorOfTokens[tokenNum - 1].returnDetectedString();
			expressionStringParameter = expressionStringParameter + rightParen;
			return expressionStringParameter;
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		throw currentToken;
	}
	return "";
}


// Checks if Token is parse_operator
// operator	->	ADD | MULTIPLY
void Parser::parse_operator() {
	if (currentToken == "ADD") {
		try {
			ADD();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else if (currentToken == "MULTIPLY") {
		try {
			MULTIPLY();
		}
		catch (string currentToken) {
			throw currentToken;
		}
	}
	else {
		throw currentToken;
	}
}

