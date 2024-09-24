# decaf-compiler

## Installation

1. **Unzip the repository:**
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
    g++ -g -o main scanner.cpp
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
    ./main test/t1.decaf
    ```

2. **Check the output:**
    The scanner will generate the output based on the provided input files and print it to the terminal

## Contributing

1. **Fork the repository:**
    Click the "Fork" button on the top right of the repository page.

2. **Create a new branch:**
    ```sh
    git checkout -b feature-branch
    ```

3. **Make your changes and commit them:**
    ```sh
    git commit -am 'Add new feature'
    ```

4. **Push to the branch:**
    ```sh
    git push origin feature-branch
    ```

5. **Create a pull request:**
    Open a pull request from your forked repository on GitHub.

## License

This project is licensed under the MIT License - see the LICENSE file for details.