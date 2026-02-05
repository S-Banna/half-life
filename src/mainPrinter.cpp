#include <iostream>

#ifndef LEXER_H
#define LEXER_H
#include "lexer.h"
#endif
#ifndef PARSER_H
#define PARSER_H
#include "parser.h"
#endif
#ifndef MAGIC_H
#define MAGIC_H
#include ".\external\magic_enum.hpp"
#endif

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
