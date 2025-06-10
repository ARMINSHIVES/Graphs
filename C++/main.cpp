#include <iostream>
#include <vector>
#include "Graph.h"


int main(){
    Graph<std::string, int> a;
    a.addEdge("A", "B", 1);
    a.addEdge("A", "C", 2);


    a.addEdge("B", "C", 2);


    a.addEdge("C", "D", 1);
    a.addEdge("C", "E", 4);


    a.addEdge("D", "E", 1);
    a.addEdge("D", "F", 2);

    a.addEdge("E", "F", 1);

    std::vector<Edge<std::string, int>> path = a.shortestPath("A", "F");
    if (path.size() == 0) {
        std::cout << "No path found" << std::endl;
    } else {
        for (size_t i = 0; i < path.size(); i++) {
            std::cout << path[i].getStartNode()->getVal() << " -> " << path[i].getEndNode()->getVal() << " (" << path[i].getValue() << ")\n";
        }
        std::cout << std::endl;
    }

    return 1;
}