import ply.lex as lex
import sys

# List of Reserved words
reserved = {
    'bool' : 'T_Boolean',
    'break' : 'T_Break',
    'continue' : 'T_Continue',
    'else' : 'T_Else',
    'extern': 'T_Extern',
    'false' : 'T_BoolConstantF',
    'for' : 't_For',
    'func' : 'T_Func',
    'if' : 'T_If',
    'int' : 'T_Int',
    'null' : 'T_Null',
    'package' : 'T_Package',
    'return' : 'T_Return',
    'string' : 'T_String',
    'true' : 'T_BoolConstantT',
    'var' : 'T_Var',
    'void' : 'T_Void',
    'while' : 'T_While',
    'Print' : 'T_Print'
}

# List of Tokens
tokens = [
   'T_IntConstant',
    'T_IDENTIFIER',
    'T_LessEqual',
    'T_GreaterEqual',
    'T_LogicalAnd',
    'T_LogicalOr',
    'T_LeftShift',
    'T_RightShift',
    'T_AssignEqual',
    'T_NotEqual',
    'T_StringConstant',

] + list(reserved.values())


#Rule declarations for simple tokens

t_T_NotEqual = r'\!\='
t_T_AssignEqual = r'\=\='
t_T_RightShift = r'\>\>'
t_T_LeftShift = r'\<\<'
t_T_LogicalAnd = r'\&\&'
t_T_LogicalOr = r'\|\|'
t_T_LessEqual = r'\<\='
t_T_GreaterEqual = r'\>\='
T_carriage_return = r'\r+'
T_horizontal_tab  = r'\t+'
T_vertical_tab    =r'\v+'
T_form_feed       =r'\f'
T_space           =r' '



# A string containing ignored characters (spaces and tabs)
t_ignore  = ' \t'

#Expression Rules
def t_T_IntConstant(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_T_StringConstant(t):
    r'"[^"]*"'
    return t

# Define a rule so we can track line numbers
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

def find_column(input, token):
    line_start = input.rfind('\n', 0, token.lexpos) + 1
    return (token.lexpos - line_start) + 1

def t_T_IDENTIFIER(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    if t.value in reserved:
        t.type = reserved[t.value]  # set the token type to the reserved word's type
    else:
        t.type = 'T_IDENTIFIER'  # set the token type to 'ID' if it's a valid ID
    return t
#List of literals
literals = [
    '{',
    '}',
    '[',
    ']',
    ',',
    ';',
    '(',
    ')',
    '=',
    '-',
    '!',
    '+',
    '*',
    '/',
    '<',
    '>',
    '%',
    '.'
]


# Error handling rule
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


# Build the lexer
lexer = lex.lex()

#findType function for formatting
def findType(tok):
    if tok.type == "T_IntConstant" or tok.type == "T_StringConstant":
        tok.type = tok.type + " (value= " + str(tok.value) + ")"
    if tok.type == "T_BoolConstantF":
        tok.type = "T_BoolConstant (value= false)"
    if tok.type == "T_BoolConstantT":
        tok.type = "T_BoolConstant (value= true)"
    if tok.type in literals:
        tok.type = "'" + str(tok.value) + "'"
    return tok.type


#main method to take in inputfile, read input file, tokenize, and output
if __name__ == "__main__":
    filename = sys.argv[1]
    f = open(filename, "r")
    data = f.read()
    lexer.input(data)
    while True:
        tok = lexer.token()
        if not tok:
            break
        columnStart = find_column(data,tok)
        tokLength = len(str(tok.value))-1
        print(tok.value, '    line', tok.lineno, 'Cols ', columnStart,"-",columnStart+tokLength, ' is ', findType(tok), "")