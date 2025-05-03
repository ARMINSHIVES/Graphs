#include <iostream>
#include <string>
#include "Node.h"


template <typename K, typename U>
class Edge {
    public:
        Edge(Node<K>* start, Node<K>* end, U value){
            this->s = start;
            this->e = end;
            this->v = value;
        }
        Node<K>* getStartNode() const {
            return this->s;
        }
        Node<K>* getEndNode() const {
            return this->e;
        }
        U getValue() const {
            return this->v;
        }
        bool operator<(const Edge<K, U>& other) const {
            return this->v < other.v;
        }
        
    private:
        Node<K>* s;
        Node<K>* e;
        std::string name;
        U v;
};