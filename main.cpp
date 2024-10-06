#include <string>
#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

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

    // string file_name = argv[1];
    string file_name = "test/t4.decaf";
    string src_code;
    readFile(file_name, &src_code);
   
    LexicalAnalyzer lexer = LexicalAnalyzer(&src_code);
    lexer.tokenize();
    lexer.printTokens();

    return 0;
}