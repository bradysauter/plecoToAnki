#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <unordered_set>
using namespace std;

class toAnki {
  private:
    unordered_set<string> partsOfSpeech;
    ifstream input;
    ofstream output;
    string buffer;

  public:
    toAnki(string inputFile = "plecoExport.txt", 
                string outputFile = "ankiImport.txt") {

        createPartsOfSpeechSet();
        input.open(inputFile);
        remove(outputFile.c_str());    
        output.open(outputFile);
    }

    ~toAnki() {
        input.close();
        output.close();
    }

    bool plecoToAnki() {
        while (getline (input, buffer, '\t')) {
            // simplified characters
            output << buffer << '\t';
            // pinyin
            getline (input, buffer, '\t');
            output << buffer << '\t';
            // definition
            getline (input, buffer);
            output << buffer << endl;


            //output << "<ol><li>";
            //for (int i = 0; i < buffer.size(); i++) {

            //}
            //output << "</ol>";
        }
    }

    void createPartsOfSpeechSet() {
        vector<string> partOfSpeechVector = {"noun", "verb", "adjective", "adverb", "pronoun",
                                            "preposition", "conjunction","interjection", 
                                            "numeral", "article", "determiner"};
        for (auto i : partOfSpeechVector) {
            partsOfSpeech.insert(i);
        }
    }

    bool isPartOfSpeech(string s) {
        if (partsOfSpeech.find(s) != partsOfSpeech.end()) {
            return true;
        }
        return false;
    }
};

int main() {
    toAnki myConverter("plecoExport.txt", "ankiImport.txt");
    myConverter.plecoToAnki();
    
    return 0;
}