/*
 * @file game.h
 * @brief Define the signature of the functions that compose the game, as well
 * as the struct that holds the informations of the players and the current sta-
 * te of the game
 * @author Group 1
 */
#ifndef GAME_H
#define GAME_H

// Define the max size a name can have
#define NAME_SIZE 14

/* Struct that holds the informations of the players and the current state of 
 * the game
 */
typedef struct
{
    char table[10];
    char player_name[NAME_SIZE];
    char player_symbol;
    char enemy_name[NAME_SIZE];
    char enemy_symbol;
} Game_inf;

void print_screen(Game_inf);
void clear_screen(void);
#endif
