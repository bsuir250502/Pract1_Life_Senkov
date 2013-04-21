#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"

#define STR_MAX 256

void str_input(char *information, char *input_text, int max_number_of_symbols);
int int_input(char *information, int min, int max);
void help(int argc, char **argv);
void file_output(char *file_name);
int game_settings();
int select_info_variant();


int main(int argc, char **argv)
{
    help(argc,argv);
    game_settings();
    return 0;
}

void help(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        file_output("README.txt");
        exit(0);
    }
}

void file_output(char *file_name)
{   
    char input_buffer[STR_MAX];
    FILE *file;
    file = fopen(file_name, "r") ;
    puts("\n");
    while (fgets(input_buffer, sizeof(input_buffer)/sizeof(*input_buffer), file)) {
            printf ("%s", input_buffer);
        }
    fclose(file);
    puts("\n");
}

int game_settings()
{
    int i = 0;
    if (select_info_variant() == 1) {
        file_output("settings.txt");
        puts("                          If you want:\n"
             "          -------------------------------------------------\n"
             "          1) to continue game with this settings, enter '1'\n"
             "          -------------------------------------------------\n"
             "               2) to input your settings, enter '2'\n");
        i = int_input("enter", 1, 2);
        if (i == 2) {
            exit(0);
        }
    }
    else {
        return 1;
    } 
    return 1;
}

int select_info_variant()
{
    int select;
    puts ("\n                            game settings :\n"
          "                  ---------------------------------------\n"
          "                     1) view already done settings list. \n"
          "                  ---------------------------------------\n"
          "     2) manual input. (size of grid, number of generations, first generation) \n");
    select = int_input("enter", 1, 2);
    return select;
}
