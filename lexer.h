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

static char* token_names[] = {
	"CONSTANT",
	"ADD",
	"MINUS",
	"MULTIPLY",
	"DIVIDE",
	"LGREAT",
	"LLESS",
	"EQUAL",
	"LPAREN",
	"RPAREN"
};

typedef struct{
	char* ch;
	int type;
	int index;
} Token;

typedef struct{
	Token** tokens;
	int n_tokens;
} T_Array;

typedef struct{
	char* exp;
	int index;
} Exp;

char* get_str();
void init_lex(char* string);

#endif