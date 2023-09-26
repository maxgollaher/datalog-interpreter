#ifndef PROJECT03_RELATION_H
#define PROJECT03_RELATION_H

#include "Scheme.h"
#include "Tuple.h"
#include <set>
#include <map>

class Relation {
private:
    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:
    Relation() = default;

    ~Relation() = default;

    Relation(const string &name, const Scheme &scheme)
            : name(name), scheme(scheme) {}

    void addTuple(const Tuple &tuple) {
        tuples.insert(tuple);
    }

    [[nodiscard]] Scheme getScheme() const { return scheme; }

    void setScheme(const Scheme &sch) { this->scheme = sch; }

    size_t size() { return tuples.size(); }

    bool empty() { return (tuples.empty()); }

    [[nodiscard]] Relation select(int index, const string &value) const {
        Relation result(name, scheme);
        for (Tuple t: tuples) {
            if (t.at(index) == value) {
                result.addTuple(t);
            }
        }
        return result;
    }

    Relation equalSelect(int col1, int col2) {
        Relation result(name, scheme);
        for (Tuple t: tuples) {
            if (t.at(col1) == t.at(col2)) {
                result.addTuple(t);
            }
        }
        return result;
    }

    Relation project(const vector<int> &cols) {
        vector<string> names;
        for (int i: cols) {
            names.push_back(scheme.at(i));
        }
        Scheme resultScheme = Scheme(names);
        Relation result(name, resultScheme);

        for (Tuple t: tuples) {
            Tuple projectedTuple;
            for (const int &i: cols) {
                projectedTuple.push_back(t.at(i));
            }
            result.addTuple(projectedTuple);
        }


        return result;
    }

    Relation rename(const vector<string> &vars) {
        vector<string> names;
        for (const auto &v: vars) {
            names.push_back(v);
        }
        Relation result(name, Scheme(names));
        for (const Tuple &t: tuples) {
            result.addTuple(t);
        }
        return result;
    }

    static bool joinable(const Scheme &leftScheme, const Scheme &rightScheme,
                         const Tuple &leftTuple, const Tuple &rightTuple) {
        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string &leftName = leftScheme.at(leftIndex);
            const string &leftValue = leftTuple.at(leftIndex);

            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string &rightName = rightScheme.at(rightIndex);
                const string &rightValue = rightTuple.at(rightIndex);

                if (rightName == leftName && rightValue != leftValue) {
                    return false;
                }
            }
        }
        return true;
    }

    Relation join(const Relation &right) {

        // if joining as a way of populating an empty database, just add the right relation
        if (this->tuples.empty()) {
            Relation result = Relation(this->name, right.scheme);
            for (const Tuple &rightTuple: right.tuples) {
                result.addTuple(rightTuple);
            }
            return result;

        } else {
            // create an empty relation, populate it with schemes and new joined tuples
            Relation result = Relation(this->name, this->joinSchemes(right));

            for (const Tuple &leftTuple: this->tuples) {
                for (const Tuple &rightTuple: right.tuples) {
                    if (joinable(this->scheme, right.scheme, leftTuple, rightTuple)) {
                        Tuple resultTuple = result.joinTuples(this->scheme, right.scheme, leftTuple, rightTuple);
                        result.addTuple(resultTuple);
                    }
                }
            }
            return result;
        }

    }

    /** joins the schemes of two relation objects
     *
     * @param this the first relation object
     * @param right the second relation object
     * @return the joined scheme
     */
    Scheme joinSchemes(const Relation &rightRelation) {
        const Scheme &left = this->scheme;
        const Scheme &right = rightRelation.scheme;
        Scheme result;

        for (const string &leftValue: left) {
            result.push_back(leftValue);
        }
        for (const string &rightValue: right) {
            result.push_back(rightValue);
            for (const string &leftValue: left) {
                if (leftValue == rightValue) {
                    result.pop_back();
                    break;
                }
            }
        }
        return result;
    }

    Tuple joinTuples(const Scheme &leftScheme, const Scheme &rightScheme, const Tuple &left, const Tuple &right) {
        const Scheme &joinScheme = this->scheme;
        Tuple result;

        for (size_t i = 0; i < joinScheme.size(); i++) {
            if (i < leftScheme.size()) {
                result.push_back(left.at(i));

            } else {
                size_t rightIndex = (i - leftScheme.size());
                while (rightScheme[rightIndex] != joinScheme[i]) {
                    rightIndex++;
                }
                result.push_back(right[rightIndex]);
            }
        }

        return result;
    }

    [[nodiscard]] string toString() const {
        stringstream out;
        for (const Tuple &t: tuples) {
            out << "  " << t.toString(scheme) << endl;
        }
        return out.str();
    }

    Relation &unionRelation(const Relation &right) {
        Relation &result = *this;
        for (const Tuple &tuple: right.tuples) {
            unsigned beforeSize = result.tuples.size();
            result.addTuple(tuple);
            if (beforeSize != result.tuples.size()) {
                cout << "  " << tuple.toString(result.scheme) << endl;
            }
        }
        return result;
    }
};

#endif //PROJECT03_RELATION_H
