# ADT List Implementations

This repository includes my implementations of various Abstract Data Type (ADT) List structures, completed as part of a CSC 2431 Data Structures course assignment. Specifically, the project showcases:

- A **Double Linked List** implementation
- A **Sorted Double Linked List** (derived from the above)
- A **Variable-Size Array List**

Although the scope of this repository is limited to these three implementations (as required by the assignment), they effectively demonstrate my understanding of dynamic memory management, pointer operations, and data structure design in C++. These implementations were designed to integrate with a provided test suite and passed all unit and memory leak tests successfully.

---

## Learning Objectives

- Practice implementing ADT Lists using:
  - **Dynamic Arrays** that grow as needed
  - **Double Linked Lists** with full CRUD operations
  - **Sorted Linked Lists** that maintain ascending order automatically

---

## 🗂Project Structure

| File | Description |
|------|-------------|
| `dlinkedlist.cpp` | 🛠 Your implementation of the `DoubleLinkedList` class |
| `sorted_double_linked_list.cpp` | 🛠 Your implementation of the `SortedDoubleLinkedList` class |
| `vsarray.cpp` | 🛠 Your implementation of the variable-size array list |
| `test.cpp` | Contains the unit test cases (do not modify) |
| `makefile` | Provided for building the project |
| `*.h` and other `*.cpp` files | Base classes (Comparable, Object, Person, etc.), **do not modify** |
