#include <iostream>
#include "Node.h"

template <typename T>
class LinkedList {
    public:
        LinkedList() {
            head = nullptr;
            size = 0;
        }
        LinkedList(T v) {
            head = new Node<T>(v);
            size = 1;
        }
        ~LinkedList() {
            Node<T>* current = head;
            while (current != nullptr) {
                Node<T>* next = current->getNext();
                delete current;
                current = next;
            }
        }
        void append(T val) {
            Node<T>* current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(val);
            size++;
        }
        bool remove(T val) {
            if (!head) return false;
            if (head->getVal() == val) {
                Node<T>* temp = head;
                head = head->getNext();
                delete temp;
                size--;
                return true;
            }
            Node<T>* current = head;
            while (current->getNext() != nullptr && current->getNext()->getVal() != val) {
                current = current->getNext();
            }
            if (current->getNext()) {
                return false;
            }
            Node<T>* temp = current->getNext();
            current->setNext(temp->getNext());
            delete temp;
            size--;
            return true;
        }
        int removeAll(T val) {
            int removedCount = 0;
            while (head && head->getVal() == val) {
                Node<T>* temp = head;
                head = head->getNext();
                delete temp;
                size--;
                removedCount++;
            }
            Node<T>* current = head;
            while (current && current->getNext()) {
                if (current->getNext()->getVal() == val) {
                    Node<T>* temp = current->getNext();
                    current->setNext(temp->getNext());
                    delete temp;
                    size--;
                    removedCount++;
                } else {
                    current = current->getNext();
                }
            }
            return removedCount;
        }
        int getSize() const {
            return size;
        }
        Node<T>* getHead() const {
            return this->head;
        }
        friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& LL) {
            Node<T>* current = LL.getHead();
            while (current != nullptr) {
                os << current->getVal() << " ";
                current = current->getNext();
            }
            return os;
        }
    private:
        Node<T>* head;
        int size;
};
