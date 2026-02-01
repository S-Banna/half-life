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

    Token ret = { TokenType::NUMBER, n };
    return ret;
}

Token Lexer::lexIdentifierOrKeyword() {
    std::string n(1, advance());
    while (!end() && std::isalnum(peek())) {
        n += advance();
    }

    Token ret;
    if (n == "assume") {
        ret = { TokenType::KEYWORD_ASSUME, n };
    } else if (n == "print") {
        ret = { TokenType::KEYWORD_PRINT, n };
    } else {
        ret = { TokenType::IDENTIFIER, n };
    }

    return ret;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> ret;

    while (!end()) {
        char c = peek();
        bool atLineStart = true;

        if (atLineStart && c == '?') {
            while (!end() && peek() != '\n') {
                advance();
            }
            continue;
        }

        switch (c) {
            case '+':
                ret.push_back(Token { TokenType::PLUS, "+" });
                advance();
                break;
            case '-':
                ret.push_back(Token { TokenType::MINUS, "-" });
                advance();
                break;
            case '*':
                ret.push_back(Token { TokenType::MULT, "*" });
                advance();
                break;
            case '/':
                ret.push_back(Token { TokenType::DIV, "/" });
                advance();
                break;
            case '=':
                ret.push_back(Token { TokenType::EQUAL, "=" });
                advance();
                break;
            case '(':
                ret.push_back(Token { TokenType::LPAREN, "(" });
                advance();
                break;
            case ')':
                ret.push_back(Token { TokenType::RPAREN, ")" });
                advance();
                break;
            case '\n':
                ret.push_back(Token { TokenType::NEWLINE, "\n" });
                advance();
                atLineStart = true;
                break;
            case ' ':
                advance();
                break;
            case '"':
                ret.push_back(Token { TokenType::QUOTE, "\""});
                advance();
                break;
            default:
                if (isalpha(c)) {
                    ret.push_back(lexIdentifierOrKeyword());
                } else if (isdigit(c)) {
                    ret.push_back(lexNumber());
                } else {
                    advance();
                }
        }
    }

    ret.push_back(Token { TokenType::END_OF_FILE, "\0" });
    return ret;
}