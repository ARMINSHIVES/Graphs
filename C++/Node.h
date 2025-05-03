#pragma once
#include <iostream>
#include <string>

template <typename T>
class Node {
public:
    Node(T v, std::string identifier = "") : Val(v), next(nullptr), id(identifier) {}
    Node(T v, Node<T>* n, std::string identifier = "") : Val(v), next(n), id(identifier) {}

    virtual ~Node() {
        // Optional recursive deletion:
        // delete next;
    }

    T getVal() const {
        return Val;
    }

    std::string getId() const {
        return id;
    }

    Node<T>* getNext() const {
        return next;
    }

    bool setVal(T val) {
        Val = val;
        return true;
    }

    bool setId(const std::string& identifier) {
        id = identifier;
        return true;
    }

    bool setNext(T val, std::string identifier = "") {
        Node<T>* n = new Node<T>(val, identifier);
        next = n;
        return true;
    }

    bool setNext(Node<T>* n) {
        next = n;
        return true;
    }

    bool operator==(const Node<T>& other) const{
        return this->id == other.getID() && this->Val == other.getVal();
    }
    bool operator<(const Node<T>& other) const {
        return this->id < other.getID() || this->Val < other.getVal();
    }

    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
        os << "[ID: " << node.id << ", Val: " << node.Val << "]";
        return os;
    }

protected:
    T Val;
    Node<T>* next;
    std::string id;
};


template <typename T>
class multiNode : public Node<T> {
public:
    multiNode(T v, std::string identifier = "") 
        : Node<T>(v, identifier) {
        this->max_size = 10;
        this->children = new multiNode<T>*[this->max_size];
        this->num_children = 0;
        for (int i = 0; i < this->max_size; ++i) {
            this->children[i] = nullptr;
        }
    }

    ~multiNode() override {
        for (int i = 0; i < max_size; ++i) {
            delete children[i];
        }
        delete[] children;
    }

    bool addNode(T val, int i, std::string identifier = "") {
        if (i < 0) return false;

        if (i >= max_size) {
            int new_size = max_size * 2;
            multiNode<T>** newChildren = new multiNode<T>*[new_size];
            for (int j = 0; j < max_size; ++j)
                newChildren[j] = children[j];
            for (int j = max_size; j < new_size; ++j)
                newChildren[j] = nullptr;
            delete[] children;
            children = newChildren;
            max_size = new_size;
        }

        if (children[i] == nullptr) {
            children[i] = new multiNode<T>(val, identifier);
            return true;
        }
        return false;
    }

private:
    multiNode<T>** children;
    int max_size;
    int num_children;
};
