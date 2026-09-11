#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "colour.h"

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
	printf("%s\nREADABLE-INTERPRETER :%s\n", BOLD_GREEN, COLOR_RESET);
	for(;;){
		char* input = get_str();
		if (strcmp(input, "exit") == 0) break;
		else if (strcmp(input, "") == 0) continue;

		ex = NULL;
		token = NULL;
		token_array = NULL;
		ast = NULL;
		
		init_lex(input);

		if (token_array != NULL) print_tokens(token_array);
		else {
			free_all();
			continue;
		}

		init_parser();

		if (ast != NULL){
			printf("\n\n%sAST tree : %s", COLOR_GREEN, COLOR_RESET);
			print_ast(ast);
		}

		init_walker();

		free_all();
	}

	return 0;
}