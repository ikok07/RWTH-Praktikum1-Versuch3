/**
 * Praktikum Informatik 1
 *
 *
 * @file othelloKI.c
 *
 * Stellt eine KI fuer das Spiel Othello zur Verfuegung
 */

#include "othelloKI.h"
#include <stdio.h>


extern int possibleMoves(const int board[HEIGHT][WIDTH], const int currentPlayer);
extern void executeMove(int board[HEIGHT][WIDTH], const int currentPlayer, const int posX, const int posY);
extern bool isValidMove(const int board[HEIGHT][WIDTH], const int currentPlayer, const int posX, const int posY);

bool computerMove(int board[HEIGHT][WIDTH], const int currentPlayer)
{
    if (possibleMoves(board,currentPlayer) == 0)
    {
        return false;
    }
    int lookahead[HEIGHT][WIDTH];
    int min_x = 0;
    int min_y = 0;
    int min = WIDTH * HEIGHT;

    for (int j = 0 ; j < HEIGHT; j++)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            // Spielfeld zuruecksetzen
            for (int cj = 0; cj < HEIGHT; cj++)
            {
                for (int ci = 0; ci < WIDTH; ci++)
                {
                    lookahead[cj][ci]=board[cj][ci];
                }
            }

            if (isValidMove(lookahead, currentPlayer, i, j))
            {
                executeMove(lookahead, currentPlayer, i, j);
                if (possibleMoves(lookahead, 3 - currentPlayer) < min)
                {
                    min=possibleMoves(lookahead, 3 - currentPlayer);
                    min_x = i;
                    min_y = j;
                }
            }
        }
    }

    executeMove(board, currentPlayer, min_x, min_y);
    printf("\nSpieler %d setzt auf %c%d\n", currentPlayer, (char)(min_x + 65), min_y + 1);

    return true;
}
