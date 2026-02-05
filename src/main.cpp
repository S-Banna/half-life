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
#ifndef PARSER_H
#define PARSER_H
#include "parser.h"
#endif
#include "interpreter.h"
#include "mainPrinter.cpp"

#define WIN32_LEAN_AND_MEAN   // needs to be here to compile
#include <windows.h>

using namespace std;

int main(int argc, char** argv) {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    ifstream source(argv[1]);
    if (!source.is_open()) {
        cerr << "error opening file!" << std::endl;
        return 1;
    }

    string contents((istreambuf_iterator<char>(source)), istreambuf_iterator<char>());
    Lexer* lex = new Lexer(contents);
    vector<Token> tokens = lex->tokenize();

    Parser parser(tokens);
    std::vector<std::unique_ptr<Stmt>> program = parser.parseProgram();

    bool debug = false;
    if (argc >= 3) {
        std::string flag = argv[2];
        if (flag == "true" || flag == "1") {
            debug = true;
            std::cout << "{debug mode enabled}" << "\n";
        }
    }

    Interpreter interpreter(debug);
    interpreter.execute(program);

    return 0;
}