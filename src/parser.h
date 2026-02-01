#include <vector>
#include "ast.h"

class Parser {
    std::vector<Token> tokens;
    size_t pos;

public:
    Parser(const std::vector<Token>& tokens);
    std::vector<std::unique_ptr<Stmt>> parseProgram();

private:
    std::unique_ptr<Stmt> parseStatement();
    std::unique_ptr<Stmt> parseAssume();
    std::unique_ptr<Stmt> parsePrint();
    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseFactor();
    std::unique_ptr<Expr> parsePrimary();
    const Token& peek();
    const Token& advance();
    const Token& previous();
    const Token& consume(TokenType type);
    bool end();
    bool match(TokenType type);
};