#include <string>
#include <memory>
#include "lexer.h"

struct ASTNode {
    virtual ~ASTNode() = default;
};



struct Expr : public ASTNode {
    virtual ~Expr() = default;
};

struct NumberExpr : public Expr {
    double number;
};

struct IdentifierExpr : public Expr {
    std::string id;
};

struct BinaryExpr : public Expr {
    TokenType op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
};



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