#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

#define EXP_SIZE 50
#define TOKEN_SIZE 30

char* get_str(){
	char* exp = (char*)malloc(sizeof(char), EXP_SIZE);
	printf("\n>> ");
	scanf("%s", exp);
	return exp;
}

char** init_token_array(int row){
	char** token_array = (char**)calloc(sizeof(char*) * row);

	for(int i = 0; i < row; i++){
		(token_array + i) = (char*)malloc(TOKEN_SIZE);
	}

	return token_array;
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

char** init_lex(char* string){
	Exp* ex = make_exp_from_str(string);
	T_Array* token_array = (T_Array*)malloc(sizeof(T_Array));

	token_array->tokens = init_token_array(sizeof(ex->exp));

	while(1){
		int ch = get_from_exp_c(ex);
		if (!ch) break;

		Token* token = (Token*)malloc(sizeof(Token));
		token->ch = ch;

		if (ch != ' '){
			switch(ch){
				case '+': case '-': case '*': case '/': //arithmetic
				case '==': case '>': case '<': 			//comparison
				case '(': case ')': {					//paranthesis	
					if (ch == '+') { 
						token->type = ADD;
						token->index = ex->index;
					}
					if (ch == '-') { 
						token->type = MINUS;
						token->index = ex->index;
					}
					if (ch == '*') { 
						token->type = MULTIPLY;
						token->index = ex->index;
					}
					if (ch == '/') { 
						token->type = DIVIDE;
						token->index = ex->index;
					}
					if (ch == '==') { 
						token->type = EQUAL;
						token->index = ex->index;
					}
					if (ch == '>') { 
						token->type = LGREAT;
						token->index = ex->index;
					}
					if (ch == '<') { 
						token->type = LLESS;
						token->index = ex->index;
					}
					if (ch == '(') { 
						token->type = LPAREN;
						token->index = ex->index;
					}
					if (ch == ')') { 
						token->type = RPAREN;
						token->index = ex->index;
					}
					break;
				}
				case '0' ... '9':{
					
				}
			}
		}
	}
}