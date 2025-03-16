/* Aaron Webb
   Project 1 - Lexical Analysis
   March 16, 2025
   Professor Bill Dulmage*/

// This file contains the function prototypes for functions that produce
// the compilation listing

enum ErrorCategories {LEXICAL, SYNTAX, GENERAL_SEMANTIC, DUPLICATE_IDENTIFIER,
	UNDECLARED};

void firstLine();
void nextLine();
int lastLine();
void appendError(ErrorCategories errorCategory, string message);

