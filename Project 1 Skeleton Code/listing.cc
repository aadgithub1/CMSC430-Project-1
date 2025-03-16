//Aaron Webb 
//CMSC 430 Compiler Theory and Design
// CMSC430 Project 1


#include <cstdio>
#include <string>
#include <vector>

using namespace std;

#include "listing.h"

static int lineNumber;
static vector<string> errors;

static int totalErrors = 0;
static int lexErrors = 0;
static int synErrors = 0;
static int semErrors = 0;

static void displayErrors();

void firstLine()
{
	lineNumber = 1;
	printf("\n%4d  ",lineNumber);
}

void nextLine()
{
	displayErrors();
	lineNumber++;
	printf("%4d  ",lineNumber);
}

int lastLine()
{
	printf("\n\n");
	
	//track each error type
	if(lexErrors == 0 && synErrors == 0 && semErrors == 0){
		printf("Compiled Successfully.     \n");
	} else{
		printf(
			"Lexical Errors: %d\n"
			"Syntactic Errors: %d\n"
			"Semantic Errors: %d\n", lexErrors, synErrors, semErrors
		);
	}

	return totalErrors;
}
    
void appendError(ErrorCategories errorCategory, string message)
{
	string messages[] = { "Lexical Error, Invalid Character ", "",
		"Semantic Error, ", "Semantic Error, Duplicate ",
		"Semantic Error, Undeclared " 
	};


	if(errorCategory == LEXICAL){
		totalErrors++;
		lexErrors++;
		errors.push_back(messages[errorCategory] + message);
	} else if(errorCategory == SYNTAX){
		totalErrors++;
		synErrors++;
		errors.push_back(messages[errorCategory] + message);
	} else if(
		errorCategory == GENERAL_SEMANTIC ||
		errorCategory == DUPLICATE_IDENTIFIER ||
		errorCategory == UNDECLARED){
			totalErrors++;
			semErrors++;
			errors.push_back(messages[errorCategory] + message);
		}
}

void displayErrors()
{
	for(auto &err : errors){
		printf("%s\n", err.c_str());
	}

	errors.clear();
}
