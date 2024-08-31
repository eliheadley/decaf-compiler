#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cctype>
#include <regex>

using namespace std;

enum TokenType{
    Identifier,
    Keyword,
    Operator,
    Literal
};

struct Token{
    string value;
    TokenType type;
};

class LexicalAnalyzer{
    private:
        unordered_map<string, TokenType> keywords;

        void initKeywords(){
            keywords["bool"] = TokenType::Keyword;
            keywords["break"] = TokenType::Keyword;
            keywords["continue"] = TokenType::Keyword;
            keywords["else"] = TokenType::Keyword;
            keywords["extern"] = TokenType::Keyword;
            keywords["false"] = TokenType::Keyword;
            keywords["for"] = TokenType::Keyword;
            keywords["func"] = TokenType::Keyword;
            keywords["if"] = TokenType::Keyword;
            keywords["int"] = TokenType::Keyword;
            keywords["null"] = TokenType::Keyword;
            keywords["package"] = TokenType::Keyword;
            keywords["return"] = TokenType::Keyword;
            keywords["string"] = TokenType::Keyword;
            keywords["true"] = TokenType::Keyword;
            keywords["var"] = TokenType::Keyword;
            keywords["void"] = TokenType::Keyword;
            keywords["while"] = TokenType::Keyword;
        }

        bool isWhiteSpace(char c){
            if(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == 'f') return true;
            return false;
        }

        bool isLetter(char c){
            if(('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) return true;
            return false;
        }

        bool isDigit(char c){
            if('0' <= c && c <= '9') return true;
            return false;
        }

    public:
        LexicalAnalyzer(const string& soruce){
            string input = soruce;
            int position = 0;
            initKeywords();
        }

        vector<Token> tokenize(){
            // remove all comments

        }


};

int main(int argc, char *argv[]) {

    string filename = argv[1];
    // read file passed from std	
	ifstream file(filename);
    if (!file)
    {
        cerr << "Error opening \"" + filename + "\"\n";
        return 1;
    }

    string input;
    string source_code;
    while(getline(file, input)){
        source_code += " " + input;
    }

    LexicalAnalyzer lexer(source_code);
    vector<Token> tokens = lexer.tokenize();

    // vector<string> tokens;
    // string temp;
    //     for(char c: input){
    //         if(!isspace(c)){
    //             temp += c;
    //         }else{
    //             if (!temp.empty()){
    //                 tokens.push_back(temp);
    //                 temp.clear();
    //             }                
    //         }
    //     }
    //     if (!temp.empty()){
    //         tokens.push_back(temp);
    //     }

    // for (const string& token: tokens)
    // {
    //     cout << token << endl;
    // }

    file.close();
    return 0;
}