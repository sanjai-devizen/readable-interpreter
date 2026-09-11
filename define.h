#ifndef DEFINE_H
#define DEFINE_H

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
	
typedef struct Node{
	int kind;
	struct Node* left;
	char binop;
	struct Node* right;
	int number;
} Node;

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
extern Exp* ex;
extern Token* token;
extern T_Array* token_array;
extern Node* ast;

char* get_str();
void init_lex(char* string);

void init_parser();

void free_all();

void init_walker();

#endif