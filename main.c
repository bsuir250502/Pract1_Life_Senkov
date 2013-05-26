#include <stdio.h>
#include <stdlib.h>
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
void str_input(char *information, char *input_text, int max_number_of_symbols);
void help(int argc, char **argv);
int select_game_settings(settings_t *size, FILE *file);
int info_variant();
int settings_input(settings_t *size, FILE *file);
void game_administration(settings_t size,  int **cur_gen, int **next_gen,
                         FILE *file, int manual_input);
int cur_filling(settings_t size, int **cur_gen, FILE *file, int manual_input);
int see_game_map(settings_t size, int **cur_gen);
void new_gen(settings_t size, int **cur_gen, int **next_gen);
int neighbors_num(settings_t size, int **cur_gen, int i, int j);
void copy_gen(settings_t size, int **cur_gen, int **next_gen);
void free_memory(settings_t size, int **cur_gen, int **next_gen);


int main(int argc, char **argv)
{
    FILE *file;
    settings_t size;
    int **cur_gen, **next_gen;
    int i, j;
    
    if (!(file = fopen("settings.txt", "r"))) {
        puts ("\n!! No such file in directory !!\n");
    }
    j = select_game_settings(&size, file);   
    cur_gen = (int**)calloc(size.height, sizeof(int*));
    for (i = 0; i < size.height; i++) {
        cur_gen[i] = (int*)calloc(size.width, sizeof(int));
    }
    next_gen = (int**)calloc(size.height, sizeof(int*));
    for (i = 0; i < size.height; i++) {
        next_gen[i] = (int*)calloc(size.width, sizeof(int));
    }

    help(argc,argv);
    game_administration(size, cur_gen, next_gen, file, j);
    
    fclose(file);
    return 0;
}


void game_administration(settings_t size, int **cur_gen, int **next_gen,
                         FILE *file, int manual_input)
{   int i = 0;
    cur_filling(size, cur_gen, file, manual_input);
    see_game_map(size, cur_gen);
    for (i = 0; i < size.gen_number; i++) {
        new_gen(size, cur_gen, next_gen);
        copy_gen(size, cur_gen, next_gen);
        see_game_map(size, cur_gen);
    }
    puts ("\n ------ RESALT ------");
    see_game_map(size, cur_gen);
    free_memory(size, cur_gen, next_gen);
}

int cur_filling(settings_t size, int **cur_gen, FILE *file, int manual_input)
{
    int i, j;
    for (i = 0; i < size.height; i++) {
        if (manual_input == 1) {
            for (j = 0; j < size.width; j++) {
                cur_gen[i][j] = getc(file) - '0';
            }
            getc(file);
        }
        else {
            puts("\nnew line:");
            for (j = 0; j < size.width; j++) {
                cur_gen[i][j] = int_input("element", 0, 1, stdin);
            }
        }
    }
    return 1;
}

int see_game_map(settings_t size, int **cur_gen)
{
    int i, j;
    puts("\n-----------------------------------------------");
    for (i = 0; i < size.height; i++) {
        for (j = 0; j < size.width; j++) {
            if(cur_gen[i][j]) {
                printf("o");
            }
            else {
                printf(" ");
            }
        }
        puts("");
    }  
    return 1; 
}

void new_gen(settings_t size, int **cur_gen, int **next_gen)
{
    int i, j, number;
    for (i = 0; i < size.height; i++) {
        for (j = 0; j < size.width; j++) {
            number = neighbors_num(size, cur_gen, i, j);
            if (number == 3 || (number == 2 && cur_gen[i][j])) {
                next_gen[i][j] = 1;
            }
            else {
                next_gen[i][j] = 0;
            }
        }
    }
}

 int neighbors_num(settings_t size, int **cur_gen, int i, int j)
 {
    int up = i - 1, down = i + 1, right = j + 1, left = j - 1, number;
    if (j == 0) {
        left = size.width - 1;
    }
    if (j == size. width - 1) {
        right = 0;
    }
    if (i == 0) {
        up = size.height - 1;
    }
    if (i == size.height - 1) {
        down = 0;
    }
    number = cur_gen[i][right] + cur_gen[up][j] + cur_gen[down][j] + 
          cur_gen[up][right] + cur_gen[up][left] + cur_gen[down][right] +
          cur_gen[down][left] + cur_gen[i][left];
    return number;
}

void copy_gen(settings_t size, int **cur_gen, int **next_gen) {
    int i, j;
    for (i = 0; i < size.height; i++) {
        for (j = 0; j < size.width; j++) {
            cur_gen[i][j] = next_gen[i][j];
        }
    } 
}

void free_memory(settings_t size, int **cur_gen, int **next_gen) {
    int i;
    for (i = 0; i < size.height; i++) {
        free(cur_gen[i]); 
        free(next_gen[i]);
    } 
    free(cur_gen);
    free(next_gen);
}

int settings_input(settings_t *size, FILE *file)
{
    size->width = int_input("\nenter width", 2, MAX_WIDTH, file);
    size->height = int_input("height", 2, MAX_LENGTH, file);
    size->gen_number = int_input("generation number", 1, MAX_GEN_NUMBER, file);
    printf("\nsize of game map:\n   width = %d\n   height = %d\n   gen_number = %d\n",
            size->width, size->height, size->gen_number);
    if (file == stdin) {
        return 0;
    }
    return 1;
}

int select_game_settings(settings_t *size, FILE *file)
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
            return settings_input(size, stdin);
        }
        else {
            return settings_input(size, file);
        }
    }
    else {
        return settings_input(size, stdin);
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

void help(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        file_output("README.txt");
        exit(0);
    }
}
