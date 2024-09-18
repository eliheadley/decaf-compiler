#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
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
    T_WHITESPACE,       // whitespace
    Unknown
};

struct Token{
    std::string value;
    TokenType type;
    int line_number;
    int col_start;
    int col_end;
    Token(TokenType t, const std::string& v, int l, int c1, int c2): type(t), value(v), line_number(l), col_start(c1), col_end(c2)
    {

    }
};



class LexicalAnalyzer{
    private:

        std::unordered_map<std::string, TokenType> keywords;
        std::unordered_map<std::string, TokenType> operators;
        std::unordered_map<std::string, TokenType> punctuation;
        std::unordered_map<std::string, TokenType> literals;
        vector<Token> tokens;
        string *input;
        int position;
        int line_num;
        int last_line_pos;

        void initKeywords() {
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
        }

        void initOperators() {
            // Operators
            operators["&&"] = T_AND;
            operators["="] = T_ASSIGN;
            operators["=="] = T_EQ;
            operators[">="] = T_GEQ;
            operators[">"] = T_GT;
            operators["<="] = T_LEQ;
            operators["<"] = T_LT;
            operators["!="] = T_NEQ;
            operators["!"] = T_NOT;
            operators["||"] = T_OR;
            operators["+"] = T_PLUS;
            operators["-"] = T_MINUS;
            operators["*"] = T_MULT;
            operators["/"] = T_DIV;
            operators["%"] = T_MOD;
            operators["<<"] = T_LEFTSHIFT;
            operators[">>"] = T_RIGHTSHIFT;
        }

        void initPunctuation() {
            // Punctuation
            punctuation[","] = T_COMMA;
            punctuation["."] = T_DOT;
            punctuation[";"] = T_SEMICOLON;
            punctuation["{"] = T_LCB;
            punctuation["}"] = T_RCB;
            punctuation["("] = T_LPAREN;
            punctuation[")"] = T_RPAREN;
            punctuation["["] = T_LSB;
            punctuation["]"] = T_RSB;
        }

        bool isWhiteSpace(char c){ return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == 'f'); }

        bool isLetter(char c){ return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')); }

        bool isDigit(char c){ return ('0' <= c && c <= '9'); }

        void removeComments(string* input) {
            int position = 0;
            int end = (*input).length();

            while (position < end) {
                if ((*input)[position] == '/' && position < end - 1 && (*input)[position] == '/') {
                    // Skip single-line comment
                    (*input)[position] = ' ';
                    (*input)[position + 1] = ' ';
                    position += 2;
                    while (position < end && (*input)[position] != '\n') {
                        (*input)[position] = ' ';
                        position++;
                    }
                } else {
                    position++;
                }
            }
        }

        int getColumnEnd(int col, string token){
            if(token.length() > 1){
                return col + token.length() - 1;
            }
            return col;
        }

        string getNextWord(int* position, string* text, int* line, int* col){
            int start;

            if(isWhiteSpace((*text)[*position])){
                while(isWhiteSpace((*text)[*position])){
                    if ((*text)[*position] == '\n') {
                        line_num++; 
                        last_line_pos = *position;
                    }
                    *position += 1;
                }
                start = *position;
            }else{
                start = *position;
            }
            
            while(!isWhiteSpace((*text)[*position])){
                *position += 1;
            }
            // Set line number and starting column number for the word
            *line = line_num;
            *col = start - last_line_pos;
            return (*text).substr(start, (*position-start));
        }

     std::string getType(TokenType type) {
            switch (type) {
                case T_AND: return "T_AND";
                case T_ASSIGN: return "T_ASSIGN";
                case T_BOOLTYPE: return "T_BOOLTYPE";
                case T_BREAK: return "T_BREAK";
                case T_CHARCONSTANT: return "T_CHARCONSTANT";
                case T_COMMA: return "T_COMMA";
                case T_COMMENT: return "T_COMMENT";
                case T_CONTINUE: return "T_CONTINUE";
                case T_DIV: return "T_DIV";
                case T_DOT: return "T_DOT";
                case T_ELSE: return "T_ELSE";
                case T_EQ: return "T_EQ";
                case T_EXTERN: return "T_EXTERN";
                case T_FALSE: return "T_FALSE";
                case T_FOR: return "T_FOR";
                case T_FUNC: return "T_FUNC";
                case T_GEQ: return "T_GEQ";
                case T_GT: return "T_GT";
                case T_ID: return "T_ID";
                case T_IF: return "T_IF";
                case T_INTCONSTANT: return "T_INTCONSTANT";
                case T_INTTYPE: return "T_INTTYPE";
                case T_LCB: return "T_LCB";
                case T_LEFTSHIFT: return "T_LEFTSHIFT";
                case T_LEQ: return "T_LEQ";
                case T_LPAREN: return "T_LPAREN";
                case T_LSB: return "T_LSB";
                case T_LT: return "T_LT";
                case T_MINUS: return "T_MINUS";
                case T_MOD: return "T_MOD";
                case T_MULT: return "T_MULT";
                case T_NEQ: return "T_NEQ";
                case T_NOT: return "T_NOT";
                case T_NULL: return "T_NULL";
                case T_OR: return "T_OR";
                case T_PACKAGE: return "T_PACKAGE";
                case T_PLUS: return "T_PLUS";
                case T_RCB: return "T_RCB";
                case T_RETURN: return "T_RETURN";
                case T_RIGHTSHIFT: return "T_RIGHTSHIFT";
                case T_RPAREN: return "T_RPAREN";
                case T_RSB: return "T_RSB";
                case T_SEMICOLON: return "T_SEMICOLON";
                case T_STRINGCONSTANT: return "T_STRINGCONSTANT";
                case T_STRINGTYPE: return "T_STRINGTYPE";
                case T_TRUE: return "T_TRUE";
                case T_VAR: return "T_VAR";
                case T_VOID: return "T_VOID";
                case T_WHILE: return "T_WHILE";
                case T_WHITESPACE: return "T_WHITESPACE";
                case Unknown: return "Unknown";
                default: return "Invalid TokenType";
            }
        }

    public:

        LexicalAnalyzer(string* source){
            input = source;
            position = 0;
            line_num = 0;
            last_line_pos = 0;
            initKeywords();
            initOperators();
            initPunctuation();
        }

        void tokenize(){
            // remove all comments
            removeComments(input);
        
            int end = (*input).length();
            TokenType type = TokenType::Unknown;
        
            while (position < end){
                // grab the next word from the file
                int line, col;
                string word = getNextWord(&position, input, &line, &col);

                // compare current word with keywords and operators
                if(keywords.find(word) != keywords.end()){
                    type = keywords[word];
                    tokens.push_back(Token(type, word, line, col, getColumnEnd(col, word)));
                }else if(operators.find(word) != operators.end()){
                    type = operators[word];
                    tokens.push_back(Token(type, word, line, col, getColumnEnd(col, word)));
                // scan each character in the word
                }else{
                    int start = 0;
                    string literal;
                    for(int i = 0; i < word.length(); i++){
                        // grab current character and cast to a string
                        string curChar;
                        curChar.push_back(word[i]);
                        if(punctuation.find(curChar) != punctuation.end()){
                            if(!literal.empty()){
                                type = TokenType::T_ID;
                                tokens.push_back(Token(type, literal, line, col, getColumnEnd(col, literal)));
                                literal.clear();
                            }
                            type = punctuation[curChar];
                            tokens.push_back(Token(type, curChar, line, col+i, getColumnEnd(col+i, curChar)));
                        }else{
                            literal += curChar;
                        }
                    }
                    // check if
                    if(!literal.empty()){
                        type = TokenType::T_ID;
                        tokens.push_back(Token(type, literal, line, col, getColumnEnd(col, literal)));
                    }
                }
            }
        }

        void printTokens(){
            for(Token t : tokens){
                cout << t.value << "     line " << t.line_number << " Cols " << t.col_start << " - " << t.col_end << " is " << getType(t.type) << endl;
            }
        }
};

void readFile(string file_name, string* source_code){
    // read file passed from std	
	ifstream file(file_name);
    if (!file)
    {
        cerr << "Error opening \"" + file_name + "\"\n";
    }

    string input;
    while(getline(file, input)){
        *source_code += "\n" + input;
    }
    
    file.close();
}

// main method to run program
int main(int argc, char *argv[]){

    string file_name = argv[1];
    string src_code;
    readFile(file_name, &src_code);
   
    LexicalAnalyzer lexer = LexicalAnalyzer(&src_code);
    lexer.tokenize();
    lexer.printTokens();

    return 0;
}