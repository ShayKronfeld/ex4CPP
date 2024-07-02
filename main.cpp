/*
shay kronfeld
322234782
kronfeldshay@gmail.com
*/

#include <iostream>
#include <string>
#include "Node.hpp"
#include "tree.hpp"
#include "Complex.hpp"

using namespace std;

int main() {
    // Example with double values
    Node<double> root_node(5.5); // Creating the root node with a double value
    Tree<double> tree; // Binary tree that contains doubles
    tree.add_root(root_node); // Adding the root node to the tree
    Node<double> n1(6.1); // Creating child nodes with different double values
    Node<double> n2(7.2);
    Node<double> n3(8.3);
    Node<double> n4(9.4);
    Node<double> n5(10.5);

    tree.add_child_node(root_node, n1); // Adding n1 as a child of the root node
    tree.add_child_node(root_node, n2); // Adding n2 as a child of the root node
    tree.add_child_node(n1, n3); // Adding n3 as a child of n1
    tree.add_child_node(n1, n4); // Adding n4 as a child of n1
    tree.add_child_node(n2, n5); // Adding n5 as a child of n2

    // The tree should look like:
    /**
     *       root = 5.5
     *     /       \
     *    6.1      7.2
     *   /  \      /
     *  8.3  9.4  10.5
     */

    cout << "Pre-order traversal (double):" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_value() << endl;
    } // prints: 5.5, 6.1, 8.3, 9.4, 7.2, 10.5

    cout << "Post-order traversal (double):" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_value() << endl;
    } // prints: 8.3, 9.4, 6.1, 10.5, 7.2, 5.5

    cout << "In-order traversal (double):" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_value() << endl;
    } // prints: 8.3, 6.1, 9.4, 5.5, 10.5, 7.2

    cout << "BFS traversal (double):" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << endl;
    } // prints: 5.5, 6.1, 7.2, 8.3, 9.4, 10.5

    cout << "Range-based for loop (BFS traversal, double):" << endl;
    for (auto node : tree) {
        cout << node.get_value() << endl;
    } // same as BFS: 5.5, 6.1, 7.2, 8.3, 9.4, 10.5

    // Tree output using operator<<
    cout << "Tree output using operator<< (double):" << endl;
    cout << tree; // Should print the tree using the GUI

    Tree<double> three_ary_tree(3); // 3-ary tree
    three_ary_tree.add_root(root_node); // Adding the root node to the 3-ary tree
    three_ary_tree.add_child_node(root_node, n1); // Adding child nodes to the root node
    three_ary_tree.add_child_node(root_node, n2);
    three_ary_tree.add_child_node(root_node, n3);
    three_ary_tree.add_child_node(n1, n4);
    three_ary_tree.add_child_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 5.5
     *     /      |     \
     *    6.1    7.2    8.3
     *   /        |
     *  9.4      10.5
     */

    cout << "Three-ary tree output (double):" << endl;
    cout << three_ary_tree; // Should print the 3-ary tree using the GUI

    // Example with Complex values
    Node<Complex> complex_root_node(Complex(2.0, 3.0)); // Creating the root node with Complex value
    Tree<Complex> complex_tree; // Binary tree that contains Complex numbers
    complex_tree.add_root(complex_root_node); // Adding the root node to the tree
    Node<Complex> cn1(Complex(4.0, 5.0)); // Creating child nodes with different Complex values
    Node<Complex> cn2(Complex(6.0, 7.0));
    Node<Complex> cn3(Complex(8.0, 9.0));
    Node<Complex> cn4(Complex(10.0, 11.0));
    Node<Complex> cn5(Complex(12.0, 13.0));

    complex_tree.add_child_node(complex_root_node, cn1); // Adding cn1 as a child of the root node
    complex_tree.add_child_node(complex_root_node, cn2); // Adding cn2 as a child of the root node
    complex_tree.add_child_node(cn1, cn3); // Adding cn3 as a child of cn1
    complex_tree.add_child_node(cn1, cn4); // Adding cn4 as a child of cn1
    complex_tree.add_child_node(cn2, cn5); // Adding cn5 as a child of cn2

    cout << "Pre-order traversal (Complex):" << endl;
    for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node) {
        cout << node->get_value() << endl;
    } // prints: (2.0, 3.0), (4.0, 5.0), (8.0, 9.0), (10.0, 11.0), (6.0, 7.0), (12.0, 13.0)

    cout << "Post-order traversal (Complex):" << endl;
    for (auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node) {
        cout << node->get_value() << endl;
    } // prints: (8.0, 9.0), (10.0, 11.0), (4.0, 5.0), (12.0, 13.0), (6.0, 7.0), (2.0, 3.0)

    cout << "In-order traversal (Complex):" << endl;
    for (auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node) {
        cout << node->get_value() << endl;
    } // prints: (8.0, 9.0), (4.0, 5.0), (10.0, 11.0), (2.0, 3.0), (12.0, 13.0), (6.0, 7.0)

    cout << "BFS traversal (Complex):" << endl;
    for (auto node = complex_tree.begin_bfs_scan(); node != complex_tree.end_bfs_scan(); ++node) {
        cout << node->get_value() << endl;
    } // prints: (2.0, 3.0), (4.0, 5.0), (6.0, 7.0), (8.0, 9.0), (10.0, 11.0), (12.0, 13.0)

    cout << "Range-based for loop (BFS traversal, Complex):" << endl;
    for (auto node : complex_tree) {
        cout << node.get_value() << endl;
    } // same as BFS: (2.0, 3.0), (4.0, 5.0), (6.0, 7.0), (8.0, 9.0), (10.0, 11.0), (12.0, 13.0)

    // Tree output using operator<<
    cout << "Tree output using operator<< (Complex):" << endl;
    cout << complex_tree; // Should print the tree using the GUI

    Tree<Complex> three_ary_complex_tree(3); // 3-ary tree
    three_ary_complex_tree.add_root(complex_root_node); // Adding the root node to the 3-ary tree
    three_ary_complex_tree.add_child_node(complex_root_node, cn1); // Adding child nodes to the root node
    three_ary_complex_tree.add_child_node(complex_root_node, cn2);
    three_ary_complex_tree.add_child_node(complex_root_node, cn3);
    three_ary_complex_tree.add_child_node(cn1, cn4);
    three_ary_complex_tree.add_child_node(cn2, cn5);

    cout << "Three-ary tree output (Complex):" << endl;
    cout << three_ary_complex_tree; // Should print the 3-ary tree using the GUI

    return 0;
}
