#ifndef PROJECT03_TUPLE_H
#define PROJECT03_TUPLE_H

#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include "Lexer/Scheme.h"
using namespace std;

class Tuple : public vector<string> {

public:
    Tuple() = default;
    explicit Tuple(vector<string> values) : vector<string>(std::move(values)) {}

    [[nodiscard]] string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;

        for (size_t k = 0; k < scheme.size(); k++) {
            out << scheme.at(k) << "=" << tuple.at(k);
            if (k + 1 != scheme.size()) {
                out << ", ";
            }
        }
        return out.str();
    }

};

#endif //PROJECT03_TUPLE_H
