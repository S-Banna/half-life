#include "parser.h"
#include <iostream>
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) { };

const Token& Parser::peek() {
    return tokens.at(pos);
}

const Token& Parser::advance() {
    return tokens.at(pos++);
}

const Token& Parser::previous() {
    return tokens.at(pos - 1);
}

const Token& Parser::consume(TokenType type) {
    try {
        if (peek().type == type)
            return advance();
        else
            throw std::invalid_argument("token does not match expected type to be consumed");
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what();
        std::exit(1);
    }
}

bool Parser::end() {
    return pos >= tokens.size() || peek().type == TokenType::END_OF_FILE;
}

bool Parser::match(TokenType type) {
    if (!end() && peek().type == type) {
        advance();
        return true;
    }
    return false;
}

std::vector<std::unique_ptr<Stmt>> Parser::parseProgram() {
    std::vector<std::unique_ptr<Stmt>> ret {};

    while (!end()) {
        std::unique_ptr<Stmt> curr = parseStatement();
        if (curr)
            ret.push_back(curr);
        while (!end() && peek().type == TokenType::NEWLINE)
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
    if (peek().type == TokenType::QUOTE) {
        std::string s = "";
        consume(TokenType::QUOTE);
        while (peek().type != TokenType::QUOTE) {
            s += advance().lexeme;
        }
        consume(TokenType::QUOTE);
        return std::make_unique<PrintStringStmt>(s);
    }

    std::unique_ptr<PrintStmt> ret = std::make_unique<PrintStmt>();

    consume(TokenType::LPAREN);
    ret->value = parseExpression();
    consume(TokenType::RPAREN);

    return ret;
}

std::unique_ptr<Expr> Parser::parseExpression() {
    return parseTerm();
}

std::unique_ptr<Expr> Parser::parseTerm() {
    std::unique_ptr<Expr> left = parseFactor();

    while (!end() && (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS)) {
        Token op = advance();
        std::unique_ptr<Expr> right = parseFactor();
        left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Expr> Parser::parseFactor() {
    std::unique_ptr<Expr> left = parsePrimary();

    while (!end() && (peek().type == TokenType::MULT || peek().type == TokenType::DIV)) {
        Token op = advance();
        std::unique_ptr<Expr> right = parsePrimary();
        left = std::make_unique<BinaryExpr>(op, std::move(left), std::move(right));
    }

    return left;
}

std::unique_ptr<Expr> Parser::parsePrimary() {
    if (end()) {
        std::cerr << "end of file in parsePrimary";
        std::exit(1);
    }

    switch (peek().type) {
        case TokenType::NUMBER:
            return std::make_unique<NumberExpr>(std::stod(advance().lexeme));
        case TokenType::IDENTIFIER:
            return std::make_unique<IdentifierExpr>(advance().lexeme);
        case TokenType::LPAREN:
            consume(TokenType::LPAREN);
            return parseExpression();
            consume(TokenType::RPAREN);
        default:
            std::cerr << "unexpected token in parsePrimary";
            std::exit(1);
    }
}