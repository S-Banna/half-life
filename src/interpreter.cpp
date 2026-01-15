#include <iostream>
#include <fstream>
#include <string>
#include "lexer.cpp"

using namespace std;

int main(int argc, char** argv) {
    ifstream source(argv[1]);
    if (!source.is_open()) {
        cerr << "error opening file!" << std::endl;
        return 1; 
    }

    string line;
    while (getline(source, line)) {
        if (line.length() == 0 || line.at(0) == '?') continue;
        cout << line << endl;
    }
}