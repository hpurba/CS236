#include "token.h"
#include <iostream>
#include <fstream>
#include <string>
#include<vector>

using namespace std;

class Scanner {
	// Object specific variables
	int currentLine = 1;		// integer that holds the line count
	int actualLineCounter = 1;	// holds the actual line count
	ifstream myStream;			// input stream from the textfile.
	string currentStr;			// Holds the current characters identified as a string
	char currentChar;			// Character that we will keep
	char nextChar;				// Character that is next
	int numTokens = 0;			// will be used to hold the number of tokens

public:
	vector<Tokenizer> scan_Identify(string inFile);
	int getNumTokens();
};

vector<Tokenizer> Scanner::scan_Identify(string inFile) {
	// Stream from file
	ifstream myStream;
	myStream.open(inFile, ifstream::in);

	vector<Tokenizer> tokensVector; // Vector of Tokens
	int type;						// holds the type enum

	while (myStream.peek() != EOF) {
		currentChar = myStream.get();	// Get the first Character
		nextChar = myStream.peek();		// Peek for the next Character

		// Character is a new line.
		if (currentChar == '\n') {
			actualLineCounter++;			// Add to the line count
			currentLine = actualLineCounter;
			// currentChar = myStream.get();
		}
		else if (isspace(currentChar)) {
			// Do nothing/ignore
		}
		else if (isblank(currentChar)) {
			// Do nothing/ignore
		}

		// Character is alphabetical
		else if (isalpha(currentChar)) {
			type = ID;
			// Append the current character to the string
			currentStr.append(1, currentChar);

			if (isalpha(nextChar) | isdigit(nextChar)) {
				type = ID;
				while (isalpha(nextChar) | isdigit(nextChar)) {
					currentChar = myStream.get();
					currentStr.append(1, currentChar);
					nextChar = myStream.peek();
				}
				
				if (currentStr == "Schemes") {
					type = SCHEMES;
				}
				else if (currentStr == "Facts") {
					type = FACTS;
				}
				else if (currentStr == "Rules") {
					type = RULES;
				}
				else if (currentStr == "Queries") {
					type = QUERIES;
				}
				// It must be an UNDEFINED
				else {
					type = ID;
				}
				
			}
			// Character is a space
			else if (isspace(currentChar)) {
				// Do nothing and skip over.
			}
			// If the next character is neither a digit or a alphabetical character, make the token.
			else {
				type = ID;
			}

			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;

		}

		// Character is a colon
		else if (currentChar == ':') {
			// instance of Colon Dash
			if (nextChar == '-') {
				currentStr.append(1, currentChar);
				currentChar = myStream.get();
				currentStr.append(1, currentChar);
				type = COLON_DASH;
			}
			// Just COLON
			else {
				currentStr.append(1, currentChar);
				type = COLON;
			}

			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;

		}

		// Character is a left paren
		else if (currentChar == '(') {
			currentStr.append(1, currentChar);
			type = LEFT_PAREN;

			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
		}
		// Character is a right paren
		else if (currentChar == ')') {
			currentStr.append(1, currentChar);
			type = RIGHT_PAREN;

			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
		}
		// Character is a right Q mark '?'
		else if (currentChar == '?') {
			currentStr.append(1, currentChar);
			type = Q_MARK;

			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
		}
		// Character is a period '.'
		else if (currentChar == '.') {
			currentStr.append(1, currentChar);
			type = PERIOD;

			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
		}
		// Character is a comma ','
		else if (currentChar == ',') {
			currentStr.append(1, currentChar);
			type = COMMA;

			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
		}
		// Character is a add ','
		else if (currentChar == '+') {
			currentStr.append(1, currentChar);
			type = ADD;

			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
		}
		// Character is a multiply ','
		else if (currentChar == '*') {
			currentStr.append(1, currentChar);
			type = MULTIPLY;

			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
		}

		// Character is a line comment '#'
		else if (currentChar == '#') {
			currentStr.append(1, currentChar);
			bool commentIsOpen = true;
			
			type = COMMENT;

			// This is a block comment
			if (nextChar == '|') {
				while (commentIsOpen) {
					currentChar = myStream.get();
					currentStr.append(1, currentChar);
					nextChar = myStream.peek();

					// Decide whether to close it
					if (nextChar == '|') {
						currentChar = myStream.get();
						// if (currentChar == '\n') { actualLineCounter++;}
						currentStr.append(1, currentChar);
						nextChar = myStream.peek();

						// close block comment
						if (nextChar == '#') {
							currentChar = myStream.get();
							currentStr.append(1, currentChar);
							commentIsOpen = false;
						}
						else if (nextChar == EOF) {
							type = UNDEFINED;
							commentIsOpen = false;
						}
						// Not closing the block comment
						else {

							// Continue / reloop

						}
					}

					else if (nextChar == EOF) {
						actualLineCounter++;
						type = UNDEFINED;
						commentIsOpen = false;
					}
					// continue creating the multilinecomment
					else {
						if (nextChar == '\n') { 
							actualLineCounter++; 
						}
					}
				}
				// Generate the comment here
				Tokenizer myToken(type, currentStr, currentLine);
				tokensVector.push_back(myToken);
				currentStr = "";
				numTokens++;
				currentLine = actualLineCounter;
			}
			// After # is EOF
			else if (nextChar == EOF) {
				type = STRING;
				commentIsOpen = false;
			}
			
			// Not a block comment, sinlge line comment 
			else {
				
				bool oneLineCommentOpen = true;
				while (oneLineCommentOpen){
					type = COMMENT;
					currentLine = actualLineCounter;

					if (nextChar == '\n') {
						currentChar = myStream.get();
						actualLineCounter++;
						oneLineCommentOpen = false;
					}
					else if (nextChar == EOF) {
						actualLineCounter++;
						// currentLine = actualLineCounter;
						oneLineCommentOpen = false;
					}
					else
					{
						currentChar = myStream.get();
						currentStr.append(1, currentChar);
						nextChar = myStream.peek();
					}

				}
			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
			}
		}

		// String 
		else if (currentChar == ('\'')) {
			currentStr.append(1, currentChar);

			bool quoteOpen = true;
			currentLine = actualLineCounter;
			type = STRING;

			// Begin identifying the quote
			while (quoteOpen) {

				nextChar = myStream.peek();

				// If the next character is EOF
				if (nextChar == EOF) {
					type = UNDEFINED;
					// char newLine = '\n';
					// currentStr.append(1, newLine);
					quoteOpen = false;
				}
				// Close quote or double quote and continue
				else if (nextChar == '\'') {
					currentChar = myStream.get();
					currentStr.append(1, currentChar);
					nextChar = myStream.peek();

					// Double Quote situation
					if (currentChar == nextChar) {
						currentChar = myStream.get();
						currentStr.append(1, currentChar);
					}
					else if (nextChar == EOF) {
						type = STRING;
						quoteOpen = false;
					}
					else
					{
						type = STRING;
						quoteOpen = false;
					}
				}
				else {
					type = STRING;

					// KEEP READING
					currentChar = myStream.get();
					currentStr.append(1, currentChar);
					if (currentChar == '\n') { actualLineCounter++; }
				}
			}
			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
		}
		else {
			// Loop
			type = UNDEFINED;
            currentStr.append(1, currentChar);  // just added this.
			Tokenizer myToken(type, currentStr, currentLine);
			tokensVector.push_back(myToken);
			currentStr = "";
			numTokens++;
			currentLine = actualLineCounter;
		}
	}

	type = E_OF;
	// actualLineCounter++;
	Tokenizer myToken(type, currentStr, actualLineCounter);
	tokensVector.push_back(myToken);
	currentStr = "";
	numTokens++;
	myStream.close();
	return tokensVector;
}

int Scanner::getNumTokens() {

	return numTokens;
};
