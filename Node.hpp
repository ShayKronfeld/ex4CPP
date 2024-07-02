/*
shay kronfeld
322234782
kronfeldshay@gmail.com
*/

#pragma once
#include <vector>

template <typename T>
class Node {
private:
    T value;
    std::vector<Node<T>*> children;

public:
    Node(const T& val) : value(val) {} // Constructor

    void set_value(const T& val) {
        value = val;
    }

    const T& get_value() const {
        return value;
    }

    const std::vector<Node<T>*>& get_children() const { // Get the children of the node
        return children;
    }

     void add_child(Node<T>* child) { // Add a child to the node
        children.push_back(child);
    }
};