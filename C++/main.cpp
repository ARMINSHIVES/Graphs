#include <iostream>
#include "Graph.h"


int main(){
    Graph<std::string, int> a;
    a.addEdge("A", "B", 1);
    a.addNode("C");
    std::cout << a <<std::endl;

    return 1;
}