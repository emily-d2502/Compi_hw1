#include <iostream>
#include <vector>
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
                // check_string(yytext);
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

bool is_hex(char n) {
    return ('0' <= n && n <= '9') || ('A' < n && n <= 'F') || ('a' < n && n <= 'f');
}

void print_string(const char* input) {
    std::string ret;
    for (int i = 1; i < strlen(input) - 1; ++i) {
        if (input[i] != '\\') {
            ret.push_back(input[i]);
            continue;
        }
        switch (input[++i])
        {
            case 'n':
                ret.push_back('\n');
                break;

            case 'r':
                ret.push_back('\r');
                break;

            case 't':
                ret.push_back('\t');
                break;

            case '\\':
                ret.push_back('\\');
                break;

            case '\"':
                ret.push_back('\"');
                break;

            case 'x':
                std::string hex;
                do {
                    hex.push_back(input[++i]);
                } while (is_hex(input[i + 1]));
                ret.push_back(std::stoi(hex, nullptr, 16));
                break;
        }
    }
    std::cout << ret;
}
