#ifndef PROJECT02_RULE_H
#define PROJECT02_RULE_H

#include "Parameter.h"
#include "Predicate.h"
#include "Token.h"
#include <string>
#include <sstream>

using namespace std;

class Rule {
private:
    Predicate headPredicate;
    vector<Predicate> parameters;

public:
    Rule() = default;

    Rule(Predicate &head, vector<Predicate> &params) : headPredicate(head), parameters(params) {};
    explicit Rule(const Predicate& head) : headPredicate(head) {};

    ~Rule() = default;

    [[nodiscard]] string getHead() const { return headPredicate.toString(); }

    [[nodiscard]] string getName() const { return headPredicate.getName(); }

    [[nodiscard]] Predicate headPred() const { return headPredicate; }

    [[nodiscard]] vector<Predicate> getParams() const { return parameters; }

    [[nodiscard]] string paramList() const {
        stringstream result;
        for (const Predicate &param: parameters) {
            result << param.toString() << ",";
        }
        string output = result.str();
        output.pop_back(); // remove trailing comma
        return output;
    }

    void addBodyPredicate(const Predicate& predicate) {
        parameters.push_back(predicate);
    }

    [[nodiscard]] string toString() const {
        stringstream result;
        result << getHead() << " :- " << paramList();
        return result.str();
    }


};

#endif //PROJECT02_RULE_H
