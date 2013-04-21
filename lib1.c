#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function for input and valid infomation (srting). */
void str_input(char *information, char *input_text, int max_number_of_symbols)
{
    while (1) {
        printf("%s", information);
        fgets(input_text, max_number_of_symbols, stdin);
        if (input_text[0] == '\n' || input_text[0] == ' ') {
            puts("Invalid input, try again.");
        }
        else {
            input_text[strlen(input_text)-1]='\0';
            break;
        }
    }
}

/* function for input and valid infomation (int). */
int int_input(char *information, int min, int max)
{
    int input_text;
    char input_buffer[128];
    printf("%s (min - %d, max - %d): ", information, min, max);
    while (1) {
        fgets(input_buffer, 128, stdin);
        input_buffer[strlen(input_buffer)-1]='\0';
        if (!(input_text = atoi(input_buffer)) || input_text < min || input_text > max) {
            puts("Invalid input, try again.");
        }
        else {
            break;
        }
    }
    return input_text;
}

/* -h */
void help_output()
{   
    char input_buffer[128];
    FILE *file = fopen("README.txt","r");
    while (fgets(input_buffer, sizeof(input_buffer)/sizeof(*input_buffer), file)) {
        printf("%s", input_buffer);
    }
    fclose(file);
}
