import os
from utils.scanner import LexicalAnalyzer

def read_file(file_name):
    try:
        with open(file_name, 'r') as file:
            return file.read()
    except IOError:
        print(f"Error opening \"{file_name}\"")
        return ""

def main():
    file_name = "test/t1.decaf"
    src_code = read_file(file_name)

    lexer = LexicalAnalyzer(src_code)
    lexer.tokenize()
    lexer.print_tokens()

if __name__ == "__main__":
    main()