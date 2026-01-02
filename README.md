# Pyramid Data Structure (C++)

This project implements a custom Pyramid data structure in C++,
where each row is represented as a singly linked list.

## Features
- Dynamic pyramid creation
- Row-wise traversal
- Column-wise traversal
- Priority-based printing (row + column)
- Search with index and priority output
- Node deletion and insertion
- Proper pyramid structure validation

## Data Structure Design
- Each row is a linked list
- Rows are stored in a dynamic array
- Priority is calculated as: row index + column index

## Concepts Used
- Linked Lists
- Dynamic Memory Allocation
- Pointer Manipulation
- Traversal Algorithms
- C++ Structs and Functions

## How to Run
Compile with a standard C++ compiler:
```bash
g++ pyramid.cpp -o pyramid
./pyramid
