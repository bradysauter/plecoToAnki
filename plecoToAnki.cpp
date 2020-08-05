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


    input.close();
    output.close();
    return 0;
}