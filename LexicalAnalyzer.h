#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <string>

namespace compiler
{ 
    enum TokenType{
        Identifier,
        Keyword,
        Operator,
        Literal
    };

    struct Token{
        std::string value;
        TokenType type;
        Token(TokenType t, const std::string& v): type(t), value(v)
        {

        }
    };

    class LexicalAnalyzer {
    private:
        std::string input;
        int position;
        

        bool isWhiteSpace(char c);
        bool isLetter(char c);
        bool isDigit(char c);
        std::string removeComments(const std::string& input);
        std::string getNextWord(int position, std::string text);

    public:
        LexicalAnalyzer(const std::string& input);
        std::string tokenize();
    };
}
#endif