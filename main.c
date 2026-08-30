#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

static char** array_of_tokens;

int main(){
	for(;;){
		char* input = get_str();

		init_lex(input);
	}

	return 0;
}