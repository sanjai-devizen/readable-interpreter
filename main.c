#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

void print_tokens(T_Array* token_array){
	for(int i = 0; i < token_array->n_tokens; i++){
		Token* token = token_array->tokens[i];

		printf("%s(%s) ", token_names[token->type], token->ch);
	}
	printf("\n");
}

void print_ast(Node* ast){
	if (ast != NULL){
		if (ast->kind == BINOP){
			printf("%c", ast->binop);
		} else {
			printf("%d", ast->number);
		}

		print_ast(ast->left);
		print_ast(ast->right);
	}
}

int main(){
	printf("READABLE-INTERPRETER : lexer done, lexer output -\n");
	for(;;){
		char* input = get_str();
		if (strcmp(input, "exit") == 0) break;
		
		init_lex(input);

		if (token_array != NULL) print_tokens(token_array);

		init_parser();

		printf("\n\nAST tree :\n");
		print_ast(ast);

		free_all();
	}

	return 0;
}