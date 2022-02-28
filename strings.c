#include <strings.h>

#include <malloc.h>
#include <string.h>

// lisaa stringit yhteen -> palauttaa stringin
//concat("paalu", "rosso") -> paalurosso
char *concat(char *str, char *add) {
	const int STR_LENGTH = strlen(str);
	const int ADD_LENGTH = strlen(add);
	
	// varaa muistia str + add + null verran
	char *output = malloc(STR_LENGTH + ADD_LENGTH + 1);
	
	// kopioi muutujan str muuttujaan output
	memcpy(output, str, STR_LENGTH);

	// kopioi muuttujan add + null muuttujan output peraan
	memcpy(output + STR_LENGTH, add, ADD_LENGTH + 1);
	
	return output;
}