// CMSC 430 Compiler Theory and Design
// Project 1 Skeleton
// UMGC CITE
// Summer 2023

// This file contains the bodies of the functions that produces the 
// compilation listing

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
	printf("\r");
	if(lexErrors != 0){
		printf("There is/are %d error(s).", lexErrors);
	} else if(synErrors != 0){
		printf("There is/are %d error(s).", synErrors);
	} else if(semErrors != 0){
		printf("There is/are %d error(s).", semErrors);
	} else{
		printf("Compiled Successfully.     \n");
	}

	return totalErrors;
}
    
void appendError(ErrorCategories errorCategory, string message)
{
	string messages[] = { "Lexical Error, Invalid Character ", "",
		"Semantic Error, ", "Semantic Error, Duplicate ",
		"Semantic Error, Undeclared " 
	};

	string errorToPush = messages[errorCategory] + message;

	if(errorCategory == LEXICAL){
		totalErrors++;
		lexErrors++;
		errors.push_back(message);
	} else if(errorCategory == SYNTAX){
		totalErrors++;
		synErrors++;
		errors.push_back(message);
	} else if(
		errorCategory == GENERAL_SEMANTIC ||
		errorCategory == DUPLICATE_IDENTIFIER ||
		errorCategory == UNDECLARED){
			totalErrors++;
			semErrors++;
			errors.push_back(message);
		}
}

void displayErrors()
{
	for(auto &err : errors){
		printf("%s\n", err.c_str());
	}

	errors.clear();
}
