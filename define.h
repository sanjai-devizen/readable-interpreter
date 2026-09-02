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

enum{
	BINOP,
	NUMBER
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
	
typedef struct{
	int kind;

	union{
		struct bin_op{
			struct bin_op* left;
			int op;
			struct bin_op* right;
		};

		struct number{
			int value;
		};
	} data;

} Node;

char* get_str();
void init_lex(char* string);

#endif