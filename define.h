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
	
typedef struct{
	int kind;
	struct Node* left;
	int binop;
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
static Exp* ex = NULL;
static Token* token = NULL;
static T_Array* token_array = NULL;
static Node* ast = NULL;

char* get_str();
void init_lex(char* string);

void init_parser();

void free_all();

#endif