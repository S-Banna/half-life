#include "interpreter.h"

void Interpreter::execute(const std::vector<std::unique_ptr<Stmt>>& program) {
    for (const auto& stmt : program) {
        state(stmt.get());
        decay();
    }
}

void Interpreter::state(const Stmt* stmt) {
    if (auto assume = dynamic_cast<const AssumeStmt*>(stmt)) {
        double value = evaluate(assume->value.get());
        env[assume->name] = value;
    } else if (auto print = dynamic_cast<const PrintStmt*>(stmt)) {
        double value = evaluate(print->value.get());
        std::cout << value << "\n";
    } else if (auto str = dynamic_cast<const PrintStringStmt*>(stmt)) {
        decayPrint(str->value);
    } else {
        std::cerr << "Unknown statement type\n";
        std::exit(1);
    }
}

double Interpreter::evaluate(const Expr* expr) {
    if (auto num = dynamic_cast<const NumberExpr*>(expr)) {
        return num->number;
    }
    if (auto id = dynamic_cast<const IdentifierExpr*>(expr)) {
        return env[id->id];
    }
    if (auto bin = dynamic_cast<const BinaryExpr*>(expr)) {
        double left = evaluate(bin->left.get());
        double right = evaluate(bin->right.get());

        switch (bin->op) {
            case TokenType::PLUS:
                return left + right;
            case TokenType::MINUS:
                return left - right;
            case TokenType::MULT:
                return left * right;
            case TokenType::DIV:
                return left / right;
            default:
                std::cerr << "Unknown operator\n";
                std::exit(1);
        }
    }

    std::cerr << "Unknown expression type\n";
    std::exit(1);
}

void Interpreter::decay() {
    for (auto& [id, num] : env) {
        if (odds(rng)) {
            if (debug)
                std::cout << "{debug: " << id
                          << " decays from " << num
                          << " to " << num / 2.0
                          << "}\n";
            num /= 2.0;
        }
    }
}

void Interpreter::decayPrint(std::string str) {
    std::uniform_real_distribution<double> chance(0.0, 1.0);
    std::discrete_distribution<int> pick({5, 1, 3});

    for (char c : str) {
        if (c != ' ' && chance(rng) < 0.18) {
            std::cout << corruption[pick(rng)];
        } else {
            std::cout << c;
        }
    }

    std::cout << '\n';
}