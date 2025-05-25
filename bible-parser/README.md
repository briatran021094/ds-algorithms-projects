# Bible Tree Parser

**Status: In Progress**

This project is a C++ implementation that parses Bible verses and organizes them into a hierarchical tree structure consisting of:

- Books  
- Chapters  
- Verses  

Each node in the tree represents a different level of this hierarchy.

## Features (In Progress)

- Parse Bible data from structured input
- Construct a tree where:
  - Root: Bible
  - Children: Books
  - Grandchildren: Chapters
  - Great-grandchildren: Verses
- Tree traversal algorithms:
  - Inorder
  - Preorder
  - Postorder

## Goals

- [x] Implement tree-based parsing logic  
- [x] Support for multiple traversal strategies  
- [ ] Export data to clean JSON format  
- [ ] Add support for searching and filtering by book/chapter/verse  
