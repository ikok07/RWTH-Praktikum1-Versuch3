/**
 * Praktikum Informatik 1
 *
 *
 * @file othello.c
 *
 * Die Funktionen fuer das Spiel Othello
 */

/**
 * @mainpage Othello
 *
 * Dokumentation des Spiels Othello im Rahmen des Praktikums Informatik 1.
 *
 */

#include "config.h"
#include "othelloKI.h"
#include "test.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Utility functions to avoid boilerplate code
 */
static void moveCursor(int dirX, int dirY, int curX, int curY, int offset,
                       int *outX, int *outY);

static bool (*getPlayerFn(int playerType))(int board[HEIGHT][WIDTH],
                                           const int currentPlayer);

/**
 * @brief Funktion zur ersten Initialisierung eines neuen Spielfelds
 *
 * Diese Funktion fuellt ein existierendes Spielfeld mit Nullen und erzeugt
 * die Startaufstellung.
 *
 * @param board Spielfeld, das initialisiert wird
 */
void initializeBoard(int board[HEIGHT][WIDTH]) {
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      board[j][i] = 0;
    }
  }
  board[HEIGHT / 2 - 1][WIDTH / 2 - 1] = 1;
  board[HEIGHT / 2][WIDTH / 2 - 1] = 2;
  board[HEIGHT / 2 - 1][WIDTH / 2] = 2;
  board[HEIGHT / 2][WIDTH / 2] = 1;
}

/**
 * @brief Ausgabe des Spielfelds auf der Konsole
 *
 * Ausgabe des aktuellen Spielfelds, 0 bedeutet leeres Feld, 1 ist Spieler 1 und
 * 2 ist Spieler2 Kreuze symbolisieren Spieler 1, waehrend Kreise Spieler 2
 * symbolisieren
 *
 *  @param board  Spielfeld, das ausgeben wird
 */
void showBoard(const int board[HEIGHT][WIDTH]) {
  printf("   | ");

  // Start bei ASCII 65 = A
  for (int i = 65; i < 65 + WIDTH; ++i)
    printf("%c | ", (char)i);

  printf("\n");

  for (int j = 0; j < HEIGHT; ++j) {
    for (int i = 0; i < WIDTH; ++i) {
      printf("---+");
    }
    printf("---+\n");

    printf(" %d |", j + 1);
    for (int i = 0; i < WIDTH; ++i) {
      switch (board[j][i]) {
      case 0:
        printf("   ");
        break;
      case 1:
        printf(" X ");
        break;
      case 2:
        printf(" O ");
        break;
      default:
        printf("Unzulaessige Daten im Spielfeld!\n");
        printf("Abbruch .... \n");
        exit(0);
        break;
      }
      printf("|");
    }; // for i
    printf("\n");
  } // for j
}

/**
 * @brief Prueft, wer Gewinner ist
 *
 * Zaehlt alle Steine auf dem Feld
 *
 * @param board Aktuelles Spielfeld, fuer das der Gewinner ermittelt wird
 * @return winner
 */
int winner(const int board[HEIGHT][WIDTH]) {
  int counterPlayer1 = 0;
  int counterPlayer2 = 0;

  for (int j = 0; j < HEIGHT; ++j) {
    for (int i = 0; i < WIDTH; ++i) {
      if (board[j][i] == 1) {
        ++counterPlayer1;
      }
      if (board[j][i] == 2) {
        ++counterPlayer2;
      }
    }
  }

  if (counterPlayer1 == counterPlayer2) {
    return 0;
  }
  if (counterPlayer1 < counterPlayer2) {
    return 2;
  } else {
    return 1;
  }
}

/**
 * @brief Ueberprueft fuer zwei Indizes, ob sie auf dem Spielfeld sind
 *
 * @param posX Index fuer die Spalte
 * @param posY Index fuer die Zeile
 * @return true, wenn Spalte und Zeile innerhalb des Spielfelds sind, sonst
 * false
 */
bool onBoard(const int posX, const int posY) {
  // Hier erfolgt jetzt Ihre Implementierung ...
  return (posX >= 0 && posX < WIDTH) && (posY >= 0 && posY < HEIGHT);
}

/**
 * @brief Ueberprueft fuer zwei Indizes, ob der Zug gueltig ist
 *
 *  Ueberprueft, ob auf einem benachbarten Feld ein gegnerischer Stein liegt.
 *  Wenn ja, wird diese Richtung solange untersucht, bis ein eigener Stein
 *  gefunden wird. Wird vorher der Spielfeldrand erreicht oder ein leeres Feld
 *  gefunden, wird false zurueckgegeben, sonst true
 *
 * @param board Das aktuelle Spielfeld
 * @param currentPlayer Der aktuelle Spieler
 * @param posX Zu ueberpruefende Spalte
 * @param posY Zu ueberpruefende Zeile
 * @return
 */
bool isValidMove(const int board[HEIGHT][WIDTH], const int currentPlayer,
                 const int posX, const int posY) {
  int opponent =
      3 - currentPlayer; // dasselbe wie: if currentPlayer == 1 -> opponent = 2
                         //               if currentPlayer == 2 -> opponent = 1

  if (board[posY][posX] != 0) // ist das Feld leer?
  {
    return false;
  }

  // Alle Richtungen ueberpruefen bis erster gueltiger Zug gefunden
  for (int row = -1; row <= 1; row++) {
    for (int col = -1; col <= 1; col++) {
      // Hier erfolgt jetzt Ihre Implementierung ...

      if (row == 0 && col == 0) {
        // The same position cannot be a valid one
        continue;
      }

      // Check if position is occupied by the opponent
      if (board[posY + row][posX + col] != opponent) {
        // No opponent has occupied the adjacent position
        continue;
      }

      // Look for the next current player position
      int offset = 0;

      while (true) {
        // Check the next position
        offset++;

        int newX, newY;
        moveCursor(col, row, posX, posY, offset, &newX, &newY);

        if (!onBoard(newX, newY)) {
          // Position is outside the board
          break;
        };

        if (board[newY][newX] == 0) {
          // Position is empty
          break;
        };

        if (board[newY][newX] == currentPlayer) {
          // Current player position found
          return true;
        }
      }
    }
  }
  return false;
}

/**
 * @brief Funktion, die einen Zug ausfuehrt
 *
 * @param board Das aktuelle Spielfeld
 * @param currentPlayer Der aktuelle Spieler
 * @param posX Die aktuelle Spalte
 * @param posY Die aktuelle Zeile
 */
void executeMove(int board[HEIGHT][WIDTH], const int currentPlayer,
                 const int posX, const int posY) {
  int opponent = 3 - currentPlayer;

  // Alle Richtungen bearbeiten
  for (int row = -1; row <= 1; row++) {
    for (int col = -1; col <= 1; col++) {
      // aehnlich wie die Funktion isValidMove(), aber stellen Sie sicher, das
      // alle gegnerischen Steine in allen Richtungen in Ihre eigenen Steine
      // umgewandelt werden
      //
      // Hier erfolgt jetzt Ihre Implementierung ...

      if (!onBoard(posX + col, posY + row)) {
        // Position outside the board
        continue;
      }

      if (board[posY + row][posX + col] != opponent) {
        // The position is not occupied by the opponent
        continue;
      }

      int offset = 0;
      int newX = 0, newY = 0;

      /*
        This indicates whether the formed straight line
        is fully enclosed (currentPlayer - opponent - currentPlayer)
      */
      bool invalidLine = 0;

      // Find the end of the straight line
      while (!invalidLine) {
        offset++;

        moveCursor(col, row, posX, posY, offset, &newX, &newY);

        if (!onBoard(newX, newY)) {
          // Position is outside the board
          invalidLine = 1;
          break;
        };

        if (board[newY][newX] == opponent) {
          // Position occupied by opponent => Look further
          continue;
        } else if (board[newY][newX] != currentPlayer) {
          // The position is neither occupied by the opponnent nor the current
          // player
          invalidLine = 1;
          break;
        }

        // Position is occupied by current player
        break;
      }

      // Look in other direction
      if (invalidLine)
        continue;

      while (true) {
        offset--;

        moveCursor(col, row, posX, posY, offset, &newX, &newY);

        if (board[newY][newX] == 0) {
          // Position is empty => We are done
          break;
          ;
        }

        // Change positions' owner to current player
        board[newY][newX] = currentPlayer;
      }
    }
  }

  // Change current possitions' owner to current player
  board[posY][posX] = currentPlayer;
}

int possibleMoves(const int board[HEIGHT][WIDTH], const int currentPlayer) {
  // Hier erfolgt jetzt Ihre Implementierung ...
  int sum = 0;
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      sum += isValidMove(board, currentPlayer, col, row);
    }
  }

  return sum;
}

bool humanMove(int board[HEIGHT][WIDTH], const int currentPlayer) {
  if (possibleMoves(board, currentPlayer) == 0) {
    return false;
  }

  int posX;
  int posY;
  char playerSymbol;
  if (currentPlayer == 1) {
    playerSymbol = 'X';
  } else {
    playerSymbol = 'O';
  }

  while (true) {
    char input[10];
    printf("\nDu bist %c. Dein Zug (z.B. A1, a1): ", playerSymbol);
    scanf("%9s", input);
    posX = (int)input[0] % 32 - 1;
    posY = (int)input[1] - 49;

    if (isValidMove(board, currentPlayer, posX, posY)) {
      // accept turn;
      break;
    } else {
      printf("\nUngueltige Eingabe !\n");
    }
  }

  executeMove(board, currentPlayer, posX, posY);
  printf("\nSpieler %d setzt auf %c%d\n", currentPlayer, (char)(posX + 65),
         posY + 1);

  return true;
}

void play(const int playerType[2]) {
  int board[HEIGHT][WIDTH];

  // Erzeuge Startaufstellung
  initializeBoard(board);

  int currentPlayer = 1;

  // This variable tracks whether a user has no more moves available
  int blockedPlayers[2] = {0, 0};

  showBoard(board);

  // solange noch Zuege bei einem der beiden Spieler moeglich sind
  //
  // Hier erfolgt jetzt Ihre Implementierung ...

  while (!blockedPlayers[0] || !blockedPlayers[1]) {
    // bool playerBlocked = blockedPlayers[currentPlayer - 1];
    // if (!playerBlocked &&
    if (!getPlayerFn(playerType[currentPlayer - 1])(board, currentPlayer)) {
      blockedPlayers[currentPlayer - 1] = 1;
    };
    currentPlayer = 3 - currentPlayer;
    showBoard(board);
  }

  switch (winner(board)) {
  // Hier erfolgt jetzt Ihre Implementierung ...
  case 0:
    printf("\nNobody wins!\n");
    break;
  case 1:
    printf("\nPlayer 1 wins!\n");
    break;
  case 2:
    printf("\nPlayer 2 wins!\n");
    break;
  }
}

/**
 * @brief Moves the current cursor "offset" positions in the desired
 * direction (X, Y)
 *
 * @param dirX Direction in X-Axis
 * @param dirY Direction in Y-Axis
 * @param curX Current X-Coordinate
 * @param curY Current Y-Coordinate
 * @param offset Offset to move
 * @param outX Variable to save the new X-Coordinate
 * @param outY Variable to save the new Y-Coordinate
 */
void moveCursor(int dirX, int dirY, int curX, int curY, int offset, int *outX,
                int *outY) {
  bool rowStatic = dirY == 0;
  bool colStatic = dirX == 0;
  bool isPerpendicular = rowStatic || colStatic;

  if (isPerpendicular) {
    if (rowStatic) {
      *outX = curX + dirX + (dirX * offset);
      *outY = curY + dirY;
    } else {
      // colStatic == true
      *outX = curX + dirX;
      *outY = curY + dirY + (dirY * offset);
    }
  } else {
    // Position is diagonal
    *outX = curX + dirX + (dirX * offset);
    *outY = curY + dirY + (dirY * offset);
  }
}

/**
 * @brief Gets the appropriate function depending on the current players' type
 *
 * @param playerType Type of the player
 * @return
 */
bool (*getPlayerFn(int playerType))(int board[HEIGHT][WIDTH],
                                    const int currentPlayer) {
  if (playerType == HUMAN) {
    return humanMove;
  }
  return computerMove;
};

int main() {
  if (TEST == 1) {
    bool overallResult = runAllTests();
    if (overallResult == true) {
      printf("ALLE TESTS BESTANDEN!\n");
    } else {
      printf("MINDESTENS EIN TEST IST FEHLGESCHLAGEN!\n");
      exit(1);
    }
    printf("\n\n");
  }

  // Die folgenden drei Zeilen werden auskommentiert oder geloescht, nachdem Sie
  // die Funktion play() implementiert haben (waeren sonst doppelt)
  // int board[HEIGHT][WIDTH];

  // initializeBoard(board);

  // showBoard(board);

  // Hier erfolgt jetzt Ihre Implementierung ...

  int playerType[2];

  bool shouldContinue = false;
  do {
    printf("\n------ GAME START ------\n");

    int typeInput;
    printf("Choose player 1 (HUMAN = 1, COMPUTER = 2):");
    scanf("%d", &typeInput);
    playerType[0] = typeInput < 0 || typeInput > COMPUTER ? HUMAN : typeInput;

    printf("Choose player 2 (HUMAN = 1, COMPUTER = 2):");
    scanf("%d", &typeInput);
    playerType[1] = typeInput < 0 || typeInput > COMPUTER ? HUMAN : typeInput;

    play(playerType);

    printf("\n------ GAME END ------\n");

    printf("\n\n Do you want to play another game? (y/n) \n\n");
    char input;
    scanf(" %c", &input);

    shouldContinue = input == 'y';
  } while (shouldContinue);

  return 0;
}
