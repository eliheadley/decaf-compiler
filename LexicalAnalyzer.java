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
    int end;

    Token(TokenType type, String value, int line, int col, int end) {
        this.type = type;
        this.value = value;
        this.line = line;
        this.col = col;
        this.end = end;
    }
}

public class LexicalAnalyzer {
    private String input;
    private int position;
    private int lineNum;
    private int lastLinePos;
    private int col;
    private int curToken;
    private List<Token> tokens;
    private Map<String, TokenType> keywords;
    private Map<String, TokenType> operators;
    private Map<String, TokenType> punctuation;

    public LexicalAnalyzer(String source) {
        this.input = source;
        this.position = 0;
        this.lineNum = 1;
        this.lastLinePos = 0;
        this.col = 0;
        this.curToken = 0;
        this.tokens = new ArrayList<>();
        this.keywords = new HashMap<>();
        this.operators = new HashMap<>();
        this.punctuation = new HashMap<>();
        initKeywords();
        initOperators();
        initPunctuation();
        tokenize();
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
        keywords.put("var", TokenType.T_VAR);
        keywords.put("void", TokenType.T_VOID);
        keywords.put("while", TokenType.T_WHILE);
    }

    private void initOperators() {
        operators.put("&&", TokenType.T_AND);
        operators.put("=", TokenType.T_ASSIGN);
        operators.put("==", TokenType.T_EQ);
        operators.put(">=", TokenType.T_GEQ);
        operators.put(">", TokenType.T_GT);
        operators.put("<=", TokenType.T_LEQ);
        operators.put("<", TokenType.T_LT);
        operators.put("!=", TokenType.T_NEQ);
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

    private int getColumnEnd(int col, String token){
        if(token.length() > 1){
            return col + token.length() - 1;
        }
        return col;
    }
    

    private void tokenize() {
        // remove all comments
        removeComments();

        int end = input.length();
        TokenType type = TokenType.Unknown;

        while (position < end){
            // grab the next word from the file
            col = 0;
            String word = getNextWord();

            // compare current word with keywords and operators
            if(keywords.containsKey(word)){
                type = keywords.get(word);
                tokens.add(new Token(type, word, lineNum, col, getColumnEnd(col, word)));
            }else if(operators.containsKey(word)){
                type = operators.get(word);
                tokens.add(new Token(type, word, lineNum, col, getColumnEnd(col, word)));
            // scan each character in the word
            }else{
                // Scan each character in the word
                int start = 0;
                String next_token;
                char firstChar;

                while (start < word.length()) {
                    firstChar = word.charAt(start);

                    if(isOperator(firstChar)){
                        // Check for operators between identifiers
                        next_token = "";
                        if (start < word.length() && isOperator(word.charAt(start))){
                            next_token += word.charAt(start);
                            if(start+1 < word.length() && isOperator(word.charAt(start+1))){
                                next_token += word.charAt(start+1);
                                tokens.add(new Token(operators.get(next_token), next_token, lineNum, col, getColumnEnd(col, next_token)));
                                start += 2;
                                col += next_token.length();
                            } else {
                                tokens.add(new Token(operators.get(next_token), next_token, lineNum, col, getColumnEnd(col, next_token)));
                                start++;
                                col += next_token.length();
                            }
                        }
                    } else if (isLetter(firstChar)) {
                        // Handle identifiers
                        next_token = "";
                        while (start < word.length() && (isLetter(word.charAt(start)) || isDigit(word.charAt(start)))) {
                            next_token += word.charAt(start);
                            start++;
                        }
                        // Check if token is a key word
                        if(keywords.containsKey(next_token)){
                            type = keywords.get(next_token);
                        }else{
                            type = TokenType.T_ID;
                        }
                        tokens.add(new Token(type, next_token, lineNum, col, getColumnEnd(col, next_token)));
                        col += next_token.length();
                        // Check for operators between identifiers
                        next_token = "";
                        if (start < word.length() && isOperator(word.charAt(start))){
                            next_token += word.charAt(start);
                            if(start+1 < word.length() && isOperator(word.charAt(start+1))){
                                next_token += word.charAt(start+1);
                                tokens.add(new Token(operators.get(next_token), next_token, lineNum, col, getColumnEnd(col, next_token)));
                                start += 2;
                                col += next_token.length();
                            } else {
                                tokens.add(new Token(operators.get(next_token), next_token, lineNum, col, getColumnEnd(col, next_token)));
                                start++;
                                col += next_token.length();
                            }
                        }
                    } else if (isDigit(firstChar)) {
                        // Handle numbers (including decimal numbers)
                        next_token = "";
                        boolean isDecimal = false;
                        while (start < word.length() && (isDigit(word.charAt(start)) || (word.charAt(start) == '.' && !isDecimal))) {
                            if (word.charAt(start) == '.') {
                                isDecimal = true;
                            }
                            next_token += word.charAt(start);
                            start++;
                        }
                        tokens.add(new Token(TokenType.T_INTCONSTANT, next_token, lineNum, col, getColumnEnd(col, next_token)));
                        col += next_token.length();
                        // Check for operators between digits
                        next_token = "";
                        if (start < word.length() && isOperator(word.charAt(start))){
                            next_token += word.charAt(start);
                            if(start+1 < word.length() && isOperator(word.charAt(start+1))){
                                next_token += word.charAt(start+1);
                                tokens.add(new Token(operators.get(next_token), next_token, lineNum, col, getColumnEnd(col, next_token)));
                                start += 2;
                                col += next_token.length();
                            } else {
                                tokens.add(new Token(operators.get(next_token), next_token, lineNum, col, getColumnEnd(col, next_token)));
                                start++;
                                col += next_token.length();
                            }
                        }
                    } else if (firstChar == '\"') {
                        // Handle string literals
                        next_token = "";
                        next_token += word.charAt(start);
                        start++;
                        while (start < word.length() && word.charAt(start) != '\"') {
                            next_token += word.charAt(start);
                            start++;
                        }
                        if (start < word.length() && word.charAt(start) == '\"') {
                            next_token += word.charAt(start);
                            start++;
                        }
                        tokens.add(new Token(TokenType.T_STRINGCONSTANT, next_token, lineNum, col, getColumnEnd(col, next_token)));
                        col += next_token.length() + 2; // Including the quotes
                    } else if (isPunctuation(firstChar)) {
                        // Handle punctuation
                        next_token = "";
                        next_token += firstChar;
                        tokens.add(new Token(punctuation.get(next_token), next_token, lineNum, col, getColumnEnd(col, next_token)));
                        start++;
                        col++;
                    } else {
                        // Handle unknown tokens
                        next_token = "";
                        next_token += firstChar;
                        tokens.add(new Token(TokenType.Unknown, next_token, lineNum, col, getColumnEnd(col, next_token)));
                        start++;
                        col++;
                    }
                }
            }
        }
    }

    public void printTokens() {
        for (Token token : tokens) {
            System.out.println(token.value + "     line " + token.line + " Cols " + token.col + "-" + token.end + " is " + getType(token.type));
        }
    }

    private boolean isWhiteSpace(char c) {
        return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f');
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
        int start;
        boolean isStringLiteral = false;

        while (isWhiteSpace(input.charAt(position))){
            if(input.charAt(position) == '\n'){
                lineNum++;
                lastLinePos = position;
            }
            position++;
        }
        start = position;

        if (input.charAt(position) == '\"'){
            isStringLiteral = true;
            position++;
        }

        while (position < input.length() && (isStringLiteral || !isWhiteSpace(input.charAt(position)))) {
            if (isStringLiteral && input.charAt(position) == '\"'){
                position++;
                break;
            }
            position++;
        }
        col = start - lastLinePos;
        return input.substring(start, position);
    }

    private void removeComments(){
        StringBuilder newStr = new StringBuilder(input);
        int i= 0;
        int end = newStr.length();

        while (i< end) {
            if (newStr.charAt(i) == '/' && i < end - 1 && newStr.charAt(i+1) == '/') {
                // Skip single-line comment
                newStr.setCharAt(i, ' ');
                newStr.setCharAt(i+1, ' ');
                i+= 2;
                while (i< end && newStr.charAt(i) != '\n') {
                    newStr.setCharAt(i, ' ');
                    i++;
                }
            } else {
                i++;
            }
        }

        input = newStr.toString();
    }

    public Token getNextToken(){
        Token t = null;
        if (this.curToken < tokens.size()){
            t = tokens.get(curToken);
            curToken++;
        }
        return t;
        
    }

    private String getType(TokenType type) {
        switch (type) {
            case T_AND: return "T_AND";
            case T_ASSIGN: return "T_ASSIGN";
            case T_BOOLTYPE: return "T_BOOLTYPE";
            case T_BREAK: return "T_BREAK";
            case T_CHARCONSTANT: return "T_CHARCONSTANT";
            case T_COMMA: return "T_COMMA";
            case T_COMMENT: return "T_COMMENT";
            case T_CONTINUE: return "T_CONTINUE";
            case T_DIV: return "T_DIV";
            case T_DOT: return "T_DOT";
            case T_ELSE: return "T_ELSE";
            case T_EQ: return "T_EQ";
            case T_EXTERN: return "T_EXTERN";
            case T_FALSE: return "T_FALSE";
            case T_FOR: return "T_FOR";
            case T_FUNC: return "T_FUNC";
            case T_GEQ: return "T_GEQ";
            case T_GT: return "T_GT";
            case T_ID: return "T_ID";
            case T_IF: return "T_IF";
            case T_INTCONSTANT: return "T_INTCONSTANT";
            case T_INTTYPE: return "T_INTTYPE";
            case T_LCB: return "T_LCB";
            case T_LEFTSHIFT: return "T_LEFTSHIFT";
            case T_LEQ: return "T_LEQ";
            case T_LPAREN: return "T_LPAREN";
            case T_LSB: return "T_LSB";
            case T_LT: return "T_LT";
            case T_MINUS: return "T_MINUS";
            case T_MOD: return "T_MOD";
            case T_MULT: return "T_MULT";
            case T_NEQ: return "T_NEQ";
            case T_NOT: return "T_NOT";
            case T_NULL: return "T_NULL";
            case T_OR: return "T_OR";
            case T_PACKAGE: return "T_PACKAGE";
            case T_PLUS: return "T_PLUS";
            case T_RCB: return "T_RCB";
            case T_RETURN: return "T_RETURN";
            case T_RIGHTSHIFT: return "T_RIGHTSHIFT";
            case T_RPAREN: return "T_RPAREN";
            case T_RSB: return "T_RSB";
            case T_SEMICOLON: return "T_SEMICOLON";
            case T_STRINGCONSTANT: return "T_STRINGCONSTANT";
            case T_STRINGTYPE: return "T_STRINGTYPE";
            case T_TRUE: return "T_TRUE";
            case T_VAR: return "T_VAR";
            case T_VOID: return "T_VOID";
            case T_WHILE: return "T_WHILE";
            case T_WHITESPACE: return "T_WHITESPACE";
            case Unknown: return "Unknown";
            default: return "Invalid TokenType";
        }
    }
}