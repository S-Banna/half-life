#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include ".\external\magic_enum.hpp"
#include "lexer.h"

using namespace std;

int main(int argc, char** argv) {
    ifstream source(argv[1]);
    if (!source.is_open()) {
        cerr << "error opening file!" << std::endl;
        return 1;
    }

    string contents((istreambuf_iterator<char>(source)), istreambuf_iterator<char>());
    Lexer* lex = new Lexer(contents);
    vector<Token> tokens = lex->tokenize();

    for (const Token& t : tokens) {
        cout << magic_enum::enum_name(t.type) << "->";
    }
    cout << "\b\b; \n"; // remove the last
}