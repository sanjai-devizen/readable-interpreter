#include <stdlib.h>
#include "define.h"

void free_all(){
	//freeing dynamically allocated memory space
	free(ex);
	if (token_array != NULL){
	    for(int i = 0; i < token_array->n_tokens; i++){
	        free(token_array->tokens[i]->ch); // Free the string buffer first
	        free(token_array->tokens[i]);     // Then free the token struct
	    }
	    free(token_array->tokens); // Free the pointer array
	    free(token_array);
	}
	if (tree != NULL) free(tree);
}