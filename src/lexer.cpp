#include <string>

enum class TokenType {
    IDENTIFIER,
    NUMBER,
    KEYWORD_ASSUME,
    KEYWORD_PRINT,
    PLUS,
    EQUAL,
    LPAREN,
    RPAREN,
    NEWLINE,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
};