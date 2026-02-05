#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
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
    std::mt19937 rng;
    std::bernoulli_distribution odds{0.5};
    bool debug = false;
    std::string corruption[3] = { "▓", "░", "⧎" };

public:
    void execute(const std::vector<std::unique_ptr<Stmt>>& program);
    Interpreter(bool debug) : rng(std::random_device{}()), debug(debug) {};

private:
    void state(const Stmt* stmt);
    double evaluate(const Expr* expr);
    void decay();
    void decayPrint(std::string str);
};