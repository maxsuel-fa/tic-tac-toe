/* @file game.c
 * @brief Define functions to control and print the game
 * @author Group 1
 */
#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"

/*
 * @brief Given the informations of the game, print the game screen
 * @param game_inf the informations of the game
 */
void print_screen(Game_inf game_inf)
{
    clear_screen();
    printf("\t\t\t\t\t\t   +------------------------+-------------------------+\n");
    printf("\t\t\t\t\t\t   | Player: %-15s|  Enemy: %-16s|                         \n"\
           , game_inf.player_name, game_inf.enemy_name);
    printf("\t\t\t\t\t\t   | Symbol: %c              |  Symbol: %c              |\n"\
           , game_inf.player_symbol, game_inf.enemy_symbol);
    printf("\t\t\t\t\t\t   +------------------------+-------------------------+\n");
    printf("\t\t\t\t\t\t   |                                                  |\n");
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t 0 |        %c       |       %c       |       %c         |\n"\
           , game_inf.table[0], game_inf.table[1], game_inf.table[2]);
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t   | ---------------+---------------+---------------- |\n");
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t 1 |        %c       |       %c       |       %c         |\n"\
           , game_inf.table[3], game_inf.table[4], game_inf.table[5]);
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t   | ---------------+---------------+---------------- |\n");
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t 2 |        %c       |       %c       |       %c         |\n"\
           , game_inf.table[6], game_inf.table[7], game_inf.table[8]);
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t   |                |               |                 |\n");
    printf("\t\t\t\t\t\t   |                                                  |\n");
    printf("\t\t\t\t\t\t   +--------------------------------------------------+\n");
    printf("\t\t\t\t\t\t           A                B              C           \n");

}

/*
 * @brief Check which operational system is running and make the call 
 * to the respective clear comand
 */
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
