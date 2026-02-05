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

void printIndent(int indent) {
    for (int i = 0; i < indent; i++)
        std::cout << "  ";
}

void printExpr(const Expr* expr, int indent) {
    printIndent(indent);

    if (auto num = dynamic_cast<const NumberExpr*>(expr)) {
        std::cout << "NumberExpr: " << num->number << "\n";
    } else if (auto id = dynamic_cast<const IdentifierExpr*>(expr)) {
        std::cout << "IdentifierExpr: " << id->id << "\n";
    } else if (auto bin = dynamic_cast<const BinaryExpr*>(expr)) {
        std::cout << "BinaryExpr: " << magic_enum::enum_name(bin->op) << "\n";
        printExpr(bin->left.get(), indent + 1);
        printExpr(bin->right.get(), indent + 1);
    } else {
        std::cout << "Unknown Expr\n";
    }
}

void printStmt(const Stmt* stmt, int indent) {
    printIndent(indent);

    if (auto assume = dynamic_cast<const AssumeStmt*>(stmt)) {
        std::cout << "AssumeStmt: " << assume->name << "\n";
        printExpr(assume->value.get(), indent + 1);
    } else if (auto print = dynamic_cast<const PrintStmt*>(stmt)) {
        std::cout << "PrintStmt\n";
        printExpr(print->value.get(), indent + 1);
    } else if (auto printStr = dynamic_cast<const PrintStringStmt*>(stmt)) {
        std::cout << "PrintStringStmt: \"" << printStr->value << "\"\n";
    } else {
        std::cout << "Unknown Stmt\n";
    }
}

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

    for (const auto& i : program) {
        printStmt(i.get(), 0);
    }
}