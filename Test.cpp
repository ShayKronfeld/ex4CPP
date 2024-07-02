/*
shay kronfeld
322234782
kronfeldshay@gmail.com
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Node.hpp"
#include "tree.hpp"
#include "Complex.hpp"

TEST_CASE("Tree traversal with template int") {
    // Creating nodes with integer values
    Node<int> root_node(10);
    Tree<int> tree;
    tree.add_root(root_node);
    Node<int> n1(20);
    Node<int> n2(30);
    Node<int> n3(40);
    Node<int> n4(50);
    Node<int> n5(60);

    // Building the tree structure
    tree.add_child_node(root_node, n1); // Add n1 as a child of root_node
    tree.add_child_node(root_node, n2); // Add n2 as a child of root_node
    tree.add_child_node(n1, n3); // Add n3 as a child of n1
    tree.add_child_node(n1, n4); // Add n4 as a child of n1
    tree.add_child_node(n2, n5); // Add n5 as a child of n2

    // Pre-order traversal checks
    auto pre_order_it = tree.begin_pre_order(); // Create an iterator for pre-order traversal
    CHECK(pre_order_it->get_value() == 10); // Check the value of the current node
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == 20); // Check the value of the next node
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == 40);
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == 50);
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == 30);
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == 60);

    // Post-order traversal checks
    auto post_order_it = tree.begin_post_order(); // Create an iterator for post-order traversal
    CHECK(post_order_it->get_value() == 40);
    ++post_order_it;
    CHECK(post_order_it->get_value() == 50);
    ++post_order_it;
    CHECK(post_order_it->get_value() == 20);
    ++post_order_it;
    CHECK(post_order_it->get_value() == 60);
    ++post_order_it;
    CHECK(post_order_it->get_value() == 30);
    ++post_order_it;
    CHECK(post_order_it->get_value() == 10);

    // In-order traversal checks
    auto in_order_it = tree.begin_in_order(); // Create an iterator for in-order traversal
    CHECK(in_order_it->get_value() == 40);
    ++in_order_it;
    CHECK(in_order_it->get_value() == 20);
    ++in_order_it;
    CHECK(in_order_it->get_value() == 50);
    ++in_order_it;
    CHECK(in_order_it->get_value() == 10);
    ++in_order_it;
    CHECK(in_order_it->get_value() == 60);
    ++in_order_it;
    CHECK(in_order_it->get_value() == 30);

    // BFS traversal checks
    auto bfs_it = tree.begin_bfs_scan();
    CHECK(bfs_it->get_value() == 10);
    ++bfs_it;
    CHECK(bfs_it->get_value() == 20);
    ++bfs_it;
    CHECK(bfs_it->get_value() == 30);
    ++bfs_it;
    CHECK(bfs_it->get_value() == 40);
    ++bfs_it;
    CHECK(bfs_it->get_value() == 50);
    ++bfs_it;
    CHECK(bfs_it->get_value() == 60);
}

TEST_CASE("Tree traversal with template complex") {
    // Creating nodes with complex values
    Node<Complex> root_node(Complex(10.0, 10.0)); // Root node with complex value
    Tree<Complex> tree; // Create a tree with complex values
    tree.add_root(root_node); // Add the root node to the tree
    Node<Complex> n1(Complex(20.0, 30.0));
    Node<Complex> n2(Complex(30.0, 40.0));
    Node<Complex> n3(Complex(40.0, 50.0));
    Node<Complex> n4(Complex(50.0, 60.0));
    Node<Complex> n5(Complex(60.0, 70.0));

    // Building the tree structure
    tree.add_child_node(root_node, n1); // Add n1 as a child of root_node
    tree.add_child_node(root_node, n2); // Add n2 as a child of root_node
    tree.add_child_node(n1, n3); // Add n3 as a child of n1
    tree.add_child_node(n1, n4); // Add n4 as a child of n1
    tree.add_child_node(n2, n5); // Add n5 as a child of n2

    // Pre-order traversal checks
    auto pre_order_it = tree.begin_pre_order(); // Create an iterator for pre-order traversal
    CHECK(pre_order_it->get_value() == Complex(10.0, 10.0));
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == Complex(20.0, 30.0));
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == Complex(40.0, 50.0));
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == Complex(50.0, 60.0));
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == Complex(30.0, 40.0));
    ++pre_order_it;
    CHECK(pre_order_it->get_value() == Complex(60.0, 70.0));

    // Post-order traversal checks
    auto post_order_it = tree.begin_post_order(); // Create an iterator for post-order traversal
    CHECK(post_order_it->get_value() == Complex(40.0, 50.0));
    ++post_order_it;
    CHECK(post_order_it->get_value() == Complex(50.0, 60.0));
    ++post_order_it;
    CHECK(post_order_it->get_value() == Complex(20.0, 30.0));
    ++post_order_it;
    CHECK(post_order_it->get_value() == Complex(60.0, 70.0));
    ++post_order_it;
    CHECK(post_order_it->get_value() == Complex(30.0, 40.0));
    ++post_order_it;
    CHECK(post_order_it->get_value() == Complex(10.0, 10.0));

    // In-order traversal checks
    auto in_order_it = tree.begin_in_order(); // Create an iterator for in-order traversal
    CHECK(in_order_it->get_value() == Complex(40.0, 50.0));
    ++in_order_it;
    CHECK(in_order_it->get_value() == Complex(20.0, 30.0));
    ++in_order_it;
    CHECK(in_order_it->get_value() == Complex(50.0, 60.0));
    ++in_order_it;
    CHECK(in_order_it->get_value() == Complex(10.0, 10.0));
    ++in_order_it;
    CHECK(in_order_it->get_value() == Complex(60.0, 70.0));
    ++in_order_it;
    CHECK(in_order_it->get_value() == Complex(30.0, 40.0));

    // BFS traversal checks
    auto bfs_it = tree.begin_bfs_scan(); // Create an iterator for BFS traversal
    CHECK(bfs_it->get_value() == Complex(10.0, 10.0));
    ++bfs_it;
    CHECK(bfs_it->get_value() == Complex(20.0, 30.0));
    ++bfs_it;
    CHECK(bfs_it->get_value() == Complex(30.0, 40.0));
    ++bfs_it;
    CHECK(bfs_it->get_value() == Complex(40.0, 50.0));
    ++bfs_it;
    CHECK(bfs_it->get_value() == Complex(50.0, 60.0));
    ++bfs_it;
    CHECK(bfs_it->get_value() == Complex(60.0, 70.0));
}
