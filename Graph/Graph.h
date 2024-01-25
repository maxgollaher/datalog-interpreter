#ifndef PROJECT03_GRAPH_H
#define PROJECT03_GRAPH_H

#include <map>
#include "Node.h"

using namespace std;

class Graph {
private:
    map<int,Node> nodes;

public:
    explicit Graph(size_t size) {
        for (int nodeID = 0; nodeID < (int) size; nodeID++)
            nodes[nodeID] = Node();
    }

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    [[nodiscard]] string toString() {
        stringstream result;
        for (auto& pair: nodes) {
            int nodeID = pair.first;
            Node node = pair.second;
            string nodeList = node.toString();
            result << "R" << nodeID << ":" << nodeList << endl;
        }
        return result.str();
    }
};

#endif //PROJECT03_GRAPH_H
