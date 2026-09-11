#include <stdio.h>
#include <stdlib.h>
#include "define.h"

/* GRAMMAR for the recursive descent parser:
 *
 * Expression -> Term (("+" / "-") Term)*
 * Term       -> Factor (("*" / "/") Factor)*
 * Factor     -> "(" Expression ")" / Number
 */

static char* lookahead_char;
static int lookahead_index = 0;
static int number_token;

Node* parse_expr(void);
Node* parse_term(void);
Node* parse_factor(void);

void consume(void) {
    lookahead_index = lookahead_index + 1;

    if (token_array->tokens[lookahead_index] != NULL){
        lookahead_char = token_array->tokens[lookahead_index]->ch;
    } else {
       	lookahead_char = "";
    }
}

int string_to_number(char* string, int string_index, int to_number){
	if (string[string_index] != '\0'){ 
		int digit = string[string_index] - '0';
		to_number = to_number * 10 + digit;

		return string_to_number(string, string_index + 1, to_number);
	} else {
		number_token = to_number;

		return 0;
	}
}

Node* create_node(int kind, char* l_char){
	Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Heap memory allocation error\n");
        exit(1);
    }

	if (kind == 0){ 
		new_node->kind = BINOP;
		new_node->left = NULL;  
		new_node->binop = l_char[0];
		new_node->right = NULL;

		consume(); 
	} else { 
		new_node->kind = NUMBER;
		string_to_number(l_char, 0, 0);
		new_node->number = number_token;
        new_node->left = NULL;
        new_node->right = NULL;

        consume(); 
	}

    return new_node; 
}

Node* parse_expr(void){ 
	printf("\nCalling term...");

	Node* left_node = parse_term();
    if (token_array->tokens[lookahead_index] != NULL){
        lookahead_char = token_array->tokens[lookahead_index]->ch;
    } else {
       	lookahead_char = "";
    }

	printf("\nLooking for + and - operators...");
	while(lookahead_char[0] == '+' || lookahead_char[0] == '-'){
		Node* op_node = create_node(BINOP, lookahead_char);
		op_node->left = left_node; 
		op_node->right = parse_term(); 
        
        left_node = op_node;

        if (token_array->tokens[lookahead_index] != NULL){
        	lookahead_char = token_array->tokens[lookahead_index]->ch;
        } else {
        	lookahead_char = "";
        }
	}

    return left_node;
}

Node* parse_term(void){ 
	printf("\nCalling factor...");

	Node* left_node = parse_factor();
    if (token_array->tokens[lookahead_index] != NULL){
        lookahead_char = token_array->tokens[lookahead_index]->ch;
    } else {
       	lookahead_char = "";
    }

	printf("\nLooking for * and / operators...");
	while(lookahead_char[0] == '*' || lookahead_char[0] == '/'){
		Node* op_node = create_node(BINOP, lookahead_char);
		op_node->left = left_node;
		op_node->right = parse_factor(); 
        
        left_node = op_node;
    	if (token_array->tokens[lookahead_index] != NULL){
        	lookahead_char = token_array->tokens[lookahead_index]->ch;
    	} else {
       		lookahead_char = "";
    	}
	}

    return left_node;
}

Node* parse_factor(void){
    if (token_array->tokens[lookahead_index] != NULL){
        lookahead_char = token_array->tokens[lookahead_index]->ch;
    } else {
       	lookahead_char = "";
    }

	printf("\nLooking for paranthesis and numbers...");
	if (lookahead_char[0] == '('){
		consume(); 
		Node* node = parse_expr();
    	if (token_array->tokens[lookahead_index] != NULL){
        	lookahead_char = token_array->tokens[lookahead_index]->ch;
    	} else {
       		lookahead_char = "";
    	}	

		if (lookahead_char[0] == ')'){
			consume(); 

            return node;
		} else {
			printf("\nparse error : Invalid syntax, expected : ')'\n");
			free_all(); 
			exit(1);
		}
	} else if (lookahead_char[0] >= '0' && lookahead_char[0] <= '9'){
		Node* number_node = create_node(NUMBER, lookahead_char);

        return number_node; 
	} else {
		printf("\nparse error : invalid syntax, expected : number or '('\n");
		exit(1);
	}
}

void init_parser(void){
	lookahead_index = 0;

    if (token_array->tokens[lookahead_index] != NULL){
        lookahead_char = token_array->tokens[lookahead_index]->ch;
    } else {
       	lookahead_char = "";
    }
    
    printf("\nStarting up AST tree...");
	ast = parse_expr();

	printf("\nAST successfully constructed :)"); 
}