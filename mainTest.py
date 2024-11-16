import ply.lex as lex
from parse_tree import TreeNode
import ply.yacc as yacc

# Token definitions
tokens = (
    'T_Int', 'T_Void', 'T_String', 'T_Bool',
    'T_If', 'T_Else', 'T_For', 'T_Return', 'T_Print',
    'T_Assign', 'T_Plus', 'T_Minus', 'T_Multiply', 'T_Divide',
    'T_Less', 'T_LessEqual', 'T_Greater', 'T_GreaterEqual',
    'T_Equal', 'T_NotEqual', 'T_LogicalAnd', 'T_LogicalOr', 'T_Not',
    'T_LParen', 'T_RParen', 'T_LBrace', 'T_RBrace', 'T_Comma', 'T_Semicolon',
    'T_Identifier', 'T_IntConstant', 'T_StringConstant', 'T_BoolConstant'
)

reserved = {
    'int': 'T_Int',
    'void': 'T_Void',
    'string': 'T_String',
    'bool': 'T_Bool',
    'if': 'T_If',
    'else': 'T_Else',
    'for': 'T_For',
    'return': 'T_Return',
    'Print': 'T_Print',
}

# Token regexes
t_T_Assign = r'='
t_T_Plus = r'\+'
t_T_Minus = r'-'
t_T_Multiply = r'\*'
t_T_Divide = r'/'
t_T_Less = r'<'
t_T_LessEqual = r'<='
t_T_Greater = r'>'
t_T_GreaterEqual = r'>='
t_T_Equal = r'=='
t_T_NotEqual = r'!='
t_T_LogicalAnd = r'&&'
t_T_LogicalOr = r'\|\|'
t_T_Not = r'!'
t_T_LParen = r'\('
t_T_RParen = r'\)'
t_T_LBrace = r'\{'
t_T_RBrace = r'\}'
t_T_Comma = r','
t_T_Semicolon = r';'

def t_T_Identifier(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = reserved.get(t.value, 'T_Identifier')
    return t

def t_T_IntConstant(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_T_StringConstant(t):
    r'"[^"]*"'
    t.value = t.value[1:-1]
    return t

def t_T_BoolConstant(t):
    r'true|false'
    t.value = (t.value == 'true')
    return t

t_ignore = ' \t'

def t_comment(t):
    r'//.*'
    pass

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

def t_error(t):
    print(f"Illegal character '{t.value[0]}'")
    t.lexer.skip(1)

lexer = lex.lex()

# Operator precedence
precedence = (
    ('left', 'T_LogicalOr'),
    ('left', 'T_LogicalAnd'),
    ('left', 'T_Equal', 'T_NotEqual'),
    ('left', 'T_Less', 'T_LessEqual', 'T_Greater', 'T_GreaterEqual'),
    ('left', 'T_Plus', 'T_Minus'),
    ('left', 'T_Multiply', 'T_Divide'),
)

# Grammar rules
def p_program(p):
    '''program : functions
            | varDecl functions
            | varDecl varDecl functions'''
    #p[0] = TreeNode('Program', children=p[1])

#def p_initVars(p):
 #   '''initVars : initVar initVar
  #                       | initVar
   #                      | epsilon'''
    #if len(p) == 2:
        #p[0] = [p[1]]
#def p_initVar(p):
 #   '''initVar : varDecl '''


def p_varDecl(p):
    '''varDecl : type T_Identifier T_Semicolon'''
   # p[0] = (p[1],p[2],p[3])


def p_functions(p):
    '''functions : functionDec functions
        | epsilon'''
    #p[0] = TreeNode('VarDecl', attributes={'Type': p[1], 'Identifier': p[2]})

def p_functionDec(p):
    '''functionDec : type T_Identifier T_LParen Args T_LBrace Statements T_RBrace'''
    #p[0] = TreeNode('FnDecl', attributes={'Type': p[1], 'Identifier': p[2]}, children=[p[4], p[6]])

def p_type(p):
    '''type : T_Void
            | T_Int
            | T_String
            | T_Bool'''

def p_Args(p):
    '''Args : Arg T_Comma Arg T_RParen
              | Arg T_RParen
              | T_RParen'''
    #p[0] = TreeNode('Formals', children=p[1])

def p_Arg(p):
    '''Arg : type T_Identifier'''
    #if len(p) == 3:
        #p[0] = [TreeNode('VarDecl', attributes={'Type': p[1], 'Identifier': p[2]})]
    #else:
        #p[0] = p[1]
        #p[0].append(TreeNode('VarDecl', attributes={'Type': p[3], 'Identifier': p[4]}))


#def p_ArgType(p):
   # '''ArgType : T_Int
     #       | T_Bool'''
    #p[0] = TreeNode('StmtBlock', children=p[2])

def p_Statements(p):
    '''Statements : VarDec Statements
             | Statement'''
    #if len(p) == 2:
        #p[0] = [p[1]]
   # else:
        #p[0] = p[1]
        #p[0].append(p[2])
def p_VarDec(p):
    '''VarDec : type T_Identifier T_Semicolon'''
    #p[0] = (p[1],p[2],p[3])

#def p_VarType(p):
    #'''VarType : T_Int
            #| T_String'''
    #p[0] = p[1]
def p_Statement(p):
    '''Statement : IfStatement Statement
            | ReturnStatement Statement
            | VarAssign Statement
            | FuncCall T_Semicolon Statement
            | ForStatement Statement
            | ElseStatement Statement
            | PrintStatement Statement
            | epsilon'''
    p[0] = p[1]

def p_IfStatement(p):
    '''IfStatement : T_If T_LParen expr_list T_RParen'''
    #p[0] = p[1]
def p_ElseStatement(p):
    '''ElseStatement : T_Else'''
    #p[0] = p[1]
def p_ReturnStatemnt(p):
    '''ReturnStatement : T_Return ReturnValues T_Semicolon'''
    #p[0] = TreeNode('ReturnStmt', children=[p[2]])

def p_ReturnValues(p):
    '''ReturnValues : T_Identifier T_Plus T_IntConstant
            | T_IntConstant
            | T_Identifier T_Multiply FuncCall
            | T_Identifier T_Plus T_Identifier'''

def p_VarAssign(p):
    '''VarAssign : T_Identifier T_Assign AssignExpr T_Semicolon'''

def p_AssignExpr(p):
    '''AssignExpr : T_StringConstant
            | FuncCall
            | T_IntConstant
            | T_Identifier T_Divide T_IntConstant'''

def p_PrintStatement(p):
    '''PrintStatement : T_Print T_LParen expr_list T_RParen T_Semicolon'''
    #p[0] = TreeNode('PrintStmt', children=p[3])


def p_FuncCall(p):
    '''FuncCall : T_Identifier T_LParen expr_list T_RParen'''
    #p[0] = TreeNode('Call', attributes={'Identifier': p[1]}, children=p[3])

def p_ForStatement(p):
    '''ForStatement : T_For T_LParen T_Identifier T_Assign T_IntConstant T_Semicolon T_Identifier T_LessEqual T_IntConstant T_Semicolon T_Identifier T_Assign T_Identifier T_Plus T_IntConstant T_RParen'''

def p_expr_list(p):
    '''expr_list : expr
                 | expr_list T_Comma expr'''
    #if len(p) == 2:
        #p[0] = [p[1]]
    #else:
        #p[0] = p[1]
        #p[0].append(p[3])

def p_expr(p):
    '''expr : T_IntConstant
            | T_StringConstant
            | T_BoolConstant
            | T_Identifier
            | FuncCall
            | expr T_Plus expr
            | expr T_Minus expr
            | expr T_Multiply expr
            | expr T_Divide expr
            | expr T_Less expr
            | expr T_LessEqual expr
            | expr T_Greater expr
            | expr T_GreaterEqual expr
            | expr T_Equal expr
            | expr T_NotEqual expr
            | expr T_LogicalAnd expr
            | T_Not expr
            | T_LParen expr T_RParen'''
    #if len(p) == 2:
        #p[0] = TreeNode('FieldAccess', attributes={'Identifier': p[1]})
    #elif len(p) == 4:
        #[0] = TreeNode('ArithmeticExpr', children=[p[1], TreeNode('Operator', attributes={'Value': p[2]}), p[3]])
    #else:
        #p[0] = p[2]
def p_epsilon(p):
    '''epsilon :'''
def p_empty(p):
    '''empty :'''
    #p[0] = []

def p_error(p):
    if p:
        print(f"Syntax error at token {p.type} (value={p.value}) at line {p.lineno}")
    else:
        print("Syntax error at EOF")

# Build the parser
parser = yacc.yacc()

if __name__ == "__main__":
    filename = 't1.decaf'
    with open(filename, 'r') as f:
        data = f.read()

    lexer.input(data)
    for token in lexer:
        print(token)

    result = parser.parse(data, debug=True, tracking=True)

    if result:
        print(result)
