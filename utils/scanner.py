import re

class TokenType:
    T_AND = '&&'
    T_ASSIGN = '='
    T_BOOLTYPE = 'bool'
    T_BREAK = 'break'
    T_CHARCONSTANT = 'char_lit'
    T_COMMA = ','
    T_COMMENT = 'comment'
    T_CONTINUE = 'continue'
    T_DIV = '/'
    T_DOT = '.'
    T_ELSE = 'T_Else'
    T_EQ = '=='
    T_EXTERN = 'extern'
    T_FALSE = 'false'
    T_FOR = 'for'
    T_FUNC = 'func'
    T_GEQ = '>='
    T_GT = '>'
    T_ID = 'identifier'
    T_IF = 'T_If'
    T_INTCONSTANT = 'T_IntConstant'
    T_INTTYPE = 'int'
    T_LCB = '{'
    T_LEFTSHIFT = '<<'
    T_LEQ = '<='
    T_LPAREN = '('
    T_LSB = '['
    T_LT = '<'
    T_MINUS = '-'
    T_MOD = '%'
    T_MULT = '*'
    T_NEQ = '!='
    T_NOT = '!'
    T_NULL = 'null'
    T_OR = '||'
    T_PACKAGE = 'package'
    T_PLUS = '+'
    T_RCB = '}'
    T_RETURN = 'T_Return'
    T_RIGHTSHIFT = '>>'
    T_RPAREN = ')'
    T_RSB = ']'
    T_SEMICOLON = ';'
    T_STRINGCONSTANT = 'T_STRINGCONSTANT'
    T_STRINGTYPE = 'string'
    T_TRUE = 'true'
    T_VAR = 'var'
    T_VOID = 'T_Void'
    T_WHILE = 'while'
    T_WHITESPACE = 'whitespace'
    Unknown = 'Unknown'

class Token:
    def __init__(self, type, value, line, col_start, col_end):
        self.type = type
        self.value = value
        self.line = line
        self.col_start = col_start
        self.col_end = col_end

class LexicalAnalyzer:
    def __init__(self, source):
        self.input = source
        self.position = 0
        self.line_num = 1
        self.last_line_pos = 0
        self.tokens = []
        self.keywords = {}
        self.operators = {}
        self.punctuation = {}
        self.init_keywords()
        self.init_operators()
        self.init_punctuation()

    def init_keywords(self):
        self.keywords = {
            "bool": TokenType.T_BOOLTYPE,
            "break": TokenType.T_BREAK,
            "continue": TokenType.T_CONTINUE,
            "else": TokenType.T_ELSE,
            "extern": TokenType.T_EXTERN,
            "false": TokenType.T_FALSE,
            "for": TokenType.T_FOR,
            "func": TokenType.T_FUNC,
            "if": TokenType.T_IF,
            "int": TokenType.T_INTTYPE,
            "null": TokenType.T_NULL,
            "package": TokenType.T_PACKAGE,
            "return": TokenType.T_RETURN,
            "string": TokenType.T_STRINGTYPE,
            "true": TokenType.T_TRUE,
            "var": TokenType.T_VAR,
            "void": TokenType.T_VOID,
            "while": TokenType.T_WHILE
        }

    def init_operators(self):
        self.operators = {
            "&&": TokenType.T_AND,
            "=": TokenType.T_ASSIGN,
            "==": TokenType.T_EQ,
            ">=": TokenType.T_GEQ,
            ">": TokenType.T_GT,
            "<=": TokenType.T_LEQ,
            "<": TokenType.T_LT,
            "!=": TokenType.T_NEQ,
            "!": TokenType.T_NOT,
            "||": TokenType.T_OR,
            "+": TokenType.T_PLUS,
            "-": TokenType.T_MINUS,
            "*": TokenType.T_MULT,
            "/": TokenType.T_DIV,
            "%": TokenType.T_MOD,
            "<<": TokenType.T_LEFTSHIFT,
            ">>": TokenType.T_RIGHTSHIFT
        }

    def init_punctuation(self):
        self.punctuation = {
            ",": TokenType.T_COMMA,
            ".": TokenType.T_DOT,
            ";": TokenType.T_SEMICOLON,
            "{": TokenType.T_LCB,
            "}": TokenType.T_RCB,
            "(": TokenType.T_LPAREN,
            ")": TokenType.T_RPAREN,
            "[": TokenType.T_LSB,
            "]": TokenType.T_RSB
        }

    def remove_comments(self):
        # Remove single-line comments
        self.input = re.sub(r'//.*', '', self.input)
        # Remove multi-line comments
        self.input = re.sub(r'/\*.*?\*/', '', self.input, flags=re.DOTALL)

    def tokenize(self):
        self.remove_comments()
        while self.position < len(self.input):
            current_char = self.input[self.position]
            if self.is_white_space(current_char):
                if current_char == '\n':
                    self.line_num += 1
                    self.last_line_pos = 0
                self.position += 1
                self.last_line_pos += 1
            elif self.is_letter(current_char):
                start_col = self.last_line_pos
                word = self.get_next_word()
                token_type = self.keywords.get(word, TokenType.T_ID)
                self.tokens.append(Token(token_type, word, self.line_num, start_col, start_col + len(word) - 1))
                self.last_line_pos += len(word)
            elif self.is_digit(current_char):
                start_col = self.last_line_pos
                number = self.get_next_word()
                self.tokens.append(Token(TokenType.T_INTCONSTANT, number, self.line_num, start_col, start_col + len(number) - 1))
                self.last_line_pos += len(number)
            elif self.is_punctuation(current_char):
                start_col = self.last_line_pos
                punct = current_char
                self.tokens.append(Token(self.punctuation[punct], punct, self.line_num, start_col, start_col))
                self.position += 1
                self.last_line_pos += 1
            elif self.is_operator(current_char):
                start_col = self.last_line_pos
                op = current_char
                self.tokens.append(Token(self.operators[op], op, self.line_num, start_col, start_col))
                self.position += 1
                self.last_line_pos += 1
            else:
                self.position += 1
                self.last_line_pos += 1

    def print_tokens(self):
        for token in self.tokens:
            print(f"{token.value}\tline {token.line} Cols {token.col_start}-{token.col_end} is {self.get_type(token.type)}")

    def is_white_space(self, c):
        return c in [' ', '\n', '\r', '\t', '\f']

    def is_letter(self, c):
        return 'a' <= c <= 'z' or 'A' <= c <= 'Z'

    def is_digit(self, c):
        return '0' <= c <= '9'

    def is_punctuation(self, c):
        return c in self.punctuation

    def is_operator(self, c):
        return c in self.operators

    def get_next_word(self):
        start = self.position
        while self.position < len(self.input) and (self.is_letter(self.input[self.position]) or self.is_digit(self.input[self.position])):
            self.position += 1
        return self.input[start:self.position]

    def get_type(self, type):
        return {
            TokenType.T_AND: "T_AND",
            TokenType.T_ASSIGN: "T_ASSIGN",
            TokenType.T_BOOLTYPE: "T_BOOLTYPE",
            TokenType.T_BREAK: "T_BREAK",
            TokenType.T_CHARCONSTANT: "T_CHARCONSTANT",
            TokenType.T_COMMA: "T_COMMA",
            TokenType.T_COMMENT: "T_COMMENT",
            TokenType.T_CONTINUE: "T_CONTINUE",
            TokenType.T_DIV: "T_DIV",
            TokenType.T_DOT: "T_DOT",
            TokenType.T_ELSE: "T_ELSE",
            TokenType.T_EQ: "T_EQ",
            TokenType.T_EXTERN: "T_EXTERN",
            TokenType.T_FALSE: "T_FALSE",
            TokenType.T_FOR: "T_FOR",
            TokenType.T_FUNC: "T_FUNC",
            TokenType.T_GEQ: "T_GEQ",
            TokenType.T_GT: "T_GT",
            TokenType.T_ID: "T_ID",
            TokenType.T_IF: "T_IF",
            TokenType.T_INTCONSTANT: "T_INTCONSTANT",
            TokenType.T_INTTYPE: "T_INTTYPE",
            TokenType.T_LCB: "T_LCB",
            TokenType.T_LEFTSHIFT: "T_LEFTSHIFT",
            TokenType.T_LEQ: "T_LEQ",
            TokenType.T_LPAREN: "T_LPAREN",
            TokenType.T_LSB: "T_LSB",
            TokenType.T_LT: "T_LT",
            TokenType.T_MINUS: "T_MINUS",
            TokenType.T_MOD: "T_MOD",
            TokenType.T_MULT: "T_MULT",
            TokenType.T_NEQ: "T_NEQ",
            TokenType.T_NOT: "T_NOT",
            TokenType.T_NULL: "T_NULL",
            TokenType.T_OR: "T_OR",
            TokenType.T_PACKAGE: "T_PACKAGE",
            TokenType.T_PLUS: "T_PLUS",
            TokenType.T_RCB: "T_RCB",
            TokenType.T_RETURN: "T_RETURN",
            TokenType.T_RIGHTSHIFT: "T_RIGHTSHIFT",
            TokenType.T_RPAREN: "T_RPAREN",
            TokenType.T_RSB: "T_RSB",
            TokenType.T_SEMICOLON: "T_SEMICOLON",
            TokenType.T_STRINGCONSTANT: "T_STRINGCONSTANT",
            TokenType.T_STRINGTYPE: "T_STRINGTYPE",
            TokenType.T_TRUE: "T_TRUE",
            TokenType.T_VAR: "T_VAR",
            TokenType.T_VOID: "T_VOID",
            TokenType.T_WHILE: "T_WHILE",
            TokenType.T_WHITESPACE: "T_WHITESPACE",
            TokenType.Unknown: "Unknown"
        }.get(type, "Invalid TokenType")