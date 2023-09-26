#ifndef PROJECT02_DATALOG_PROGRAM_H
#define PROJECT02_DATALOG_PROGRAM_H

#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include <set>

class DatalogProgram {
private:
    vector<Predicate> schemeList;
    vector<Predicate> factList;
    vector<Rule> ruleList;
    vector<Predicate> queryList;
    set <string> domainList;

public:
    DatalogProgram() = default;

    ~DatalogProgram() = default;

    void addSchemes(const Predicate &scheme) { schemeList.push_back(scheme); };

    void addFacts(const Predicate &fact) { factList.push_back(fact); };

    void addRules(const Rule& rule) { ruleList.push_back(rule); };

    void addQueries(const Predicate &query) { queryList.push_back(query); };

    [[nodiscard]] bool noSchemes() const { return schemeList.empty(); }

    [[nodiscard]] bool noQueries() const { return queryList.empty(); }

    [[nodiscard]] vector<Predicate> getSchemes() const { return schemeList; }

    [[nodiscard]] vector<Predicate> getFacts() const { return factList; }

    [[nodiscard]] vector<Rule> getRules() const { return ruleList; }

    [[nodiscard]] vector<Predicate> getQueries() const { return queryList; }

    /**Adds all of the parameters in factList to the domainList set */
    void addDomains() {
        for (const Predicate &fact: factList) {
            for (const Parameter &param: fact.getParams()) {
                string value = param.getValue();
                domainList.insert(value);
            }
        }
    };

    string toString() {
        stringstream result;

        result << "Schemes(" << schemeList.size() << "):" << endl;
        for (const Predicate &scheme: schemeList) {
            result << "  " << scheme.toString() << endl;
        }

        result << "Facts(" << factList.size() << "):" << endl;
        for (const Predicate &fact: factList) {
            result << "  " << fact.toString() << "." << endl;
        }

        result << "Rules(" << ruleList.size() << "):" << endl;
        for (const Rule &rule: ruleList) {
            result << "  " << rule.toString() << endl;
        }

        result << "Queries(" << queryList.size() << "):" << endl;
        for (const Predicate &query: queryList) {
            result << "  " << query.toString() << "?" << endl;
        }

        addDomains();
        result << "Domain(" << domainList.size() << "):" << endl;
        for (const string &domain: domainList) {
            result << "  " << domain << endl;
        }

        return result.str();
    }

};


#endif //PROJECT02_DATALOG_PROGRAM_H
