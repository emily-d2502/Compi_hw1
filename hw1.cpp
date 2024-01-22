#include <iostream>
#include "tokens.hpp"

#define TOKEN_CASE(token)           \
        case token:                 \
            show_token(#token);     \
            break;

int main() {
	int token;
    while ((token = yylex()))
    {
        switch (token)
        {
            TOKEN_CASE(VOID)
            TOKEN_CASE(INT)
            TOKEN_CASE(BYTE)
            TOKEN_CASE(B)
            TOKEN_CASE(BOOL)
            TOKEN_CASE(AND)
            TOKEN_CASE(OR)
            TOKEN_CASE(NOT)
            TOKEN_CASE(TRUE)
            TOKEN_CASE(FALSE)
            TOKEN_CASE(RETURN)
            TOKEN_CASE(IF)
            TOKEN_CASE(ELSE)
            TOKEN_CASE(WHILE)
            TOKEN_CASE(BREAK)
            TOKEN_CASE(CONTINUE)
            TOKEN_CASE(SC)
            TOKEN_CASE(LPAREN)
            TOKEN_CASE(RPAREN)
            TOKEN_CASE(LBRACE)
            TOKEN_CASE(RBRACE)
            TOKEN_CASE(ASSIGN)
            TOKEN_CASE(RELOP)
            TOKEN_CASE(BINOP)
            TOKEN_CASE(COMMENT)
            TOKEN_CASE(ID)
            TOKEN_CASE(NUM)
            case STRING:
                check_string(yytext);
                print_string(yytext);
                break;
        }
    }
	return 0;
}

void show_token(const char* name) {
    if (!strcmp(name, "COMMENT")) {
        std::cout << yylineno << " " << name << " //" << "\n";
    } else {
        std::cout << yylineno << " " << name << " " << yytext << "\n";
    }
}

void check_string(const char* str) {
    while (str++) {
        // check for errors
    }
}

void print_string(const char* str) {
    // Todo
}
