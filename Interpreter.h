#ifndef PROJECT03_INTERPRETER_H
#define PROJECT03_INTERPRETER_H

#include <iostream>
#include "Relation.h"
#include "DatalogProgram.h"
#include "Database.h"
#include "Scheme.h"
#include "Graph.h"

class Interpreter {
private:
    DatalogProgram datalog;
    Database database;

public:
    explicit Interpreter(DatalogProgram &datalog) : datalog(datalog), database() {
        evalSchemes();
        evalFacts();
        evalRules();
        evalQueries();
    };

    void evalSchemes() {
        for (const Predicate &s: datalog.getSchemes()) {
            Scheme scheme = Scheme(s.paramVector());
            Relation relationInit = Relation(s.getName(), scheme);
            database[s.getName()] = relationInit;
        }
    };

    void evalFacts() {
        for (const Predicate &f: datalog.getFacts()) {
            database[f.getName()].addTuple(Tuple(f.paramVector()));
        }
    };

    // needs to evaluate things a second time. this is incorrect...
    void evalRules() {
        cout << "Rule Evaluation" << endl;
        bool changed = true;
        int relationStep = 0;

        while (changed) {
            changed = false;
            relationStep++;
            for (const Rule &r: datalog.getRules()) {
                cout << r.toString() << endl;
                Predicate head = r.headPred();
                string ruleName = head.getName();

                Relation currDatabase = database[ruleName];

                // create a vector to store each relation object for the right-side parameters
                vector<Relation> relObjects;
                for (const Predicate &q: r.getParams()) {
                    string name = q.getName();
                    Relation relObject = database[name]; // get the current facts/scheme of the rule, evaluate
                    map<string, int> queryVars;
                    vector<string> vars;
                    vector<int> cols;

                    int index = 0;
                    for (const Parameter &p: q.getParams()) {
                        if (p.isVar()) {
                            int dupIndex = duplicateQuery(p, queryVars);
                            if (dupIndex != -1) {
                                relObject = relObject.equalSelect(dupIndex, index);
                            } else {
                                queryVars[p.getValue()] = index;
                                vars.push_back(p.getValue());
                                cols.push_back(index);
                            }
                        } else {
                            relObject = relObject.select(index, p.getValue());
                        }
                        index++;
                    }

                    relObject = relObject.project(cols);
                    relObject = relObject.rename(vars);
                    relObjects.push_back(relObject);
                }

                // join the relations that result from the pass
                Relation joinedRelations;
                for (const Relation &relation: relObjects) {
                    joinedRelations = joinedRelations.join(relation);
                }

                vector<int> cols;
                for (const string &var: head.paramVector()) {
                    int index = 0;
                    for (const string &curr: joinedRelations.getScheme()) {
                        if (var == curr) {
                            cols.push_back(index);
                            break;
                        }
                        index++;
                    }
                }
                joinedRelations = joinedRelations.project(cols);
                vector<string> renameVars = database[ruleName].getScheme();
                joinedRelations = joinedRelations.rename(renameVars);

                unsigned beforeSize = database[ruleName].size();
                database[ruleName] = database[ruleName].unionRelation(joinedRelations);
                if (beforeSize != database[ruleName].size()) {
                    changed = true;
                }

                Relation relObject = database[ruleName];
            }
        }

        cout << "\nSchemes populated after " << relationStep << " passes through the Rules.\n" << endl;
    }

    void evalQueries() {
        cout << "Query Evaluation" << endl;
        vector<Predicate> queries = datalog.getQueries();
        for (const Predicate &q: queries) {
            string name = q.getName();
            Relation relObject = database[name];
            map<string, int> queryVars;
            vector<string> vars;
            vector<int> cols;

            int index = 0;
            for (const Parameter &p: q.getParams()) {
                if (p.isVar()) {
                    int dupIndex = duplicateQuery(p, queryVars);
                    if (dupIndex != -1) {
                        relObject = relObject.equalSelect(dupIndex, index);
                    } else {
                        queryVars[p.getValue()] = index;
                        vars.push_back(p.getValue());
                        cols.push_back(index);
                    }
                } else {
                    relObject = relObject.select(index, p.getValue());
                }
                index++;
            }

            relObject = relObject.project(cols);
            relObject = relObject.rename(vars);


            stringstream queryResult;
            queryResult << q.toString() << "?";
            if (relObject.empty()) {
                queryResult << " No";
            } else {
                queryResult << " Yes(" << relObject.size() << ")";
            }
            cout << queryResult.str() << endl;
            if (!relObject.empty()) {
                cout << relObject.toString();
            }
        }
    };

    /**@returns the index of a duplicate variable or -1 if no duplicate is found. */
    static int duplicateQuery(const Parameter &param, map<string, int> queryVars) {
        string value = param.getValue();
        if (queryVars.find(value) != queryVars.end()) {
            return queryVars[value];
        }
        return -1;
    }

    static Graph makeGraph(const vector<Rule>& rules) {
        Graph graph(rules.size());
        int fromRuleID = 0;
        for (const Rule& fromRule: rules) {
            for (const Predicate &fromPred: fromRule.getParams()) {
                string fromPredName = fromPred.getName();
                int toRuleID = 0;

                for (const Rule& toRule: rules) {
                    string toRuleName = toRule.getName();
                    if (fromPredName == toRuleName) {
                        graph.addEdge(fromRuleID, toRuleID);
                    }
                    toRuleID++;
                }
            }
            fromRuleID++;
        }
        return graph;

    }


};


#endif //PROJECT03_INTERPRETER_H
