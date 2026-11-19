/**
 * Praktikum Informatik 1 
 * 
 *
 * @file othelloKI.h
 *
 * Stellt eine KI fuer das Spiel Othello zur Verfuegung
 */

#ifndef OTHELLOKI_H_
#define OTHELLOKI_H_

#include <stdbool.h>
#include "config.h"

/**
 * Eine Funktion, die eine KI fuer das Spiel Othello zur Verfuegung stellt
 *
 * @param board Das aktuelle Spielfeld
 * @param currentPlayer Der aktuelle Spieler
 * @return True wenn der Zug ausgefuehrt wurde. False wenn kein Zug moeglich ist.
 */
bool computerMove(int board[HEIGHT][WIDTH], const int currentPlayer);

#endif /* OTHELLOKI_H_ */
