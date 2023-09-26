#ifndef PROJECT02_PARAMETER_H
#define PROJECT02_PARAMETER_H

#include <string>
#include <sstream>

using namespace std;

class Parameter {
private:
    string value;
    bool isConstant = false;

public:
    Parameter() = default;

    explicit Parameter(string &value, TokenType &type) : value(value) {
        isConstant = (type == STRING);
    }

    ~Parameter() = default;

    [[nodiscard]] string getValue() const { return value; };

    [[nodiscard]] bool isVar() const { return !isConstant; };

    [[nodiscard]] string toString() const {
        stringstream result;
        result << value;
        return result.str();
    };

};

#endif //PROJECT02_PARAMETER_H
