#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifndef MAGIC_H
#define MAGIC_H
#include ".\external\magic_enum.hpp"
#endif

#ifndef LEXER_H
#define LEXER_H
#include "lexer.h"
#endif

#include "parser.h"

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
    cout << "\b\b; \n"; // remove the last ->

    Parser parser(tokens);
    std::vector<std::unique_ptr<Stmt>> program = parser.parseProgram();

    std::cout << "Parsed " << program.size() << " statement(s)." << std::endl;
}