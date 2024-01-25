#ifndef PROJECT02_PREDICATE_H
#define PROJECT02_PREDICATE_H

#include <string>
#include "Parameter.h"
#include <vector>
#include <sstream>

using namespace std;

class Predicate {
private:
    string name;
    vector<Parameter> parameters;

public:
    Predicate() = default;

    explicit Predicate(string &name) : name(name) {};

    explicit Predicate(string &name, vector<Parameter> &parameters) : name(name),
                                                                      parameters(parameters) {};

    ~Predicate() = default;

    [[nodiscard]] string getName() const { return name; }

    [[nodiscard]] vector<Parameter> getParams() const { return parameters; }

    void add(const Parameter &param) { parameters.push_back(param); }

    [[nodiscard]] string paramList() const {
        stringstream result;
        for (const Parameter &param: parameters) {
            result << param.getValue() << ",";
        }
        string output = result.str();
        if (!output.empty()) output.pop_back(); // remove trailing comma
        return output;
    }

    [[nodiscard]] vector<string> paramVector() const {
        vector<string> result;
        for (const Parameter &param: parameters) {
            result.push_back(param.getValue());
        }
        return result;
    }


    [[nodiscard]] string toString() const {
        stringstream result;
        result << name << "(" << paramList() << ")";
        return result.str();
    }

};

#endif //PROJECT02_PREDICATE_H
