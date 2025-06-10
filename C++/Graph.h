#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <climits>
#include "Node.h"
#include "Edge.h"
#include "LinkedList.h"

template <typename K, typename U>
// Directed Graph
class Graph {
    public:
        Graph(){
        }
        
        ~Graph(){
            typename std::map<K, Node<K>*>::iterator node_it = this->Nodes.begin();
            while(node_it != this->Nodes.end()){
                delete node_it->second;
                node_it++;
            }
        }

        bool addNode(K node_val){
            if (this->Nodes.find(node_val) == this->Nodes.end()) {
                Node<K>* start_node = new Node<K>(node_val);
                this->Nodes[node_val] = start_node;
                this->Edges[start_node] = {};
                return true;
            }
            return false;
        }

        bool addEdge(K start_node_val, K end_node_val, U edge_val) {
            Node<K>* start_node;
            Node<K>* end_node;
            if (this->Nodes.find(start_node_val) == this->Nodes.end()) {
                start_node = new Node<K>(start_node_val);
                this->Nodes[start_node_val] = start_node;
            } else {
                start_node = this->Nodes[start_node_val];
            }
            if (this->Nodes.find(end_node_val) == this->Nodes.end()) {
                end_node = new Node<K>(end_node_val);
                this->Nodes[end_node_val] = end_node;
            } else {
                end_node = this->Nodes[end_node_val];
            }
            Edge<K, U> newEdge(start_node, end_node, edge_val);
            this->Edges[start_node].push_back(newEdge);
            return true;
        }

        bool hasNode(K val){
            return this->Nodes.find(val) != this->Nodes.end();
        }

        std::vector<Edge<K, U>> shortestPath(K start, K end){
            std::vector<Edge<K, U>> path;
            if (this->Nodes.find(start) == this->Nodes.end() || this->Nodes.find(end) == this->Nodes.end()) {
                return path;
            }
            std::map<Node<K>*, U> distances;
            std::map<Node<K>*, Node<K>*> previous;
            std::map<Node<K>*, bool> visited;
            for (auto& node_pair : this->Nodes) {
                distances[node_pair.second] = INT_MAX;
                previous[node_pair.second] = nullptr;
                visited[node_pair.second] = false;
            }
            distances[this->Nodes[start]] = 0;
            Node<K>* current_node = this->Nodes[start];
            while (current_node != nullptr) {
                visited[current_node] = true;
                for (const auto& edge : this->Edges[current_node]) {
                    Node<K>* neighbor = edge.getEndNode();
                    if (!visited[neighbor]) {
                        U new_distance = distances[current_node] + edge.getValue();
                        if (new_distance < distances[neighbor]) {
                            distances[neighbor] = new_distance;
                            previous[neighbor] = current_node;
                        }
                    }
                }
                current_node = nullptr;
                U min_distance = INT_MAX;
                for (const auto& node_pair : this->Nodes) {
                    if (!visited[node_pair.second] && distances[node_pair.second] < min_distance) {
                        min_distance = distances[node_pair.second];
                        current_node = node_pair.second;
                    }
                }
            }
            current_node = this->Nodes[end];
            while (current_node != nullptr) {
                Node<K>* prev_node = previous[current_node];
                if (prev_node != nullptr) {
                    for (const auto& edge : this->Edges[prev_node]) {
                        if (edge.getEndNode() == current_node) {
                            path.push_back(edge);
                            break;
                        }
                    }
                }
                current_node = prev_node;
            }

            int i = 0;
            int j = path.size() - 1;
            while (i < j) {

                Edge<K, U> temp = path[i];
                path[i] = path[j];
                path[j] = temp;
                i++;
                j--;
            }
            return path;
        }
        friend std::ostream& operator<<(std::ostream& os, const Graph<K, U>& g) {
            typename std::map<Node<K>*, std::vector<Edge<K, U>>>::const_iterator  edge_it = g.Edges.begin();
            while(edge_it != g.Edges.end()){
                os << edge_it->first->getVal() << " [";
                for(size_t i = 0; i < edge_it->second.size(); i++){
                    os << "("<<edge_it->second[i].getEndNode()->getVal() << ", " << edge_it->second[i].getValue() << ")";
                    if(i < edge_it->second.size() - 1){
                        os << ", ";
                    }
                }
                os << "]\n";
                edge_it++;
            }
            return os;
        }
    
    private:
        std::map<K, Node<K>*> Nodes;
        std::map<Node<K>*, std::vector<Edge<K, U>>> Edges;
};
