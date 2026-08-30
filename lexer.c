#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

#define EXP_SIZE 50
#define CHAR_SIZE 64

//Custom written string append function
void str_append(char* str_1, char* str_2){
	int end_str_1 = 0, end_str_2 = 0;
	for(; str_1[end_str_1] != '\0'; end_str_1 = end_str_1 + 1){ }

	for(; str_2[end_str_2] != '\0'; end_str_2 = end_str_2 + 1, end_str_1 = end_str_1 + 1){
		str_1[end_str_1] = str_2[end_str_2];
	}
    str_1[end_str_1] = '\0';
}

char* pack_char_into_str(int ch){
	char* character = (char*)calloc(CHAR_SIZE, sizeof(char));
	character[0] = (char)ch;
	character[1] = '\0';

	return character;
}

char* get_str(){
	char* str = (char*)malloc(sizeof(char) * EXP_SIZE);
	printf("\n>> ");
	if (fgets(str, EXP_SIZE, stdin) != NULL) {
        // fgets includes the '\n' (Enter key) at the end of the string. 
        // This removes it so it doesn't mess up your lexer.
        str[strcspn(str, "\n")] = '\0';
    }

	return str;
}

Token** init_token_array(int row){
	Token** token_array = (Token**)calloc(sizeof(Token*), row);

	return token_array;
}

void store_token_into_array(Token* token, T_Array* token_array){
	token_array->tokens[token_array->n_tokens] = token;
	token_array->n_tokens = token_array->n_tokens + 1;
}

Exp* make_exp_from_str(char* string){
	Exp* expression = (Exp*)malloc(sizeof(Exp));
	expression->exp = string;
	expression->index = 0;

	return expression;
}

int get_from_exp_c(Exp* exp){
	int ch = (int)exp->exp[exp->index];
	exp->index = exp->index + 1;

	if (ch == '\0') return 0;

	return ch;
}

int peek_from_exp_c(Exp* exp){
	int ch = (int)exp->exp[exp->index];

	if (ch == '\0') return 0;

	return ch;
}

void print_tokens(T_Array* token_array){
	for(int i = 0; i < token_array->n_tokens; i++){
		Token* token = token_array->tokens[i];

		printf("%s(%s)", token_names[token->type], token->ch);
	}
}

void init_lex(char* string){
	//Making of expression and initializing token array
	Exp* ex = make_exp_from_str(string);
	T_Array* token_array = (T_Array*)malloc(sizeof(T_Array));

	token_array->tokens = init_token_array(strlen(ex->exp) + 1);
	token_array->n_tokens = 0;

	//tokenization engine
	while(1){
		int character = get_from_exp_c(ex);
		if (!character) break;

		char* ch = pack_char_into_str(character);

		if (ch[0] != ' '){

		//Making of token
		Token* token = (Token*)malloc(sizeof(Token));
		token->ch = ch;
				if (!strcmp(ch, "+")) { 
					token->type = ADD;
					token->index = ex->index;
				} else if (!strcmp(ch, "-")) { 
					token->type = MINUS;
					token->index = ex->index;
				} else if (!strcmp(ch, "*")) { 
					token->type = MULTIPLY;
					token->index = ex->index;
				} else if (!strcmp(ch, "/")) { 
					token->type = DIVIDE;
					token->index = ex->index;
				} else if (!strcmp(ch, ">")) { 
					token->type = LGREAT;
					token->index = ex->index;
				} else if (!strcmp(ch, "<")) { 
					token->type = LLESS;
					token->index = ex->index;
				} else if (!strcmp(ch, "(")) { 
					token->type = LPAREN;
					token->index = ex->index;
				} else if (!strcmp(ch, ")")) { 
					token->type = RPAREN;
					token->index = ex->index;
				} else if (!strcmp(ch, "=")){
					if (peek_from_exp_c(ex) == '='){
						int next_ch = get_from_exp_c(ex);
						char append_str[2] = {(char)next_ch, '\0'};							
						
						str_append(token->ch, append_str);
					}
				} else if (ch[0] >= '0' && ch[0] <= '9'){
					token->type = CONSTANT;
					token->index = ex->index;
					while(peek_from_exp_c(ex) >= '0' && peek_from_exp_c(ex) <= '9'){
						int next_ch = get_from_exp_c(ex);
						char append_str[2] = {(char)next_ch, '\0'};							
						
						str_append(token->ch, append_str);
					}			
				}	

		store_token_into_array(token, token_array);
		}
	}
	print_tokens(token_array);

	//freeing dynamically allocated memory space
	free(ex);
    for(int i = 0; i < token_array->n_tokens; i++){
        free(token_array->tokens[i]->ch); // Free the string buffer first
        free(token_array->tokens[i]);     // Then free the token struct
    }
    free(token_array->tokens); // Free the pointer array
    free(token_array);
}