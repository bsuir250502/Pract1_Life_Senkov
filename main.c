#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"

#define STR_MAX 256

typedef struct {
    int width;
    int length;
    int gen_number;
} settings_t;

int int_input(char *information, int min, int max);
void file_output(char *file_name);
void help(int argc, char **argv);
void game_administration(settings_t size);
int select_game_settings();
int info_variant();
int settings_input(settings_t size);
int file_read(settings_t size);


int main(int argc, char **argv)
{
    settings_t size;
    help(argc,argv);
    game_administration(size);
    return 0;
}

void help(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        file_output("README.txt");
        exit(0);
    }
}

void game_administration(settings_t size)
{
    if(select_game_settings()) {
        settings_input(size);
    }
    else {
        file_read(size);
    }
}

int settings_input(settings_t size)
{
    size.width = int_input("\nenter width", 0, 20);
    size.length = int_input("length", 0, 20);
    size.gen_number = int_input("generation number", 1, 100);
    return 1;
}

int file_read(settings_t size)
{
    FILE *file = fopen("settings.txt", "r");
    fclose(file);
    return 1;
}

int select_game_settings()
{
    int i = 0;
    if (info_variant() == 1) {
        file_output("settings.txt");
        puts("                          If you want:\n"
             "          -------------------------------------------------\n"
             "          1) to continue game with this settings, enter '1'\n"
             "          -------------------------------------------------\n"
             "               2) to input your settings, enter '2'\n");
        if ((i = int_input("enter", 1, 2)) == 2) {
            return 1;
        }
        else {
            return 0;
        }
    }
    return 1;
}

int info_variant()
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
