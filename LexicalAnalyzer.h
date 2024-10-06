#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <string>
#include <unordered_map>
#include <vector>

enum TokenType {
    T_AND,
    T_ASSIGN,
    T_BOOLTYPE,
    T_BREAK,
    T_CHARCONSTANT,
    T_COMMA,
    T_COMMENT,
    T_CONTINUE,
    T_DIV,
    T_DOT,
    T_ELSE,
    T_EQ,
    T_EXTERN,
    T_FALSE,
    T_FOR,
    T_FUNC,
    T_GEQ,
    T_GT,
    T_ID,
    T_IF,
    T_INTCONSTANT,
    T_INTTYPE,
    T_LCB,
    T_LEFTSHIFT,
    T_LEQ,
    T_LPAREN,
    T_LSB,
    T_LT,
    T_MINUS,
    T_MOD,
    T_MULT,
    T_NEQ,
    T_NOT,
    T_NULL,
    T_OR,
    T_PACKAGE,
    T_PLUS,
    T_RCB,
    T_RETURN,
    T_RIGHTSHIFT,
    T_RPAREN,
    T_RSB,
    T_SEMICOLON,
    T_STRINGCONSTANT,
    T_STRINGTYPE,
    T_TRUE,
    T_VAR,
    T_VOID,
    T_WHILE,
    T_WHITESPACE,
    Unknown
};

class LexicalAnalyzer {
private:
    int line_num;
    int last_line_pos;
    std::unordered_map<std::string, TokenType> keywords;
    std::unordered_map<std::string, TokenType> operators;
    std::unordered_map<std::string, TokenType> punctuation;

    void initKeywords();
    void initOperators();
    void initPunctuation();
    bool isWhiteSpace(char c);
    bool isLetter(char c);
    bool isDigit(char c);
    bool isPunctuation(char c);
    bool isOperator(char c);
    void removeComments(std::string* input);
    int getColumnEnd(int col, std::string token);
    std::string getNextWord(int* position, std::string* text, int* line, int* col);
    std::string getType(TokenType type);

public:
    LexicalAnalyzer(std::string* source);
    void tokenize();
    void printTokens();
};

#endif // LEXICAL_ANALYZER_H