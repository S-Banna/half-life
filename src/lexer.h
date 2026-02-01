#include <string>
#include <vector>

enum class TokenType {
    IDENTIFIER,
    NUMBER,
    KEYWORD_ASSUME,
    KEYWORD_PRINT,
    PLUS,
    MINUS,
    MULT,
    DIV,
    EQUAL,
    LPAREN,
    RPAREN,
    QUOTE,
    NEWLINE,
    END_OF_FILE
};

struct Token {
    TokenType type;
    std::string lexeme;
};

class Lexer {
    std::string source;
    size_t pos;

public:
    Lexer(const std::string& src);
    std::vector<Token> tokenize();

private:
    char peek();
    char advance();
    bool end();

    Token lexNumber();
    Token lexIdentifierOrKeyword();
};