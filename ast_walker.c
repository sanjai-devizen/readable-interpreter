#include <stdio.h>
#include "define.h"
#include "colour.h"

int ast_walk(Node* ast){
	if (ast != NULL){
		if (ast->kind == BINOP){

			if (ast->binop == '+') return ast_walk(ast->left) + ast_walk(ast->right);
			if (ast->binop == '-') return ast_walk(ast->left) - ast_walk(ast->right);
			if (ast->binop == '*') return ast_walk(ast->left) * ast_walk(ast->right);
			if (ast->binop == '/') return ast_walk(ast->left) / ast_walk(ast->right);			
		} else {
			return ast->number;
		}
	}
}

void init_walker(){
	int final_result;

	final_result = ast_walk(ast);

	printf("\n\n%sWalker done :) Output :%s ", COLOR_GREEN, COLOR_RESET);
	printf("%s%d%s\n", COLOR_MAGENTA, final_result, COLOR_RESET);
}