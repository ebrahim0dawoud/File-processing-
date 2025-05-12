#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void findAndReplace(const string& filename, const string& searchWord, const string& replaceWord) {
    ifstream fileIn(filename);
    if (!fileIn) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    ostringstream buffer;
    buffer << fileIn.rdbuf();
    string content = buffer.str();
    fileIn.close();

    size_t pos = 0;
    while ((pos = content.find(searchWord, pos)) != string::npos) {
        content.replace(pos, searchWord.length(), replaceWord);
        pos += replaceWord.length();
    }

    ofstream fileOut(filename);
    if (!fileOut) {
        cerr << "Error: Unable to write to file." << endl;
        return;
    }
    fileOut << content;
    fileOut.close();

    cout << "Replacement completed successfully." << endl;
}

int main() {
    string filename, searchWord, replaceWord;
    cout << "Enter file name: ";
    cin >> filename;
    cout << "Enter word to search: ";
    cin >> searchWord;
    cout << "Enter word to replace with: ";
    cin >> replaceWord;

    findAndReplace(filename, searchWord, replaceWord);

    return 0;
}
