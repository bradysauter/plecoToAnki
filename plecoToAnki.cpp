#include <iostream>
#include <fstream>
#include <sstream>
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
        string buffer;
        while (getline (input, buffer)) {
            stringstream ss(buffer);
            // simplified characters
            getline(ss, buffer, '\t');
            output << buffer << '\t';
            // pinyin
            getline (ss, buffer, '\t');
            output << buffer << '\t';
            // definition
            formatPlecoDefinition(ss);
        }
    }

    void formatPlecoDefinition(stringstream& ss) {
        if (!ss.good()) return;
        output << "<ol>";
        string buffer;
        bool insertNewline = true;
        while (ss >> buffer) {
            if (isNumber(buffer)) {
                insertNewline = true;
            }
            else if (isPartOfSpeech(buffer)) {
                insertNewline = true;
            }
            else if (buffer[buffer.length() - 1] == ';') {
                if (insertNewline) {
                    output << "<li>";
                }
                output << buffer.substr(0, buffer.length() - 1);
                insertNewline = true;
            }
            else {
                if (insertNewline) {
                    output << "<li>";
                }
                output << buffer << " ";
                insertNewline = false;
            }
        }
        output << "</ol>" << endl;
    }

    void createPartsOfSpeechSet() {
        vector<string> partOfSpeechVector = {"noun", "verb", "adjective", "adverb", "pronoun",
                                            "preposition", "conjunction","interjection", 
                                            "numeral", "article", "determiner"};
        for (auto i : partOfSpeechVector) {
            partsOfSpeech.insert(i);
        }
    }

    inline bool isPartOfSpeech(string s) {
        if (partsOfSpeech.find(s) != partsOfSpeech.end()) {
            return true;
        }
        return false;
    }

    inline bool isNumber(string s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] < '0' || s[i] > '9') {
                return false;
            }
        }
        return true;
    }
    inline bool isNumber(char c) {
        if (c < '0' || c > '9') {
            return false;
        }
        return true;
    }
};

int main() {
    toAnki myConverter("plecoExport.txt", "ankiImport.txt");
    myConverter.plecoToAnki();

    return 0;
}