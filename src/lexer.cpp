#include "lexer.h"
#include <iostream>
#include <string>
#include <vector>

Lexer::Lexer(const std::string& src)
    : source(src), pos(0) { };

char Lexer::peek() {
    return source.at(pos);
}

char Lexer::advance() {
    return source.at(pos++);
}

bool Lexer::end() {
    return pos >= source.length();
}

Token Lexer::lexNumber() {
    std::string n(1, advance());
    while (!end() && std::isdigit(peek())) {
        n += advance();
    }

    Token ret = {TokenType::NUMBER, n};
    return ret;
}

Token Lexer::lexIdentifierOrKeyword() {
    std::string n(1, advance());
    while (!end() && std::isalnum(peek())) {
        n += advance();
    }

    Token ret;
    if (n == "assume") {
        ret = {TokenType::KEYWORD_ASSUME, n};
    } else if (n == "print") {
        ret = {TokenType::KEYWORD_PRINT, n};
    } else {
        ret = {TokenType::IDENTIFIER, n};
    }

    return ret;
}