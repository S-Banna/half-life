#include <memory>
#include <string>
#include "lexer.h"

struct ASTNode {
    virtual ~ASTNode() = default;
};

// Expressions

struct Expr : public ASTNode {
    virtual ~Expr() = default;
};

struct NumberExpr : public Expr {
    double number;
    NumberExpr(double n) : number(n) { }
};

struct IdentifierExpr : public Expr {
    std::string id;
    IdentifierExpr(const std::string& s) : id(s) { }
};

struct BinaryExpr : public Expr {
    TokenType op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
    BinaryExpr(TokenType op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
        : op(op), left(std::move(left)), right(std::move(right)) { }
};

// Statements

struct Stmt : public ASTNode {
    virtual ~Stmt() = default;
};

struct AssumeStmt : public Stmt {
    std::string name;
    std::unique_ptr<Expr> value;
};

struct PrintStmt : public Stmt {
    std::unique_ptr<Expr> value;
};