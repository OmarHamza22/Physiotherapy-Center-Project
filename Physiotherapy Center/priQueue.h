#pragma once
#include "priNode.h"
#include <iostream>
using namespace std;

template <typename T>
class priQueue
{
    priNode<T>* head;
    int size = 0;

public:
    priQueue() : head(nullptr) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p));
    }

    // Insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {
            newNode->setNext(head);
            head = newNode;
            size++;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        size++;
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        size--;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;
        int dummy;
        topEntry = head->getItem(dummy);
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int getSize() const { return size; }


    // Corrected member function to print the queue
    
    void printQueue() const {
        priNode<T>* current = head;
        while (current != nullptr) {
            int dummyPriority;  // Temporary variable to hold the priority
            current->getItem(dummyPriority)->print();  // Call print() on the item

            if (current->getNext() != nullptr)
                cout << ",";  // Print a comma if there's another node

            current = current->getNext();
        }
    }
};
