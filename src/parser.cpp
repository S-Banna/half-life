#include "parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) { };

std::vector<std::unique_ptr<Stmt>> Parser::parseProgram() {
    std::vector<std::unique_ptr<Stmt>> ret {};

    while (!end()) {
        std::unique_ptr<Stmt> curr = parseStatement();
        if (curr)
            ret.push_back(curr);
        while (peek().type == TokenType::NEWLINE)
            advance();
    }

    return ret;
}

std::unique_ptr<Stmt> Parser::parseStatement() {
    if (match(TokenType::KEYWORD_ASSUME))
        return parseAssume();
    else if (match(TokenType::KEYWORD_PRINT))
        return parsePrint();

    advance();
    return nullptr;
}

std::unique_ptr<Stmt> Parser::parseAssume() {
    std::unique_ptr<AssumeStmt> ret = std::make_unique<AssumeStmt>();

    ret->name = consume(TokenType::IDENTIFIER).lexeme;
    consume(TokenType::EQUAL);
    ret->value = parseExpression();

    return ret;
}

std::unique_ptr<Stmt> Parser::parsePrint() {
    std::unique_ptr<PrintStmt> ret = std::make_unique<PrintStmt>();

    consume(TokenType::LPAREN);
    ret->value = parseExpression();
    consume(TokenType::RPAREN);

    return ret;
}