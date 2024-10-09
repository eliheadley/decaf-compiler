import java.util.*;

enum TokenType {
    T_AND,
    T_ASSIGN,
    T_BOOLTYPE,
    T_BREAK,
    T_CHARCONSTANT,
    T_COMMA,
    T_COMMENT,
    T_CONTINUE,
    T_DIV,
    T_DOT,
    T_ELSE,
    T_EQ,
    T_EXTERN,
    T_FALSE,
    T_FOR,
    T_FUNC,
    T_GEQ,
    T_GT,
    T_ID,
    T_IF,
    T_INTCONSTANT,
    T_INTTYPE,
    T_LCB,
    T_LEFTSHIFT,
    T_LEQ,
    T_LPAREN,
    T_LSB,
    T_LT,
    T_MINUS,
    T_MOD,
    T_MULT,
    T_NEQ,
    T_NOT,
    T_NULL,
    T_OR,
    T_PACKAGE,
    T_PLUS,
    T_RCB,
    T_RETURN,
    T_RIGHTSHIFT,
    T_RPAREN,
    T_RSB,
    T_SEMICOLON,
    T_STRINGCONSTANT,
    T_STRINGTYPE,
    T_TRUE,
    T_VAR,
    T_VOID,
    T_WHILE,
    T_WHITESPACE,
    Unknown
}

class Token {
    TokenType type;
    String value;
    int line;
    int col;

    Token(TokenType type, String value, int line, int col) {
        this.type = type;
        this.value = value;
        this.line = line;
        this.col = col;
    }
}

public class LexicalAnalyzer {
    private String input;
    private int position;
    private int lineNum;
    private int lastLinePos;
    private List<Token> tokens;
    private Map<String, TokenType> keywords;
    private Map<String, TokenType> operators;
    private Map<String, TokenType> punctuation;

    public LexicalAnalyzer(String source) {
        this.input = source;
        this.position = 0;
        this.lineNum = 1;
        this.lastLinePos = 0;
        this.tokens = new ArrayList<>();
        this.keywords = new HashMap<>();
        this.operators = new HashMap<>();
        this.punctuation = new HashMap<>();
        initKeywords();
        initOperators();
        initPunctuation();
    }

    private void initKeywords() {
        keywords.put("bool", TokenType.T_BOOLTYPE);
        keywords.put("break", TokenType.T_BREAK);
        keywords.put("continue", TokenType.T_CONTINUE);
        keywords.put("else", TokenType.T_ELSE);
        keywords.put("extern", TokenType.T_EXTERN);
        keywords.put("false", TokenType.T_FALSE);
        keywords.put("for", TokenType.T_FOR);
        keywords.put("func", TokenType.T_FUNC);
        keywords.put("if", TokenType.T_IF);
        keywords.put("int", TokenType.T_INTTYPE);
        keywords.put("null", TokenType.T_NULL);
        keywords.put("package", TokenType.T_PACKAGE);
        keywords.put("return", TokenType.T_RETURN);
        keywords.put("string", TokenType.T_STRINGTYPE);
        keywords.put("true", TokenType.T_TRUE);
    }

    private void initOperators() {
        operators.put("!", TokenType.T_NOT);
        operators.put("||", TokenType.T_OR);
        operators.put("+", TokenType.T_PLUS);
        operators.put("-", TokenType.T_MINUS);
        operators.put("*", TokenType.T_MULT);
        operators.put("/", TokenType.T_DIV);
        operators.put("%", TokenType.T_MOD);
        operators.put("<<", TokenType.T_LEFTSHIFT);
        operators.put(">>", TokenType.T_RIGHTSHIFT);
    }

    private void initPunctuation() {
        punctuation.put(",", TokenType.T_COMMA);
        punctuation.put(".", TokenType.T_DOT);
        punctuation.put(";", TokenType.T_SEMICOLON);
        punctuation.put("{", TokenType.T_LCB);
        punctuation.put("}", TokenType.T_RCB);
        punctuation.put("(", TokenType.T_LPAREN);
        punctuation.put(")", TokenType.T_RPAREN);
        punctuation.put("[", TokenType.T_LSB);
        punctuation.put("]", TokenType.T_RSB);
    }

    public void tokenize() {
        while (position < input.length()) {
            char currentChar = input.charAt(position);
            if (isWhiteSpace(currentChar)) {
                position++;
            } else if (isLetter(currentChar)) {
                String word = getNextWord();
                TokenType type = keywords.containsKey(word) ? keywords.get(word) : TokenType.T_ID;
                tokens.add(new Token(type, word, lineNum, lastLinePos));
            } else if (isDigit(currentChar)) {
                String number = getNextWord();
                tokens.add(new Token(TokenType.T_INTCONSTANT, number, lineNum, lastLinePos));
            } else if (isPunctuation(currentChar)) {
                String punct = String.valueOf(currentChar);
                tokens.add(new Token(punctuation.get(punct), punct, lineNum, lastLinePos));
                position++;
            } else if (isOperator(currentChar)) {
                String op = String.valueOf(currentChar);
                tokens.add(new Token(operators.get(op), op, lineNum, lastLinePos));
                position++;
            } else {
                position++;
            }
        }
    }

    public void printTokens() {
        for (Token token : tokens) {
            System.out.println("Token: " + getType(token.type) + ", Value: " + token.value
                    + ", Line: " + token.line + ", Column: " + token.col);
        }
    }

    private boolean isWhiteSpace(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    private boolean isLetter(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    private boolean isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    private boolean isPunctuation(char c) {
        return punctuation.containsKey(String.valueOf(c));
    }

    private boolean isOperator(char c) {
        return operators.containsKey(String.valueOf(c));
    }

    private String getNextWord() {
        StringBuilder word = new StringBuilder();
        while (position < input.length() && (isLetter(input.charAt(position)) || isDigit(input.charAt(position)))) {
            word.append(input.charAt(position));
            position++;
        }
        return word.toString();
    }

    private String getType(TokenType type) {
        switch (type) {
            case T_AND: return "&&";
            case T_ASSIGN: return "=";
            case T_BOOLTYPE: return "bool";
            case T_BREAK: return "break";
            case T_CHARCONSTANT: return "char_lit";
            case T_COMMA: return ",";
            case T_COMMENT: return "comment";
            case T_CONTINUE: return "continue";
            case T_DIV: return "/";
            case T_DOT: return ".";
            case T_ELSE: return "T_Else";
            case T_EQ: return "==";
            case T_EXTERN: return "extern";
            case T_FALSE: return "false";
            case T_FOR: return "for";
            case T_FUNC: return "func";
            case T_GEQ: return ">=";
            case T_GT: return ">";
            case T_ID: return "identifier";
            case T_IF: return "T_If";
            case T_INTCONSTANT: return "T_IntConstant";
            case T_INTTYPE: return "int";
            case T_LCB: return "{";
            case T_LEFTSHIFT: return "<<";
            case T_LEQ: return "<=";
            case T_LPAREN: return "(";
            case T_LSB: return "[";
            case T_LT: return "<";
            case T_MINUS: return "-";
            case T_MOD: return "%";
            case T_MULT: return "*";
            case T_NEQ: return "!=";
            case T_NOT: return "!";
            case T_NULL: return "null";
            case T_OR: return "||";
            case T_PACKAGE: return "package";
            case T_PLUS: return "+";
            case T_RCB: return "}";
            case T_RETURN: return "T_Return";
            case T_RIGHTSHIFT: return ">>";
            case T_RPAREN: return ")";
            case T_RSB: return "]";
            case T_SEMICOLON: return ";";
            case T_STRINGCONSTANT: return "T_STRINGCONSTANT";
            case T_STRINGTYPE: return "string";
            case T_TRUE: return "true";
            case T_VAR: return "var";
            case T_VOID: return "T_Void";
            case T_WHILE: return "while";
            case T_WHITESPACE: return "whitespace";
            case Unknown: return "Unknown";
            default: return "Invalid TokenType";
        }
    }
}