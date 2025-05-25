# Polynomial Class

This repository includes my full implementation of a `Polynomial` class as part of a school assignment for CSC2431 (Data Structures II). The class demonstrates use of dynamic memory and the implementation of various operations on polynomials, including addition, subtraction, multiplication, evaluation, derivation, and more.

> Note: This project was assigned in class and is included here only to show my ability to implement all parts of it. It is not intended as a standalone project. It complements the main list-related ADT projects I focused on this quarter.

## What This Code Shows

Even though this was a structured school assignment, this implementation shows that I can:
- Work with dynamic memory (using `new` and `delete[]`)
- Overload operators and create utility functions
- Translate math formulas into functional C++ code
- Handle complexity, such as polynomial division and integration (extra credit)

I kept this code clean, followed good naming conventions, and used pseudocode + debugging with TAs to ensure it worked fully.

## Features Implemented

| Method | Description |
|--------|-------------|
| `Polynomial(size_t degree)` | Basic constructor |
| `Polynomial(size_t degree, const float* coefficients)` | Constructor with coefficients |
| `Polynomial(const Polynomial& other)` | Deep-copy constructor |
| `~Polynomial()` | Destructor with memory cleanup |
| `Sum`, `Subtract`, `Minus` | Math operations |
| `Multiply`, `Divide`, `Derive`, `Evaluate`, `Integrate` | Extended math operations |
| `operator=`, `ToString`, `Equals` | Utilities and printing |
| `Read`, `Write` | Stream input/output |
