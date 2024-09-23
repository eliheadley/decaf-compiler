# decaf-compiler

## Installation

1. **Clone the repository:**
    ```sh
    git clone https://github.com/yourusername/decaf-compiler.git
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
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

## Running the Compiler

1. **Run the compiler:**
    ```sh
    ./decaf-compiler <source-file>
    ```

    Replace `<source-file>` with the path to the Decaf source file you want to compile.

## Example

1. **Compile a sample Decaf file:**
    ```sh
    ./decaf-compiler ../examples/sample.decaf
    ```

2. **Check the output:**
    The compiler will generate the output based on the provided input files t1.decaf, t3.decaf, and t4.decaf