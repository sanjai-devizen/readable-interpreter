#include <stdio.h>
#include "lexer.h"

static char** array_of_tokens;

int main(){
	while(1){
		char* input = get_str();

		array_of_tokens = init_lex(input);

		free(input);
	}

	return 0;
}