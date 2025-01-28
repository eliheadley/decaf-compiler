// Change the language to
package main

import (
	"fmt"
	"log"
	"os"
)

type TokenType int

const (
	T_EOF            TokenType = 0  // end of file
	T_AND            TokenType = 1  // &&
	T_ASSIGN         TokenType = 2  // =
	T_BREAK          TokenType = 3  // break
	T_CHARCONSTANT   TokenType = 4  // char_lit (character literal)
	T_COLON          TokenType = 5  // ;
	T_COMMA          TokenType = 6  // ,
	T_COMMENT        TokenType = 7  // comment
	T_CONTINUE       TokenType = 8  // continue
	T_DIV            TokenType = 9  // /
	T_DOT            TokenType = 10 // .
	T_ELSE           TokenType = 11 // else
	T_EQ             TokenType = 12 // ==
	T_FALSE          TokenType = 13 // false
	T_FOR            TokenType = 14 // for
	T_FUNC           TokenType = 15 // func
	T_GEQ            TokenType = 16 // >=
	T_GT             TokenType = 17 // >
	T_ID             TokenType = 18 // identifier
	T_IF             TokenType = 19 // if
	T_INTCONSTANT    TokenType = 20 // int_lit (integer literal)
	T_LCB            TokenType = 21 // {
	T_LEFTSHIFT      TokenType = 22 // <<
	T_LEQ            TokenType = 23 // <=
	T_LPAREN         TokenType = 24 // (
	T_LSB            TokenType = 25 // [
	T_LT             TokenType = 26 // <
	T_MINUS          TokenType = 27 // -
	T_MOD            TokenType = 28 // %
	T_MULT           TokenType = 29 // *
	T_NEQ            TokenType = 30 // !=
	T_NOT            TokenType = 31 // !
	T_NULL           TokenType = 32 // null
	T_OR             TokenType = 33 // ||
	T_PLUS           TokenType = 34 // +
	T_RCB            TokenType = 35 // }
	T_RETURN         TokenType = 36 // return
	T_RIGHTSHIFT     TokenType = 37 // >>
	T_RPAREN         TokenType = 39 // )
	T_RSB            TokenType = 40 // ]
	T_SEMICOLON      TokenType = 41 // ;
	T_STRINGCONSTANT TokenType = 42 // string_lit (string literal)
	T_TRUE           TokenType = 43 // true
	T_WHILE          TokenType = 44 // while
	T_WHITESPACE     TokenType = 45 // whitespace
	T_BOOLTYPE       TokenType = 46 // bool
	T_INTTYPE        TokenType = 47 // int
	T_STRINGTYPE     TokenType = 48 // string
	T_EXTERN         TokenType = 49 // extern
	T_PACKAGE        TokenType = 50 // package
	T_VAR            TokenType = 51 // var
	T_VOID           TokenType = 52 // void
	Unknown          TokenType = -1
)

type Token struct {
	val      string
	typ      TokenType
	line_num int
	col      int
}

func reserved_charaters() (map[string]TokenType, map[string]TokenType, map[string]TokenType) {
	var keywords = make(map[string]TokenType)
	var operators = make(map[string]TokenType)
	var punctuation = make(map[string]TokenType)

	// Keywords
	keywords["bool"] = T_BOOLTYPE
	keywords["break"] = T_BREAK
	keywords["continue"] = T_CONTINUE
	keywords["else"] = T_ELSE
	keywords["extern"] = T_EXTERN
	keywords["false"] = T_FALSE
	keywords["for"] = T_FOR
	keywords["func"] = T_FUNC
	keywords["if"] = T_IF
	keywords["int"] = T_INTTYPE
	keywords["null"] = T_NULL
	keywords["package"] = T_PACKAGE
	keywords["return"] = T_RETURN
	keywords["string"] = T_STRINGTYPE
	keywords["true"] = T_TRUE
	keywords["var"] = T_VAR
	keywords["void"] = T_VOID
	keywords["while"] = T_WHILE
	// Operators
	operators["&&"] = T_AND
	operators["="] = T_ASSIGN
	operators["=="] = T_EQ
	operators[">="] = T_GEQ
	operators[">"] = T_GT
	operators["<="] = T_LEQ
	operators["<"] = T_LT
	operators["!="] = T_NEQ
	operators["!"] = T_NOT
	operators["||"] = T_OR
	operators["+"] = T_PLUS
	operators["-"] = T_MINUS
	operators["*"] = T_MULT
	operators["/"] = T_DIV
	operators["%"] = T_MOD
	operators["<<"] = T_LEFTSHIFT
	operators[">>"] = T_RIGHTSHIFT
	// Punctuation
	punctuation[","] = T_COMMA
	punctuation["."] = T_DOT
	punctuation[";"] = T_SEMICOLON
	punctuation["{"] = T_LCB
	punctuation["}"] = T_RCB
	punctuation["("] = T_LPAREN
	punctuation[")"] = T_RPAREN
	punctuation["["] = T_LSB
	punctuation["]"] = T_RSB

	return keywords, operators, punctuation
}

func removeComments(src_code *[]byte) {
	var position int = 0
	var end int = len(*src_code)

	for position < end {
		if (*src_code)[position] == '/' && position < end-1 && (*src_code)[position+1] == '/' {
			// Skip single-line comment
			(*src_code)[position] = ' '
			(*src_code)[position+1] = ' '
			position += 2
			for position < end && (*src_code)[position] != '\n' {
				(*src_code)[position] = ' '
				position += 1
			}
		} else {
			position += 1
		}
	}
}

func getNextToke() {
	// This function grabs the next token from the input
	fmt.Println("Next token")
}

func tokenize(src_code *[]byte) {
	removeComments(src_code)
	fmt.Println(string(*src_code))
}

func readFile(file string) []byte {
	content, err := os.ReadFile(file)
	if err != nil {
		log.Fatal(err)
	}
	return content
}

func main() {
	var src_code = readFile(os.Args[1])
	tokenize(&src_code)
}
