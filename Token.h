#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <sstream>
#include <utility>

using namespace std;

enum TokenType {
    COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES,
    QUERIES, ID, STRING, COMMENT, UNDEFINED, END
};

class Token {
private:
    TokenType type{};
    string value;
    int line{};

public:
    Token() = default;

    Token(TokenType type, string value, int line) : type(type), value(std::move(value)), line(line) {};

    ~Token() = default;

    [[nodiscard]] TokenType getType() const { return type; };

    [[nodiscard]] string getValue() const { return value; };

    [[nodiscard]] int getLine() const { return line; };

    [[nodiscard]] string toString() const {
        stringstream out;
        out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
        return out.str();
    };

    static string typeName(TokenType type) {
        static string enumValues[] = {
                "COMMA", "PERIOD", "Q_MARK", "LEFT_PAREN", "RIGHT_PAREN", "COLON", "COLON_DASH",
                "MULTIPLY", "ADD", "SCHEMES", "FACTS", "RULES", "QUERIES", "ID", "STRING", "COMMENT",
                "UNDEFINED", "EOF"
        };
        return enumValues[type];
    };

};


#endif // TOKEN_H