#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#ifndef MAGIC_H
#define MAGIC_H
#include ".\external\magic_enum.hpp"
#endif
#ifndef PARSER_H
#define PARSER_H
#include "parser.h"
#endif

class Interpreter {
    std::unordered_map<std::string, double> env;

public:
    void execute(const std::vector<std::unique_ptr<Stmt>>& program);

private:
    void state(const Stmt* stmt);
    double evaluate(const Expr* expr);
};