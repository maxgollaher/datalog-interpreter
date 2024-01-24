#ifndef SCANNER_H
#define SCANNER_H

#include <cctype>
#include <utility>
#include "Token.h"

using namespace std;


class Scanner {
private:
    string &input;
    int lineNum;

public:
    explicit Scanner(string &input) : input(input), lineNum(1) {}

    ~Scanner() = default;

    int getLine() const { return lineNum; }

    bool isNewLine() {
        return input[0] == '\n' || input[0] == '\v' || input[0] == '\r';
    }

    Token scanToken() {
        // create EOF token if file is empty
        if (input.empty()) return {END, "", lineNum};

        // trim whitespace, if EOF is reached, create EOF token
        while (isspace(input[0])) {
            if (isNewLine()) lineNum++;
            input = input.substr(1);
            if (input.empty()) return {END, "", lineNum};
        }

        // switch cases
        char value = input[0];
        switch (value) {
            case ',':
                if (!input.empty()) input = input.substr(1);
                return {COMMA, ",", lineNum};

            case '.':
                if (!input.empty()) input = input.substr(1);
                return {PERIOD, ".", lineNum};

            case '?':
                if (!input.empty()) input = input.substr(1);
                return {Q_MARK, "?", lineNum};

            case '(':
                if (!input.empty()) input = input.substr(1);
                return {LEFT_PAREN, "(", lineNum};

            case ')':
                if (!input.empty()) input = input.substr(1);
                return {RIGHT_PAREN, ")", lineNum};

            case ':':
                // check COLON_DASH case
                if (input.length() > 1 && input[1] == '-') {
                    input = input.substr(2);
                    return {COLON_DASH, ":-", lineNum};
                } else {
                    if (!input.empty()) input = input.substr(1);
                    return {COLON, ":", lineNum};
                }

            case '*':
                if (!input.empty()) input = input.substr(1);
                return {MULTIPLY, "*", lineNum};

            case '+':
                if (!input.empty()) input = input.substr(1);
                return {ADD, "+", lineNum};

            case '\'': {
                stringstream result;
                // add quote to result, trim input
                result << value;
                if (!input.empty()) input = input.substr(1);
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
                    if (!input.empty())
                        if (!input.empty()) input = input.substr(1);
                    return {STRING, result.str(), lineNum - lineDiff};
                }
                return {UNDEFINED, result.str(), lineNum - lineDiff};
            }

            case '#': {
                stringstream result;
                // add # to result, trim input
                result << value;
                if (!input.empty()) input = input.substr(1);
                value = input[0];

                // add the rest of the line to result and return COMMENT token
                while (!input.empty() && !isNewLine()) {
                    result << value;
                    if (!input.empty()) input = input.substr(1);
                    value = input[0];
                }
                return {COMMENT, result.str(), lineNum};
            }

            default:

                // ID token
                if (isalpha(value)) {
                    stringstream result;
                    while (isalpha(value) || isdigit(value)) {
                        result << value;
                        if (!input.empty()) input = input.substr(1);
                        value = input[0];
                    }

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
        }
        string unrecognizedChar(1, value);
        if (!input.empty()) input = input.substr(1);
        return {UNDEFINED, unrecognizedChar, lineNum}; // unrecognized character
    }
};


#endif //SCANNER_H
