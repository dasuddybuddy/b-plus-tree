## B+ Tree
This project is a B+ Tree implementation in C++20

## Instructions
Run code with gcc:
```bash
g++ -std=c++20 src/main.cpp -o main
./main
```

Run code with clang:
```bash
clang++ -std=c++20 src/main.cpp -o main
./main
```

Run code with MSVC:
```bash
cl /EHsc src/main.cpp
```

Read doxygen docs:
```bash
open docs/html/index.html
```

## Project Structure

### `include/`
Contains B+ Tree class definitions and declarations. Also contains B+ Tree Node structure.

### `implementation/`
Contains implementation for all methods in B+ Tree class.

### `src/`
Contains terminal program allowing you to insert, remove, search, query values (int only so far) and
print tree

### `tests/`
Unit tests
