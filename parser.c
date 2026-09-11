#include <stdoio.h>
#include <stdlib.h>
#include "define.h"

/* GRAMMAR for the recursice descent parser:
 *
 * Expression -> Term.(("+" / "-").Term)*
 * Term       -> Factor.(("*" / "/").Factor)*
 * Factor     -> "(".Expression.")" / Number
 * Number     -> (0 - 9)*
 */

static char* lookahead_char;
static int lookahead_index = 0;
static int number_token;

int string_to_number(char* string, int string_index, int to_number){
	if (string[string_index] != '/0'){
		int digit = string[string_index] - '0';
		to_number = to_number * 10 + digit;

		return string_to_number(string, string_index + 1, to_number);
	} else {
		number_token = to_number;
		return 0;
	}
}

Node* create_node(int kind, char* lookahead_char){
	Node* new_node = (Node*)malloc(sizeof(Node));

	if (kind == 0){
		new_node->kind = BINOP;
		new_node->left = NULL
		new_node->binop = *(lookahead_char + 0);
		new_node->right = NULL;

		lookahead_index = lookahead_index + 1;
	} else {
		new_node->kind = NUMBER;
		string_to_number(lookahead_char, 0, 0);

		new_node->number = number_token;
	}
}

void parse_expr(){
	parse_term();
	lookahead_char = token_array[lookahead_index]->ch;

	while(lookahead_char[0] == '+' || lookahead_char[0] == '-'){
		Node* op_node = create_node(BINOP, lookahead_char);
		op_node->left = tree;

		parse_term();
	}
}

int parse_term(){
	parse_factor();
	lookahead_char = token_array[lookahead_index]->ch;

	while(lookahead_char[0] == '*' || lookahead_char[0] == '/'){
		Node* op_node = create_node(BINOP, lookahead_char);
		op_node->left = tree;

		parse_term();
	}
}

int parse_factor(){
	lookahead_char = token_array[lookahead_index]->ch;	

	if (lookahead_char[0] == '('){
		consume();
		parse_expr();
		lookahead_char = token_array[lookahead_index]->ch;	

		if (lookahead_char[0] == ')'){
			consume();
		} else {
			printf("\nparse error : Invalid syntax, expected : ')'");
			free_all();
			exit(1);
		}
	} else if (lookahead_char[0] >= '0' && lookahead_char[0] <= '9'){
		Node* number_node = create_node(NUMBER, lookahead_char);
		number_node->left = tree;
	} else {
		printf("\nparse error : invalid syntax, expected : number or '()");
		exit(1);
	}
}

void init_parser(){
	ast = (Node*)malloc(sizeof(Node));

	parse_expr();
}