%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap

whitespace		([\r\t\n ])
digit   		([0-9])
non_zero_dig    ([1-9])
letter  		([a-zA-Z])

%%
void                            return VOID;
int                             return INT;
b                               return B;
byte                            return BYTE;
bool                            return BOOL;
and                             return AND;
or                              return OR;
not                             return NOT;
true                            return TRUE;
false                           return FALSE;
return                          return RETURN;
if                              return IF;
else                            return ELSE;
while                           return WHILE;
break                           return BREAK;
continue                        return CONTINUE;

;                               return SC;
\(                              return LPAREN;
\)                              return RPAREN;
\{                              return LBRACE;
\}                              return RBRACE;
=                               return ASSIGN;
(==|!=|<|>|<=|>=)               return RELOP;
(\+|-|\/|\*)                    return BINOP;
(\/\/[^\n\r]*)                  return COMMENT;
{non_zero_dig}{digit}*|(0)	    return NUM;
{letter}({letter}|{digit})*	    return ID;
{whitespace}				    ;
(\"([^\"\\]|(\\\")|(\\[^\"]))*\")  return STRING;
.		                        return ERROR;

%%

