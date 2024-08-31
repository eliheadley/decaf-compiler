# include <iostream>
using namespace std;

void printString(const string& source){
    for(int i = 0; i < source.length(); i++)
    cout << source[i] << endl;
}

int main(){
    string word = "hello";
    printString(word);
    return 0;
}