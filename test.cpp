#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

enum TokenType {
    T_AND,              // &&
    T_ASSIGN,           // =
    T_BOOLTYPE,         // bool
    T_BREAK,            // break
    T_CHARCONSTANT,     // char_lit (character literal)
    T_COMMA,            // ,
    T_COMMENT,          // comment
    T_CONTINUE,         // continue
    T_DIV,              // /
    T_DOT,              // .
    T_ELSE,             // else
    T_EQ,               // ==
    T_EXTERN,           // extern
    T_FALSE,            // false
    T_FOR,              // for
    T_FUNC,             // func
    T_GEQ,              // >=
    T_GT,               // >
    T_ID,               // identifier
    T_IF,               // if
    T_INTCONSTANT,      // int_lit (integer literal)
    T_INTTYPE,          // int
    T_LCB,              // {
    T_LEFTSHIFT,        // <<
    T_LEQ,              // <=
    T_LPAREN,           // (
    T_LSB,              // [
    T_LT,               // <
    T_MINUS,            // -
    T_MOD,              // %
    T_MULT,             // *
    T_NEQ,              // !=
    T_NOT,              // !
    T_NULL,             // null
    T_OR,               // ||
    T_PACKAGE,          // package
    T_PLUS,             // +
    T_RCB,              // }
    T_RETURN,           // return
    T_RIGHTSHIFT,       // >>
    T_RPAREN,           // )
    T_RSB,              // ]
    T_SEMICOLON,        // ;
    T_STRINGCONSTANT,   // string_lit (string literal)
    T_STRINGTYPE,       // string
    T_TRUE,             // true
    T_VAR,              // var
    T_VOID,             // void
    T_WHILE,            // while
    T_WHITESPACE        // whitespace
};

struct Token{
    std::string value;
    TokenType type;
    Token(TokenType t, const std::string& v): type(t), value(v)
    {

    }
};

int main() {
    std::unordered_map<std::string, TokenType> keywords;
    // Keywords
    keywords["bool"] = T_BOOLTYPE;
    keywords["break"] = T_BREAK;
    keywords["continue"] = T_CONTINUE;
    keywords["else"] = T_ELSE;
    keywords["extern"] = T_EXTERN;
    keywords["false"] = T_FALSE;
    keywords["for"] = T_FOR;
    keywords["func"] = T_FUNC;
    keywords["if"] = T_IF;
    keywords["int"] = T_INTTYPE;
    keywords["null"] = T_NULL;
    keywords["package"] = T_PACKAGE;
    keywords["return"] = T_RETURN;
    keywords["string"] = T_STRINGTYPE;
    keywords["true"] = T_TRUE;
    keywords["var"] = T_VAR;
    keywords["void"] = T_VOID;
    keywords["while"] = T_WHILE;
    
    string text[7] = {"int", "main()", "{", "printf(8);", "return", "0;", "}"};
    
    for(int i = 0; i < 7; i++){
        if(keywords.find(text[i]) != keywords.end()){
            cout << text[i] << endl;
        }
    }

    return 0;
}