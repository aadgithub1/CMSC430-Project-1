/* Aaron Webb
   Project 1 - Lexical Analysis
   March 16, 2025
   Professor Bill Dulmage*/

   /*This file contains the listing functionality that 
   coordinates line numbering, error logging, and final 
   reporting of compilation. It maintains a global 
   line counter (lineNumber), as well as counters for different 
   types of errors (lexical, syntactic, and semantic). Whenever 
   the source code advances to a new line, the function nextLine()
   displays any errors that were accumulated for the previous line, 
   increments the line counter, and prints it as a prefix. 
   As tokens are recognized (or invalid characters are found), 
   appendError(...) is called with an ErrorCategories value and 
   a message string. The relevant error counter is incremented, 
   and the message is added to a vector of error strings. At the 
   end of compilation, lastLine() prints either a “Compiled Successfully”
   message (if no errors occurred) or a summary of how many lexical, 
   syntactic, and semantic errors were encountered. This approach ensures 
   that all errors for a specific line are displayed 
   before moving on, and that an error summary including all error types 
   is produced once all lines have been processed. */


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
	
	//if no errors we compiled successfully
	if(lexErrors == 0 && synErrors == 0 && semErrors == 0){
		printf("Compiled Successfully.     \n");
	} else{
		//we have at least one error, show number of each type
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

	//depending on error type, increment that error type's count
	//an push the corresponding message to the vector/dynamic array
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
	//print all errors for this line (in the vector)
	//then clear for the next line's errors
	for(auto &err : errors){
		printf("%s\n", err.c_str());
	}

	errors.clear();
}
