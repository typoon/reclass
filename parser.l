%{
#include <stdio.h>
#include "parser.tab.h"

#define YY_NO_INPUT

int new_instruction = 0;

%}

%option nounput
%option noyywrap

%%


[\t]                           ;
[\n]                           { new_instruction = 1; }
[1-9]+[0-9]*                   { yylval.int_val = atoi(yytext);    return INT; }
["]([^\\"]+|\\.)*["]           { yylval.str_val = strdup(yytext);  return STRING; }

[\.]int                        { return VAR_INT; }
[\.]double                     { return VAR_DOUBLE; }
[\.]string                     { return VAR_STRING; }

[\.]method                     { return METHOD_START; }
[\.]method_end                 { return METHOD_END; }
[\(][\)]                       { yylval.param = strdup(yytext);       return PARAMS; }

getstatic                      { return GETSTATIC; }

[a-zA-Z]+                      { yylval.identifier = strdup(yytext);  return IDENTIFIER; }

.                              ; 

%%
