#ifndef TOKENS_HPP_
#define TOKENS_HPP_
#include <string>

enum tokentype {
    // Token Types Enum
    VOID = 1,
    INT = 2,
    BYTE = 3,
    B = 4,
    BOOL = 5,
    AND = 6,
    OR = 7,
    NOT = 8,
    TRUE = 9,
    FALSE = 10,
    RETURN = 11,
    IF = 12,
    ELSE = 13,
    WHILE = 14,
    BREAK = 15,
    CONTINUE = 16,
    SC = 17,
    LPAREN = 18,
    RPAREN = 19,
    LBRACE = 20,
    RBRACE = 21,
    ASSIGN = 22,
    RELOP = 23,
    BINOP = 24,
    COMMENT = 25,
    ID = 26,
    NUM = 27,
    STRING = 28,
    ERROR = 29
};

// lex.yy.c predefined variables
extern int yylineno;
extern char* yytext;
extern int yyleng;
extern int yylex();

// Helper functions declarations
void show_token(const char* name);
void check_string(const char* str);
void print_string(const char* str);
void main_error(const char* str);
void undefined_escape_sequence_error(const char* str);
bool is_hex(const char n);
void unclosed_string_error(const char* str);
bool isCharLegal(const char c);

#endif /* TOKENS_HPP_ */