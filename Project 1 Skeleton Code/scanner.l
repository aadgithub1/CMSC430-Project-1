/* Aaron Webb
   Project 1 - Lexical Analysis
   March 16, 2025
   Professor Bill Dulmage*/

/* This file contains the Flex specification used 
 for lexical analysis in the compiler project. It defines 
 the rules and patterns by which the input source code 
 is scanned and transformed into tokens. It provides regular 
 expressions that 
 match different lexical elements such as whitespace, 
 comments (// or --), identifiers, and numeric constants 
 (e.g., integers, decimals, hexadecimal, and real numbers). 
 Each pattern either echoes the matched text and returns an
 associated token, or calls appendError(LEXICAL, ...) 
 if an unrecognized character is encountered. Finally,
 the main function initializes the listing mechanism with firstLine(),
 reads tokens by repeatedly calling yylex(), logs them to a file
 (lexemes.txt), and finishes by invoking lastLine() to display a 
 summary of any errors.*/

%{
#include <cstdio>
#include <string>

using namespace std;

#include "listing.h"
#include "tokens.h"

%}

%option noyywrap

ws			[ \t\r]+
comment		"//".*\n
cmnt		"--".*\n
line		[\n]
id			([A-Za-z]|[A-Za-z][A-Za-z0-9]*_{0,2}[A-Za-z0-9]+_{0,2}[A-Za-z0-9]+_{0,2}[A-Za-z0-9]+|[A-Za-z][A-Za-z0-9]*_{0,2}[A-Za-z0-9]+|[A-Za-z][A-Za-z0-9]+)
digit		[0-9]
int			{digit}+
dec			{digit}+"."{digit}+
hex			#[A-Fa-f0-9]+
real		{digit}*"."{digit}+((e|E)("+"|-)*([0-9])+)*
char		'.'
schar		["'\\b'"|"'\\t'"|"'\\n'"|"'\\r'"|"'\\f'"|]
punc		[\(\),:;]
%%

{ws}		{ ECHO; }
{comment}	{ ECHO; nextLine(); }
{cmnt}		{ ECHO; nextLine(); }
{line}		{ ECHO; nextLine(); }
"+"			{ ECHO; return(ADDOP); }
"-"			{ ECHO; return(ADDOP); }
"*"			{ ECHO; return(MULOP); }
"/"			{ ECHO; return(MULOP); }
"&"			{ ECHO; return(ANDOP); }
"<"			{ ECHO; return(RELOP); }
"=>"		{ ECHO; return(ARROW); }
"|"			{ ECHO; return(OROP); }
"!"			{ ECHO; return(NOTOP); }
"="			{ ECHO; return(RELOP); }
"<>"		{ ECHO; return(RELOP); }
">"			{ ECHO; return(RELOP); }
">="		{ ECHO; return(RELOP); }
"<="		{ ECHO; return(RELOP); }
"%"			{ ECHO; return(REMOP); }
"^"			{ ECHO; return(EXPOP); }
"~"			{ ECHO; return(NEGOP); }
begin		{ ECHO; return(BEGIN_); }
case		{ ECHO; return(CASE); }
character	{ ECHO; return(CHARACTER); }
else		{ ECHO; return(ELSE); }
elsif		{ ECHO; return(ELSIF); }
end			{ ECHO; return(END); }
endfold		{ ECHO; return(ENDFOLD); }
endif		{ ECHO; return(ENDIF); }
endswitch	{ ECHO; return(ENDSWITCH); }
fold		{ ECHO; return(FOLD); }
function	{ ECHO; return(FUNCTION); }
if			{ ECHO; return(IF); }
integer		{ ECHO; return(INTEGER); }
is			{ ECHO; return(IS); }
left		{ ECHO; return(LEFT); }
list		{ ECHO; return(LIST); }
of			{ ECHO; return(OF); }
others		{ ECHO; return(OTHERS); }
real		{ ECHO; return(REAL); }
returns		{ ECHO; return(RETURNS); }
right		{ ECHO; return(RIGHT); }
switch		{ ECHO; return(SWITCH); }
then		{ ECHO; return(THEN); }
when		{ ECHO; return(WHEN); }

{id}		{ ECHO; return(IDENTIFIER);}
{int}		{ ECHO; return(INT_LITERAL); }
{dec}		{ ECHO; return(INT_LITERAL); }
{hex}		{ ECHO; return(INT_LITERAL); }
{real}		{ ECHO; return(REAL_LITERAL); }
{char}		{ ECHO; return(CHAR_LITERAL); }
{schar}		{ ECHO; return(CHAR_LITERAL); }
{punc}		{ ECHO; return(yytext[0]); }
.			{ ECHO; appendError(LEXICAL, yytext); }
%%

int main() {
	firstLine();
	
	FILE *file = fopen("lexemes.txt", "wa"); 
	int token = yylex();
	while (token) {
		fprintf(file, "%d %s\n", token, yytext);
		token = yylex();
	}
	lastLine();
	fclose(file);
	return 0;
}