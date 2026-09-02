#include <stdoio.h>
#include <stdlib.h>
#include "define.h"

#define BINOP 0
#define NUMBER 1

Node* build_binop(){
	Node* op_node = NULL;

	op_node = (Node*)malloc(sizeof(Node));
	op_node->kind = BINOP;
	op_node->data.bin_op.left = NULL;
	op_node->data.bin_op.right = NULL;

	return op_node;
}

Node* build_number(){
	Node* num_node = NULL;

	num_node = (Node*)malloc(sizeof(Node));

	return num_node;
}

Node* build_ast(Node* head, int kind){
	Node* node = NULL;

	if (kind == BINOP){
		node = build_binop();
	} else if (kind == NUMBER){
		node = build_number();
	}

	if (head == NULL) return node;
	else if (head->kind == BINOP){

	} else if (head->kind == NUMBER){

	}
}

int parse_expr(Token** token_array){

}

int parse_term(Token** token_array){

}

int parse_factor(Token** token_array){

}

void init_parser(Token** token_array){
	Node* ast_head = NULL;

	
}