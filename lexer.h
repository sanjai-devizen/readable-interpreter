#ifndef LEXER_H
#define LEXER_H

enum{
	CONSTANT,
	ADD,
	MINUS,
	MULTIPLY,
	DIVIDE,
	LGREAT,
	LLESS,
	EQUAL,
	LPAREN,
	RPAREN
};

typedef struct{
	int ch;
	int type;
	int index;
} Token;

typedef struct{
	char** tokens;
	int n_tokens;
} T_Array;

typedef struct{
	char* exp;
	int curr_index;
} Exp;

char* get_exp();

#endif