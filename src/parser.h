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
    std::unique_ptr<Expr> parseExpression();
    bool end();
    bool match(TokenType type);
    Token peek();
    Token advance();
    Token previous();
};