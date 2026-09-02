#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

static char** array_of_tokens;

int main(){
	printf("READABLE-INTERPRETER : lexer done, lexer output -\n");
	for(;;){
		char* input = get_str();
		if (strcmp(input, "exit") == 0) break;
		
		init_lex(input);
	}

	return 0;
}