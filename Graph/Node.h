#ifndef PROJECT03_NODE_H
#define PROJECT03_NODE_H

#include <string>
#include <set>
#include <sstream>
using namespace std;

class Node {
private:
    set<int> adjacentNodeIDs;
    bool visited;
    int postOrderNum;

public:
    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    bool empty() const { return adjacentNodeIDs.empty(); };

    [[nodiscard]] string toString() const {
        stringstream resultStream;
        for (const int& i: adjacentNodeIDs) {
            resultStream << "R" << i << ",";
        }
        string result = resultStream.str();
        if (!result.empty()) {
            result.pop_back();
        }
        return result;
    };

};

#endif //PROJECT03_NODE_H
