#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

int main() {
    ifstream input("plecoExport.txt");
    string outputFile = "ankiImport.txt";
    remove(outputFile.c_str());    
    ofstream output(outputFile);
    string buffer;

    while (getline (input, buffer, '\t')) {
        // simplified characters
        output << buffer << '\t';
        // pinyin
        getline (input, buffer, '\t');
        output << buffer << '\t';
        // definition
        getline (input, buffer);
        output << buffer << endl;
    }
    
    input.close();
    output.close();
    return 0;
}