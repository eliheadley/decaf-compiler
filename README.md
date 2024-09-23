# decaf-compiler

## Installation

1. **Unzip the repository:**
    ```sh
    cd decaf-compiler
    ```

2. **Install dependencies:**
    Ensure you have `cmake` and a C++ compiler installed on your system.

    - **Windows:**
        - Install [CMake](https://cmake.org/download/) and add it to your system PATH.
        - Install a C++ compiler like [MinGW](http://www.mingw.org/) or use Visual Studio's compiler.

    - **Linux:**
        ```sh
        sudo apt-get update
        sudo apt-get install cmake g++
        ```

    - **macOS:**
        ```sh
        brew install cmake
        xcode-select --install
        ```

3. **Build the project:**
    ```sh
    g++ -g -o main main.cpp
    or you can use cmake
    ```

## Running the Compiler

1. **Run the scanner:**
    ```sh
    ./main <source-file>
    ```

    Replace `<source-file>` with the path to the Decaf source file you want to compile.

## Example

1. **Compile a sample Decaf file:**
    ```sh
    ./main t1.decaf
    ```

2. **Check the output:**
    The scanner will generate the output based on the provided input files and print it to the terminal