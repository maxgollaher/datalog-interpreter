#include "Lexer.h"

Lexer::Lexer(std::string &input) : input(input), lineNum(1) {
}

bool Lexer::isNewLine() {
    return input[0] == '\n' || input[0] == '\v' || input[0] == '\r';
}

std::vector<Token> Lexer::scanFile() {
    int totalTokens = 0;
    Token t = Token();
    std::vector<Token> tokens;
    do {
        // create token for each token in line
        t = this->scanToken();
        if (t.getType() != COMMENT) tokens.push_back(t);  // skip comments
        totalTokens++;
    } while (!input.empty());

    // if no EOF token created, create one
    if (t.getType() == UNDEFINED || input.empty()) {
        t = Token(END, "", lineNum);
        tokens.push_back(t);
        totalTokens++;
    }
    return tokens;
}

Token Lexer::scanToken() {
    // create EOF token if file is empty
    if (input.empty()) return {END, "", lineNum};

    // trim whitespace, if EOF is reached, create EOF token
    while (std::isspace(input[0])) {
        if (isNewLine()) lineNum++;
        input = input.substr(1);
        if (input.empty()) return {END, "", lineNum};
    }

    // switch cases
    return getToken();
}

Token Lexer::getToken() {
    char value = input[0];
    if (!input.empty()) input = input.substr(1);
    switch (value) {
        case ',':
            return {COMMA, ",", lineNum};

        case '.':
            return {PERIOD, ".", lineNum};

        case '?':
            return {Q_MARK, "?", lineNum};

        case '(':
            return {LEFT_PAREN, "(", lineNum};

        case ')':
            return {RIGHT_PAREN, ")", lineNum};

        case ':':
            return colonDash(); // check COLON_DASH case

        case '*':
            return {MULTIPLY, "*", lineNum};

        case '+':
            return {ADD, "+", lineNum};

        case '\'':
            return stringToken(value);

        case '#':
            return commentToken(value);

        default:
            // ID tokens and other multi-character tokens
            if (std::isalpha(value)) {
                return idToken(value);
            }
    }
    std::string unrecognizedChar(1, value);
    return {UNDEFINED, unrecognizedChar, lineNum}; // unrecognized character
}

Token Lexer::idToken(char value) {
    std::stringstream result;
    do {
        result << value;
        value = input[0];
        if (!input.empty() && std::isalnum(value)) input = input.substr(1);
    } while (std::isalnum(value));

    // all ID tokens are compared with preset functions, those
    // functions are given priority over the ID token
    if (result.str() == "Schemes") {
        return {SCHEMES, "Schemes", lineNum};

    } else if (result.str() == "Facts") {
        return {FACTS, "Facts", lineNum};

    } else if (result.str() == "Rules") {
        return {RULES, "Rules", lineNum};

    } else if (result.str() == "Queries") {
        return {QUERIES, "Queries", lineNum};
    }
    return {ID, result.str(), lineNum};
}

Token Lexer::commentToken(char value) {
    std::stringstream result;
    // add # to result, trim input
    result << value;
    value = input[0];

    // add the rest of the line to result and return COMMENT token
    while (!input.empty() && !isNewLine()) {
        result << value;
        if (!input.empty()) input = input.substr(1);
        value = input[0];
    }
    return {COMMENT, result.str(), lineNum};
}

Token Lexer::stringToken(char value) {
    std::stringstream result;
    // add quote to result, trim input
    result << value;
    value = input[0];

    // trim input/add to result until quote found/EOF reached
    int lineDiff = 0;
    while (value != '\'' && !input.empty()) {

        // increment lineDiff for multi-line strings
        if (isNewLine()) {
            lineNum++;
            lineDiff++;
        }
        result << value;
        if (!input.empty()) input = input.substr(1);
        value = input[0];

        // apostrophe case
        if (input.length() > 1 && input.substr(0, 2) == "''") {
            result << input.substr(0, 2);
            input = input.substr(2);
            value = input[0];
        }
    }
    // add final quote, unless EOF was reached, else create a UNDEFINED string token
    if (value == '\'') {
        result << value;
        if (!input.empty()) input = input.substr(1);
        return {STRING, result.str(), lineNum - lineDiff};
    }
    return {UNDEFINED, result.str(), lineNum - lineDiff};
}

Token Lexer::colonDash() {
    if (!input.empty() && input[0] == '-') {
        input = input.substr(1);
        return {COLON_DASH, ":-", lineNum};
    } else {
        return {COLON, ":", lineNum};
    }
}
