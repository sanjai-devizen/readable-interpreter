#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "colour.h"

void print_tokens(T_Array* token_array){
	for(int i = 0; i < token_array->n_tokens; i++){
		Token* token = token_array->tokens[i];

		printf("%s%s(%s%s%s)%s ", COLOR_BLUE, token_names[token->type], COLOR_RESET, token->ch, COLOR_BLUE, COLOR_RESET);
	}
	printf("\n");
}

void print_ast(Node* ast){
	if (ast != NULL){
		if (ast->kind == BINOP){
			printf("%c ", ast->binop);
		} else {
			printf("%d ", ast->number);
		}

		print_ast(ast->left);
		print_ast(ast->right);
	}
}

void print_guide(){
	printf("You found my readable interpreter ?!\nGo ahead and type a mathematical expression into the prompt.\nYou would see log entries of every step under each phase of the interpreter in the making of THE OUTPUT.\nIf you want to exit type 'exit'.\nIf you want to use your colour of choice refer to 'colour.h' to see available colours and do feel free to use it wherever needed.\n");
}

int main(){
	printf("%s\nREADABLE-INTERPRETER :)%s\n", BOLD_GREEN, COLOR_RESET);
	for(;;){
		char* input = get_str();
		if (strcmp(input, "exit") == 0) break;
		else if (strcmp(input, "") == 0) continue;
		else if (strcmp(input, "help") == 0) {
			print_guide();
			continue;
		}

		ex = NULL;
		token = NULL;
		token_array = NULL;
		ast = NULL;
		
		printf("%sPhase 1: Initializing lexer%s", COLOR_YELLOW, COLOR_RESET);
		init_lex(input);

		if (token_array != NULL) {
			printf("%s, Lexer Output (Array of tokens) :%s\n\n", COLOR_YELLOW, COLOR_RESET);
			print_tokens(token_array);
		}
		else {
			printf("\n%sAbort%s\n", COLOR_RED, COLOR_RESET);
			free_all();
			continue;
		}

		printf("\n%sPhase 2: Initializing parser, Parser Output :%s\n", COLOR_YELLOW, COLOR_RESET);
		init_parser();

		if (ast != NULL){
			printf("\n\n%sAST tree (Prefix format): %s", COLOR_GREEN, COLOR_RESET);
			print_ast(ast);
		}

		printf("\n\n%sPhase 3: Initializing AST walker, walker Output :%s", COLOR_YELLOW, COLOR_RESET);
		init_walker();

		free_all();
	}

	return 0;
}