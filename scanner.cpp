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
    Token(TokenType t, const std::string& v): type(t), value(v)
    {

    }
};



class LexicalAnalyzer{
    private:

        std::unordered_map<std::string, TokenType> keywords;
        std::unordered_map<std::string, TokenType> operators;
        std::unordered_map<std::string, TokenType> punctuation;
        std::unordered_map<std::string, TokenType> literals;

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

        string removeComments(string input) {
            ostringstream output;
            int position = 0;
            int end = input.length();

            while (position < end) {
                if (input[position] == '/' && position < end - 1 && input[position + 1] == '/') {
                    // Skip single-line comment
                    position += 2;
                    while (position < end && input[position] != '\n') {
                        position++;
                    }
                } else {
                    output << input[position];
                    position++;
                }
            }
            return output.str();
        }

        string getNextWord(int* position, string text){
            int start;

            if(isWhiteSpace(text[*position])){
                while(isWhiteSpace(text[*position])){
                    *position += 1;
                }
                start = *position;
            }else{
                start = *position;
            }
            
            while(!isWhiteSpace(text[*position])){
                *position += 1;
            }
            
            return text.substr(start, (*position-start));
        }

    public:
        string input;
        int position;

        LexicalAnalyzer(string source){
            input = source;
            position = 0;
            initKeywords();
            initOperators();
            initPunctuation();
        }

        vector<Token> tokenize(){
            vector<Token> tokens;
            // remove all comments
            string scanned_text = removeComments(input);
        
            int end = scanned_text.length();
            TokenType type = TokenType::Unknown;

            while (position < end){
                // grab the next word from the file
                string word = getNextWord(&position, scanned_text);

                // compare current word with keywords and operators
                if(keywords.find(word) != keywords.end()){
                    type = keywords[word];
                    tokens.push_back(Token(type, word));
                }else if(operators.find(word) != operators.end()){
                    type = operators[word];
                    tokens.push_back(Token(type, word));
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
                                tokens.push_back(Token(type, literal));
                                literal.clear();
                            }
                            type = punctuation[curChar];
                            tokens.push_back(Token(type, curChar));
                        }else{
                            literal += curChar;
                        }
                    }
                    // check if
                    if(!literal.empty()){
                        type = TokenType::T_ID;
                        tokens.push_back(Token(type, literal));
                    }
                }

            }
            return tokens;
        }
};

string readFile(string file_name){
    // read file passed from std	
	ifstream file(file_name);
    if (!file)
    {
        cerr << "Error opening \"" + file_name + "\"\n";
        return "";
    }

    string input;
    string source_code;
    while(getline(file, input)){
        source_code += "\n" + input;
    }
    
    file.close();
    return source_code;
}

// main method to run program
int main(int argc, char *argv[]){

    string file_name = argv[1];
    
    string src_code = readFile(file_name);
    // string src_code = "int main() { printf(\"hello\") return 0; }";

    LexicalAnalyzer lexer = LexicalAnalyzer(src_code);
    vector<Token> tokens = lexer.tokenize();

    for(Token t : tokens){
        cout << t.type << " and Lexeme: " << t.value << endl;
    }

    return 0;
}