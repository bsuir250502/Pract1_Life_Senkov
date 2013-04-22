#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"

#define STR_MAX 256
#define MAX_WIDTH 50
#define MAX_LENGTH 50
#define MAX_GEN_NUMBER 150

typedef struct {
    int width;
    int height;
    int gen_number;
} settings_t;

int int_input(char *information, int min, int max, FILE *file);
void file_output(char *file_name);
void help(int argc, char **argv);
void game_administration(settings_t size);
int select_game_settings();
int info_variant();
int settings_input(settings_t *size, FILE *file);



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
    FILE *file;
    if (!(file = fopen("settings.txt", "r"))) {
        puts ("\n!! No such file in directory !!\n");
    }
    if(select_game_settings()) {
        settings_input(&size, stdin);
    }
    else {
        settings_input(&size, file);
    }
    fclose(file);
}

int settings_input(settings_t *size, FILE *file)
{
    size->width = int_input("\nenter width", 2, MAX_WIDTH, file);
    size->height = int_input("height", 2, MAX_LENGTH, file);
    size->gen_number = int_input("generation number", 1, MAX_GEN_NUMBER, file);
    printf("\nsize of game map:\n   width = %d\n   height = %d\n   gen_number = %d\n",
            size->width, size->height, size->gen_number);

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
        if ((i = int_input("enter", 1, 2, stdin)) == 2) {
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
    select = int_input("enter", 1, 2, stdin);
    return select;
}
