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
    T_Print,            // Print
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
            keywords["Print"] = T_Print;
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

        bool isWhiteSpace(char c){ return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f'); }

        bool isLetter(char c){ return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || c == '_'; }

        bool isDigit(char c){ return ('0' <= c && c <= '9'); }

        bool isPunctuation(char c){
            bool isPunc = false;
            string temp;
            temp.push_back(c);
            if(punctuation.find(temp) != punctuation.end()){
                isPunc = true;
            }
            return isPunc;
        }

        bool isOperator(char c){
            bool isOp = false;
            string temp;
            temp.push_back(c);
            if(operators.find(temp) != operators.end()){
                isOp = true;
            }
            return isOp;
        }

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
            bool isStringLiteral = false;

            if (isWhiteSpace((*text)[*position])) {
                while (isWhiteSpace((*text)[*position])) {
                    if ((*text)[*position] == '\n') {
                        line_num++;
                        last_line_pos = *position;
                    }
                    *position += 1;
                }
                start = *position;
            } else {
                start = *position;
            }

            if ((*text)[*position] == '\"') {
                isStringLiteral = true;
                start = *position;
                *position += 1;
            }

            while (*position < text->length() && (isStringLiteral || !isWhiteSpace((*text)[*position]))) {
                if (isStringLiteral && (*text)[*position] == '\"') {
                    *position += 1;
                    break;
                }
                *position += 1;
            }

            // Set line number and starting column number for the word
            *line = line_num;
            *col = start - last_line_pos;
            return (*text).substr(start, (*position - start));
        }

     std::string getType(TokenType type) {
            switch (type) {
                case T_AND: return "T_logicaland";
                case T_ASSIGN: return "=";
                case T_BOOLTYPE: return "T_BoolType";
                case T_BREAK: return "T_BREAK";
                case T_CHARCONSTANT: return "T_CHARCONSTANT";
                case T_COMMA: return "\',\'";
                case T_COMMENT: return "T_COMMENT";
                case T_CONTINUE: return "T_CONTINUE";
                case T_DIV: return "T_DIV";
                case T_DOT: return "T_DOT";
                case T_ELSE: return "T_Else";
                case T_EQ: return "T_EQ";
                case T_EXTERN: return "T_EXTERN";
                case T_FALSE: return "T_BoolConstant";
                case T_FOR: return "T_For";
                case T_FUNC: return "T_FUNC";
                case T_GEQ: return "T_GEQ";
                case T_GT: return "T_GT";
                case T_ID: return "T_IDENTIFIER";
                case T_IF: return "T_If";
                case T_INTCONSTANT: return "T_IntConstant";
                case T_INTTYPE: return "T_Int";
                case T_LCB: return "\'{\'";
                case T_LEFTSHIFT: return "T_LEFTSHIFT";
                case T_LEQ: return "T_LessEqual";
                case T_LPAREN: return "\'(\'";
                case T_LSB: return "T_LSB";
                case T_LT: return "T_LT";
                case T_MINUS: return "\'-\'";
                case T_MOD: return "T_MOD";
                case T_MULT: return "\'*\'";
                case T_NEQ: return "T_NEQ";
                case T_NOT: return "\'!\'";
                case T_NULL: return "T_NULL";
                case T_OR: return "T_OR";
                case T_PACKAGE: return "T_PACKAGE";
                case T_PLUS: return "\'+\'";
                case T_Print: return "T_Print";
                case T_RCB: return "\'}\'";
                case T_RETURN: return "T_Return";
                case T_RIGHTSHIFT: return "T_RIGHTSHIFT";
                case T_RPAREN: return "\')\'";
                case T_RSB: return "T_RSB";
                case T_SEMICOLON: return "\';\'";
                case T_STRINGCONSTANT: return "T_STRINGCONSTANT";
                case T_STRINGTYPE: return "T_String";
                case T_TRUE: return "T_BoolConstant";
                case T_VAR: return "T_VAR";
                case T_VOID: return "T_Void";
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
                    // Scan each character in the word
                    int start = 0;
                    string next_token;
                    char firstChar;

                    while (start < word.length()) {
                        firstChar = word[start];

                        if(isOperator(firstChar)){
                            // Check for operators between identifiers
                            next_token.clear();
                            if (start < word.length() && isOperator(word[start])){
                                next_token.push_back(word[start]);
                                if(start+1 < word.length() && isOperator(word[start+1])){
                                    next_token.push_back(word[start+1]);
                                    tokens.push_back(Token(operators[next_token], next_token, line, col, getColumnEnd(col, next_token)));
                                    start += 2;
                                    col += next_token.length();
                                } else {
                                    tokens.push_back(Token(operators[next_token], next_token, line, col, getColumnEnd(col, next_token)));
                                    start++;
                                    col += next_token.length();
                                }
                            }
                        } else if (isLetter(firstChar)) {
                            // Handle identifiers
                            next_token.clear();
                            while (start < word.length() && (isLetter(word[start]) || isDigit(word[start]))) {
                                next_token.push_back(word[start]);
                                start++;
                            }
                            // Check if token is a key word
                            if(keywords.find(next_token) != keywords.end()){
                                type = keywords[next_token];
                            }else{
                                type = TokenType::T_ID;
                            }
                            tokens.push_back(Token(type, next_token, line, col, getColumnEnd(col, next_token)));
                            col += next_token.length();
                            // Check for operators between identifiers
                            next_token.clear();
                            if (start < word.length() && isOperator(word[start])){
                                next_token.push_back(word[start]);
                                if(start+1 < word.length() && isOperator(word[start+1])){
                                    next_token.push_back(word[start+1]);
                                    tokens.push_back(Token(operators[next_token], next_token, line, col, getColumnEnd(col, next_token)));
                                    start += 2;
                                    col += next_token.length();
                                } else {
                                    tokens.push_back(Token(operators[next_token], next_token, line, col, getColumnEnd(col, next_token)));
                                    start++;
                                    col += next_token.length();
                                }
                            }
                        } else if (isDigit(firstChar)) {
                            // Handle numbers (including decimal numbers)
                            next_token.clear();
                            bool isDecimal = false;
                            while (start < word.length() && (isDigit(word[start]) || (word[start] == '.' && !isDecimal))) {
                                if (word[start] == '.') {
                                    isDecimal = true;
                                }
                                next_token.push_back(word[start]);
                                start++;
                            }
                            tokens.push_back(Token(TokenType::T_INTCONSTANT, next_token, line, col, getColumnEnd(col, next_token)));
                            col += next_token.length();
                            // Check for operators between digits
                            next_token.clear();
                            if (start < word.length() && isOperator(word[start])){
                                next_token.push_back(word[start]);
                                if(start+1 < word.length() && isOperator(word[start+1])){
                                    next_token.push_back(word[start+1]);
                                    tokens.push_back(Token(operators[next_token], next_token, line, col, getColumnEnd(col, next_token)));
                                    start += 2;
                                    col += next_token.length();
                                } else {
                                    tokens.push_back(Token(operators[next_token], next_token, line, col, getColumnEnd(col, next_token)));
                                    start++;
                                    col += next_token.length();
                                }
                            }
                        } else if (firstChar == '\"') {
                            // Handle string literals
                            next_token.clear();
                            next_token.push_back(word[start]);
                            start++;
                            while (start < word.length() && word[start] != '\"') {
                                next_token.push_back(word[start]);
                                start++;
                            }
                            if (start < word.length() && word[start] == '\"') {
                                next_token.push_back(word[start]);
                                start++;
                            }
                            tokens.push_back(Token(TokenType::T_STRINGCONSTANT, next_token, line, col, getColumnEnd(col, next_token)));
                            col += next_token.length() + 2; // Including the quotes
                        } else if (isPunctuation(firstChar)) {
                            // Handle punctuation
                            next_token.clear();
                            next_token.push_back(firstChar);
                            tokens.push_back(Token(punctuation[next_token], next_token, line, col, getColumnEnd(col, next_token)));
                            start++;
                            col++;
                        } else {
                            // Handle unknown tokens
                            next_token.clear();
                            next_token.push_back(firstChar);
                            tokens.push_back(Token(TokenType::Unknown, next_token, line, col, getColumnEnd(col, next_token)));
                            start++;
                            col++;
                        }
                    }
                }
            }
        }

        void printTokens(){
            for(Token t : tokens){
                if(t.type == T_INTCONSTANT || t.type == T_STRINGCONSTANT || t.type == T_TRUE || t.type == T_FALSE){
                    cout << t.value << "     line " << t.line_number << " Cols " << t.col_start << " - " << t.col_end << " is " << getType(t.type) << " (value= " << t.value << ")" << endl;
                }else{
                    cout << t.value << "     line " << t.line_number << " Cols " << t.col_start << " - " << t.col_end << " is " << getType(t.type) << endl;
                }
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
    // If reading file from terminal is not working uncomment this line
    // string file_name = "t1.decaf";
    string src_code;
    readFile(file_name, &src_code);
   
    LexicalAnalyzer lexer = LexicalAnalyzer(&src_code);
    lexer.tokenize();
    lexer.printTokens();

    return 0;
}