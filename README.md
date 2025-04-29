# Serial - Binary file serialization library
[![License: MIT](https://img.shields.io/badge/License-MIT-lightgrey.svg)](https://opensource.org/licenses/MIT)

Serial is a lightweight C++ library for binary file serialization. It allows for reading and writing binary files in a portable format, commonly used for file saving, network protocols, and other binary data handling tasks.

## Features
- Binary file reading and writing with `IBinaryFile` and `OBinaryFile` classes
- Serialization of primitive types (integers, floats, booleans, characters)
- Serialization support for standard C++ containers:
    - `std::string`
    - `std::vector<T>`
    - `std::array<T, N>`
    - `std::map<K, V>`
- Big-endian serialization format for cross-platform compatibility
- FIFO data storage ordering
- Custom struct serialization through operator overloading
- Built-in test suite using GoogleTest

## Requirements
- C++17 compatible compiler
- CMake 3.10 or higher
- GoogleTest (included)

## Build Instructions
1. Clone the repository
    ```bash
    git clone https://github.com/charlottekruzic/cpp-serialization-library.git
    ```
2. Create build directory
    ```bash
    mkdir build && cd build
    ```
3. Configure and build
    ```bash
    cmake ..
    make
    ```
## Run tests
The Serial library includes a test suite with 94 tests across 21 suites. When all tests pass, you should see output similar to :
```bash
[----------] Global test environment tear-down
[==========] 94 tests from 21 test suites ran. (8 ms total)
[  PASSED  ] 94 tests.
```
To run the tests:
```bash
./testSerial
```

## API Reference
### OBinaryFile
Write binary data to files:
```cpp
// Construct
OBinaryFile(const std::string &filename, Mode mode = Truncate);

// Write
std::size_t write(const std::byte *data, std::size_t size);
```

### IBinaryFile
Read binary data from files:
```cpp
// Construct
IBinaryFile(const std::string &filename);

// Read
std::size_t read(std::byte *data, std::size_t size);
```

### Serialization Operators
The library provides overloaded operators for various types:
```cpp
// Write operators
OBinaryFile& operator<<(OBinaryFile& file, T value);

// Read operators
IBinaryFile& operator>>(IBinaryFile& file, T& value);
```

Where `T` can be: integer types, floating point types, character type, boolean type, std::string, container types (vector, array, map), or custom structures with appropriate operator overloads.

## Project assignment
For more information about the purpose of this project, you can find the [complete project assignment file](./resources/project-assignment-fr.pdf) (in french) within this repository. This project is part of the third-year Bachelor's degree in Computer Science at the University of Franche-Comté.
