# ex4CPP

# Tree Traversal and Operations Project

## Overview

This project implements a templated tree data structure in C++ with various traversal methods and operations. The tree can handle different data types such as `int`, `double`, and user-defined types like `Complex`. The project includes traversal methods such as pre-order, post-order, in-order, and breadth-first search (BFS). Additionally, the tree supports different arities (binary, ternary, etc.) and provides an operator for graphical output using a GUI library.

## Structure

The project is organized into several files:

- **Node.hpp**: Defines the `Node` class template, representing individual nodes in the tree.
- **Tree.hpp**: Defines the `Tree` class template, representing the tree structure and traversal methods.
- **Complex.hpp**: Defines the `Complex` class to handle complex numbers.
- **main.cpp**: Contains examples and tests demonstrating the usage of the tree with different data types and traversals.
- **CMakeLists.txt**: CMake configuration for building the project.
- **README.md**: Detailed documentation of the project.

## Features

### Tree Class

- **Templated Design**: The `Tree` class template allows creating trees of various data types.
- **Traversal Methods**: Supports pre-order, post-order, in-order, and BFS traversals.
- **Arity Support**: The tree can be configured to support different arities, such as binary and ternary trees.
- **Graphical Output**: Provides an operator for graphical output using a GUI library.

### Node Class

- **Templated Design**: The `Node` class template allows creating nodes of various data types.
- **Value Storage**: Each node stores a value of the specified type.
- **Child Management**: Methods to add and manage child nodes.

### Complex Class

- **Complex Numbers**: Represents complex numbers with real and imaginary parts.
- **Operator Overloading**: Provides overloaded operators for arithmetic operations and comparisons.

### Example Code

Examples demonstrating the usage of the `Tree`, `Node`, and `Complex` classes are provided in `main.cpp`. The examples cover:

- Creating and manipulating trees with different data types.
- Performing various traversals and printing the results.
- Using the graphical output operator to visualize the tree.

### Testing

The project uses the Doctest framework for testing. To run the tests:

## Dependencies

- **C++ Standard Library**: Used for standard data structures and algorithms.
- **Doctest**: For unit testing.
- **CMake**: For building the project.
- **GUI Library**: For graphical output (e.g., Qt or SFML).
