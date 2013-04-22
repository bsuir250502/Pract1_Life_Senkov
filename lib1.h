#ifndef _LIB1_H_
#define _LIB1_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_input(char *information, char *input_text, int max_number_of_symbols);
int int_input(char *information, int min, int max, FILE *file);
void file_output(char *file_name);

#endif /* _LIB1_H_ */
