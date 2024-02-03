#include <iostream>
#include <vector>
#include "tokens.hpp"
#include <cstring>

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
            case ERROR:
                main_error(yytext);
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

void main_error(const char* c){
    if (*c=='\0'){
        printf("Error \n", *c);
    }
    else{
        printf("Error %c\n", *c);
        exit(0);
    }
    
}

void undefined_escape_sequence_error(const char* str){
    printf("Error undefined escape sequence %s\n", str);
    exit(0);
}

void unclosed_string_error(const char* str){
    printf("Error unclosed string %s\n", str);
    exit(0);
}

bool is_hex(const char n) {
    return ('0' <= n && n <= '9') || ('A' <= n && n <= 'F') || ('a' <= n && n <= 'f');
}

bool isCharLegal(const char c){
    return ( c==0x0D || c==0x0A || c==0x09 || (c>0x1F && c<0x7F) );
}

void check_string(const char* str) {
    int len=yyleng-2;
    bool backSlash=false;
    ++str;
    int i=0;
    while (i<len) {
        if (backSlash){
            std::string hex1("");
            std::string hexEscSeq("");
            switch (str[i]){
            case 'n':
            case 'r':
            case 't':
            case '\\':
            case '\"':
            case '0':
            backSlash=false;
                ++i;
                continue;
            case 'x':
                if (len-i<3){
                    for(int j=i;j<len;j++){
                        hexEscSeq.push_back(str[j]);
                    }
                    undefined_escape_sequence_error(hexEscSeq.c_str());
                    return;
                }
                for(int j=i+1;j<i+3;j++){
                    hex1.push_back(str[j]);
                }
                hexEscSeq="x"+hex1;
                if (is_hex(hex1[0]) && is_hex(hex1[1]) && isCharLegal(std::stoi(hex1, nullptr, 16))){
                    backSlash=false;
                    ++i;
                    continue;
                }
                else{
                    undefined_escape_sequence_error(hexEscSeq.c_str());
                    return;
                }
            default:
                std::string escSeq=std::string("")+str[i];
                undefined_escape_sequence_error(escSeq.c_str());
                return;
            }
        }
        if (str[i]=='\\'){
            backSlash=true;
            ++i;
            continue;
        }
        if(!isCharLegal(str[i])){
            main_error(&(str[i]));
            exit(0);
        }
        if (str[i] == '\n' || str[i] == '\r' ) {
            std::cout << "Error unclosed string\n";  
            exit(0);          
        }
        ++i;
    }
    if (backSlash==true){
        unclosed_string_error(str);
    }
}

void print_string(const char* input) {
    std::string ret;
    int len=yyleng-1;
    for (int i = 1; i < len; ++i) {
        if (input[i] != '\\') {
            ret.push_back(input[i]);
            continue;
        }
        ++i;
        if (i==len) break;
        switch (input[i])
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
            case '0':
                ret.push_back('\0');
                break;
            case 'x':
                std::string hex;
                for (int j=0;j<2;++j){
                    ++i;
                    if (i==len) break;
                    hex.push_back(input[i]);
                }
                ret.push_back(std::stoi(hex, nullptr, 16));
                break;
        }
    }
    std::string output=std::to_string(yylineno)+" STRING ";
    printf("%s",output.c_str());
    printf("%s",ret.c_str());
    printf("\n");
}
