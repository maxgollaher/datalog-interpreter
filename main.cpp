#include <iostream>
#include <fstream>
#include <vector>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Interpreter.h"
#include "Node.h"
#include "Graph.h"

using namespace std;


//int main(int argc, char *argv[]) {
//    if (argc != 2) return -1;
//    ifstream in(argv[1]);       // create input file stream
//    stringstream fileStream;
//    fileStream << in.rdbuf();
//    string line = fileStream.str();
//
//
//    int totalTokens = 0;
//    auto s = Scanner(line);     // create scanner for the file
//    Token t = Token();
//    vector<Token> tokens;
//    do {
//        // create token for each token in line
//        t = s.scanToken();
//        if (t.getType() != COMMENT) tokens.push_back(t);  // skip comments
//        totalTokens++;
//    } while (!line.empty());
//
//    // if no EOF token created, create one
//    if (t.getType() == UNDEFINED || line.empty()) {
//        t = Token(END, "", s.getLine());
//        tokens.push_back(t);
//        totalTokens++;
//    }
//
//    Parser p = Parser(tokens);
//    p.datalogProgram();
//
//
//    in.close();
//
//    return 0;
//}

int main() {

    // predicate names for fake rules
    // first is name for head predicate
    // second is names for body predicates
    pair<string,vector<string>> ruleNames[] = {
            { "A", { "B", "C" } },
            { "B", { "A", "D" } },
            { "B", { "B" } },
            { "E", { "F", "G" } },
            { "E", { "E", "F" } },
    };

    vector<Rule> rules;

    for (auto& rulePair : ruleNames) {
        string headName = rulePair.first;
        Rule rule = Rule(Predicate(headName));
        vector<string> bodyNames = rulePair.second;
        for (auto& bodyName : bodyNames)
            rule.addBodyPredicate(Predicate(bodyName));
        rules.push_back(rule);
    }

    Graph graph = Interpreter::makeGraph(rules);
    cout << graph.toString();

}