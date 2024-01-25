#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include <sstream>

class Parameter {
private:
    std::string value;
    bool isConstant = false;

public:
    Parameter() = default;

    explicit Parameter(std::string &value, TokenType &type) : value(value) {
        isConstant = (type == STRING);
    }

    ~Parameter() = default;

    [[nodiscard]] std::string getValue() const { return value; };

    [[nodiscard]] bool isVar() const { return !isConstant; };

    [[nodiscard]] std::string toString() const {
        stringstream result;
        result << value;
        return result.str();
    };

};

#endif //PARAMETER_H
