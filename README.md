# decaf-interpter

## Installation

1. **Clone the repository:**
    ```sh
    git clone https://github.com/eliheadley/decaf-interpreter.git
    cd decaf-interpreter
    ```

2. **Set up a virtual environment:**
    ```sh
    python -m venv venv
    source venv/bin/activate  # On Windows use `venv\Scripts\activate`
    ```

3. **Install dependencies:**
    ```sh
    pip install -r requirements.txt
    ```

## Running the Compiler

1. **Run the scanner:**
    ```sh
    python main.py <source-file>
    ```

    Replace `<source-file>` with the path to the Decaf source file you want to run.

## Example

1. **run a sample Decaf file:**
    ```sh
    python main.py test/t1.decaf
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