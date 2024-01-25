#ifndef LEXER_H
#define LEXER_H

#include <cctype>
#include <utility>
#include <vector>
#include <sstream>
#include "Token.h"

class Lexer {
private:
    std::string &input;
    int lineNum;

public:
    explicit Lexer(std::string &input);
    ~Lexer() = default;

    bool isNewLine();

    std::vector<Token> scanFile();

    Token scanToken();

    Token getToken();

    Token idToken(char value);

    Token commentToken(char value);

    Token stringToken(char value);

    Token colonDash();
};

#endif //LEXER_H