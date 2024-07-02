/*
shay kronfeld
322234782
kronfeldshay@gmail.com
*/

#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <iostream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include <map>
#include "Complex.hpp"
#include <sstream>
#include <iomanip>

#define NODE_RADIUS 25.f
#define VERTICAL_SPACING 80.f
#define INITIAL_HORIZONTAL_SPACING 200.f
#define FONT_PATH "font.ttf"

template <typename T> // template beacuse we want to use the same code for different types
class Tree {
private:
    Node<T>* root; // Root node of the tree
    size_t k; // Maximum number of children
// Compare this snippet from Node.hpp:
    static void flatten_to_vector(Node<T>* node, std::vector<Node<T>*> &result) {
        if (!node)
            return;
        result.push_back(node); // Add the current node to the result vector
        for (auto child : node->get_children()) {
            flatten_to_vector(child, result); // Recursively flatten children
        }
    }

// Compare this snippet from Test.cpp:
    void delete_tree(Node<T>* node) {
        if (!node)
            return;
        for (auto child : node->get_children()) {
            delete_tree(child); // Recursively delete children
        }
        delete node; // Delete the current node
        node = nullptr; // Set the node to null
    }

    // Find a node with a specific value in the tree
    Node<T>* find_node(Node<T>* current, const T& value) const {

        if (current->get_value() == value)
            return current; // Return the current node if its value matches

        for (auto child : current->get_children()) {
            if (child) {
                Node<T>* result = find_node(child, value); // Recursively search children   
               if (result)
                    return result; // Return the result if found in the subtree
            }
        }
        
        return nullptr; // Return null if not found in the subtree
    }

public:
    explicit Tree(size_t k = 2) : root(nullptr), k(k) {} // Constructor initializing the tree with a default arity (number of children) of 2

    ~Tree() {
        // Destructor: no dynamic memory to clean up
    }

    void add_root(Node<T>& node) {
        root = &node; // Assign the given node as the root of the tree
    }

    template <typename U>
    void add_child_node(Node<T>& parent, Node<U>& child) {
        throw std::runtime_error("Child node type does not match"); // Prevent adding a child node of a different type
    }


    void add_child_node(Node<T>& parent, Node<T>& child) {
        if (!root) {
            throw std::runtime_error("Root cannot be set."); // If the root is not set, throw an error
        }

        Node<T>* parentNode = find_node(root, parent.get_value()); // Find the parent node in the tree
        if (parentNode) {
            parentNode->add_child(&child); // Add the child node to the found parent node
        } else {
            throw std::runtime_error("Parent node not found."); // Throw an error if the parent node is not found
        }
    }

    // In-order iterator class for traversing the tree in in-order manner
    class in_order_iterator {

    private:
        std::stack<Node<T>*> nodes; // Stack to manage nodes during traversal
        size_t k; // Maximum number of children

        void push_left(Node<T>* node) {
            while (node != nullptr) {
                nodes.push(node);
                if (node->get_children().size() > 0)
                    node = node->get_children()[0]; // Continue pushing leftmost children
                else
                    break;
            }
        }
    

    public:
        explicit in_order_iterator(Node<T>* node, size_t k) : k(k) {
            
            if (node) {
                if (k == 2) {
                    push_left(node); // For binary trees, push the leftmost path
                } else {
                    nodes.push(node); // For general trees, start with the root node
                    while (!nodes.empty() && !nodes.top())
                        nodes.pop();
                }
            }
        }


        Node<T>& operator*() const {
            return *nodes.top(); // Dereference the current node
        }
    
        Node<T>* operator->() const {
            return nodes.top(); // Access the current node
        }

        bool operator!=(const in_order_iterator& other) const {
            return !nodes.empty() != !other.nodes.empty(); // Check if there are remaining nodes to visit
        }

        in_order_iterator& operator++() {
            if (nodes.empty()) return *this;

            if (k == 2) {
                Node<T>* node = nodes.top();                
                nodes.pop();
                if (node->get_children().size() > 1 && node->get_children()[1] != nullptr) {
                    push_left(node->get_children()[1]); // For binary trees, push the leftmost path for the right child
                }

            } else {
                Node<T>* current = nodes.top();
                nodes.pop();
                for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it) {
                    if (*it != nullptr)
                        nodes.push(*it); // Push children in reverse order for general trees
                }
            }
            return *this;
        }
    };

    in_order_iterator begin_in_order() const {
        return in_order_iterator(root, k); // Create an in-order iterator starting from the root
    }

    in_order_iterator end_in_order() const {
        return in_order_iterator(nullptr, k); // Create an in-order iterator indicating the end
    }

    // Pre-order iterator class for traversing the tree in pre-order manner
    class pre_order_iterator {
    private:
        std::stack<Node<T>*> nodes; // Stack to manage nodes during traversal
        size_t k; // Maximum number of children

    public:
        explicit pre_order_iterator(Node<T>* node, size_t k) : k(k) {
            if (node) nodes.push(node); // Start with the root node if it exists
        }

        Node<T>& operator*() const {
            return *nodes.top(); // Dereference the current node
        }

        Node<T>* operator->() const {
            return nodes.top(); // Access the current node
        }

        bool operator!=(const pre_order_iterator& other) const {
            return !nodes.empty() != !other.nodes.empty(); // Check if there are remaining nodes to visit
        }

        pre_order_iterator& operator++() {
            Node<T>* current = nodes.top();
            nodes.pop();
            for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it) {
                if (*it != nullptr) nodes.push(*it); // Push children in reverse order to the stack
            }
            return *this;
        }

    };

    pre_order_iterator begin_pre_order() const {
        return pre_order_iterator(root, k); // Create a pre-order iterator starting from the root
    }

    pre_order_iterator end_pre_order() const {
        return pre_order_iterator(nullptr, k); // Create a pre-order iterator indicating the end
    }

    // Post-order iterator class for traversing the tree in post-order manner
    class post_order_iterator {

    private:
    std::stack<Node<T>*> nodes; // Stack to manage nodes during traversal
    Node<T>* current; // Current node in the iteration
    size_t k; // Maximum number of children
    
    void pushLeftmostPath(Node<T>* node) {
        while (node) {
            nodes.push(node);
            if (!node->get_children().empty()) {
                node = node->get_children()[0]; // Push leftmost children in binary trees
            } else {
                break;
            }
        }
    }
    
    public:
        explicit post_order_iterator(Node<T>* node, size_t k) : current(nullptr), k(k) {
            if (node) {
                if (k == 2) {
                    pushLeftmostPath(node); // For binary trees, push the leftmost path
                } else {
                    nodes.push(node); // For general trees, start with the root node
                }
            }
            ++(*this); // Move to the first valid node
        }


        Node<T>& operator*() const {
            return *current; // Dereference the current node
        }

        Node<T>* operator->() const {
            return current; // Access the current node
        }
        
         bool operator!=(const post_order_iterator& other) const {
            return current != other.current; // Check if the iterators are different
        }


        post_order_iterator& operator++() {
            if (k == 2) {
                if (!nodes.empty()) {
                    Node<T>* node = nodes.top();
                    nodes.pop();
                    if (!nodes.empty()) {
                        Node<T>* parent = nodes.top();
                        if (parent->get_children().size() > 1 && node == parent->get_children()[0]) {
                            pushLeftmostPath(parent->get_children()[1]); // Push leftmost path for the right child in binary trees
                        }
                    }
                    current = node;
                } else {
                    current = nullptr; // End of iteration
                }
            } else {
                if (!nodes.empty()) {
                    Node<T>* node = nodes.top();
                    nodes.pop();
                    for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it) {
                        if (*it) {
                            nodes.push(*it); // Push children in reverse order for general trees
                        }
                    }
                    current = node;
                } else {
                    current = nullptr; // End of iteration
                }
            }
            return *this;
        }
    };

    post_order_iterator begin_post_order() const {
        return post_order_iterator(root, k); // Create a post-order iterator starting from the root
    }

    post_order_iterator end_post_order() const {
        return post_order_iterator(nullptr, k); // Create a post-order iterator indicating the end
    }

    // BFS (Breadth-First Search) iterator class for traversing the tree in level-order manner
    class bfs_iterator {
    private:
        std::queue<Node<T>*> nodes; // Queue to manage nodes during traversal
    
    public:
        explicit bfs_iterator(Node<T>* node) {
            if (node) nodes.push(node); // Start with the root node if it exists
        }

        Node<T>& operator*() const {
            return *nodes.front(); // Dereference the current node
        }

        Node<T>* operator->() const {
            return nodes.front(); // Access the current node
        }

        bool operator!=(const bfs_iterator& other) const {
            return !nodes.empty() != !other.nodes.empty(); // Check if there are remaining nodes to visit
        }

        bfs_iterator& operator++() {
            Node<T>* current = nodes.front();
            nodes.pop();
            for (const auto& child : current->get_children()) {
                if (child != nullptr)
                    nodes.push(child); // Push all children to the queue
            }
            return *this;
        }
    };

    bfs_iterator begin_bfs_scan() const {
        return bfs_iterator(root); // Create a BFS iterator starting from the root
    }

    bfs_iterator end_bfs_scan() const {
        return bfs_iterator(nullptr); // Create a BFS iterator indicating the end
    }

    // DFS (Depth-First Search) iterator class for traversing the tree in depth-first manner
    class dfs_iterator {
    private:
        std::stack<Node<T>*> nodes; // Stack to manage nodes during traversal
    public:
        explicit dfs_iterator(Node<T>* node) {
            if (node) nodes.push(node); // Start with the root node if it exists
        }

        Node<T>& operator*() const {
            return *nodes.top(); // Dereference the current node
        }

        Node<T>* operator->() const {
            return nodes.top(); // Access the current node
        }

        bool operator!=(const dfs_iterator& other) const {
            return !nodes.empty() != !other.nodes.empty(); // Check if there are remaining nodes to visit
        }

        dfs_iterator& operator++() {
            Node<T>* current = nodes.top();
            nodes.pop();
            for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it) {
                if (*it != nullptr)
                    nodes.push(*it); // Push children in reverse order
            }
            return *this;
        }
    };

    dfs_iterator begin_dfs_scan() const {
        return dfs_iterator(root); // Create a DFS iterator starting from the root
    }

    dfs_iterator end_dfs_scan() const {
        return dfs_iterator(nullptr); // Create a DFS iterator indicating the end
    }

    bfs_iterator begin() const {
        return bfs_iterator(root); // Default iterator is BFS starting from the root
    }

    bfs_iterator end() const {
        return bfs_iterator(nullptr); // Default iterator indicating the end
    }

    // Heap iterator class for traversing the tree in heap-order manner (only for binary trees)
    class heap_iterator {
    private:
        struct CompareNodes {
            bool operator()(Node<T>* a, Node<T>* b) {
                return a->get_value() > b->get_value(); // Compare nodes by value for heap ordering
            }
        };

        void collect_nodes(Node<T>* node) {
            if (node) {
                heap_nodes.push_back(node); // Collect the current node
                for (auto child : node->get_children()) {
                    collect_nodes(child); // Recursively collect children nodes
                }
            }
        }

        std::vector<Node<T>*> heap_nodes; // Vector to store heap nodes
        size_t k; // Maximum number of children

    public:
        explicit heap_iterator(Node<T>* node, size_t k) : k(k) {
            if (k != 2) {
                throw std::runtime_error("Cannot create heap iterator for non-binary tree"); // Error if the tree is not binary
            }
            if (node) {
                collect_nodes(node); // Collect all nodes for heap
                std::make_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes()); // Create a heap
            }
        }

        Node<T>& operator*() const {
            return *heap_nodes.front(); // Dereference the current node in the heap
        }

        Node<T>* operator->() const {
            return heap_nodes.front(); // Access the current node in the heap
        }

        bool operator!=(const heap_iterator& other) const {
            return !heap_nodes.empty() != !other.heap_nodes.empty(); // Check if heap is not empty
        }

        heap_iterator& operator++() {
            if (!heap_nodes.empty()) {
                std::pop_heap(heap_nodes.begin(), heap_nodes.end(), CompareNodes()); // Remove the front node
                heap_nodes.pop_back();
            }
            return *this;
        }
    };

    heap_iterator myHeap() const {
        return heap_iterator(root, k); // Create a heap iterator starting from the root
    }

    heap_iterator end_heap() const {
        return heap_iterator(nullptr, k); // Create a heap iterator indicating the end
    }

friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
    if (!tree.root)
        return os; // If the tree is empty, return

    // Create SFML window for visualization
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Tree Visualization");
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Error loading font\n";
        return os; // Error message if font file cannot be loaded
    }

    const float node_radius = 25.f; // Radius of each node circle
    const float vertical_spacing = 80.f; // Vertical spacing between nodes
    const float initial_horizontal_spacing = 200.f; // Initial horizontal spacing for root node

    std::map<Node<T>*, sf::Vector2f> positions; // Map to store positions of nodes

    // Function to recursively position nodes based on tree structure
    std::function<void(Node<T>*, float, float, float)> position_nodes = [&](Node<T>* node, float x, float y, float horizontal_spacing) {
        if (!node)
            return;

        positions[node] = sf::Vector2f(x, y); // Store position of current node

        float child_x_offset = x - (node->get_children().size() - 1) * horizontal_spacing / 2.f;

        // Position each child node recursively
        for (size_t i = 0; i < node->get_children().size(); ++i) {
            Node<T>* child = node->get_children()[i];
            if (child) {
                position_nodes(child, child_x_offset + i * horizontal_spacing, y + vertical_spacing, horizontal_spacing / 2.f);
            }
        }
    };

    // Start positioning nodes from the root
    position_nodes(tree.root, window.getSize().x / 2.f, node_radius + 50.f, initial_horizontal_spacing);

    // SFML main loop for drawing
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White); // Clear window with white color

        // Draw nodes and connections
        for (const auto& pair : positions) {
            Node<T>* node = pair.first;
            sf::Vector2f position = pair.second;

            // Draw circle for node
            sf::CircleShape circle(node_radius);
            circle.setFillColor(sf::Color::Yellow);
            circle.setPosition(position - sf::Vector2f(node_radius, node_radius));
            window.draw(circle);

            // Draw text inside node circle
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);

            std::ostringstream oss;
            oss << node->get_value();
            text.setString(oss.str());

            sf::FloatRect text_bounds = text.getLocalBounds();
            text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
            text.setPosition(position);
            window.draw(text);

            // Draw lines connecting parent and child nodes
            for (Node<T>* child : node->get_children()) {
                if (child) {
                    sf::Vector2f child_position = positions[child];

                    sf::Vertex line[] = {
                        sf::Vertex(position, sf::Color::Black),
                        sf::Vertex(child_position, sf::Color::Black)
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        window.display(); // Display drawn elements
    }
    return os;
}

};

#endif // TREE_HPP
