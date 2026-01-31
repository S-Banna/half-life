#include "parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {};

std::vector<std::unique_ptr<Stmt>> Parser::parseProgram() {
    std::vector<std::unique_ptr<Stmt>> ret;
    while (!end()) {
        ret.push_back(parseStatement());
    }
    return ret;
}