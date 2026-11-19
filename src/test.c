/**
 * Praktikum Informatik 1
 *
 * @file test.c
 *
 * Stellt Funktionen zum Testen der Spielfunktionen zur Verfuegung
 */

#include "test.h"
#include "config.h"
#include <stdbool.h>
#include <stdio.h>

/*
 * Deklaration der in den Tests verwendeten Funktionen.
 * Dadurch weiss der Compiler, das es sich bei den Namen
 * um Funktionsaufrufe handelt, die in einer anderen Datei
 * definiert sind (extern).
 */
extern void showBoard(const int board[HEIGHT][WIDTH]);
extern int winner(const int board[HEIGHT][WIDTH]);
extern bool onBoard(const int posX, const int posY);
extern bool isValidMove(const int board[HEIGHT][WIDTH], const int player,
                        const int posX, const int posY);
extern void executeMove(int board[HEIGHT][WIDTH], const int player,
                        const int posX, const int posY);
extern int possibleMoves(const int board[HEIGHT][WIDTH], const int player);

/*
 * Utility functions to avoid boilerplate code
 */
static void printTestInit(char *fnName, int testNumber);

/**
 * @brief Funktion zum Testen der winner() Funktion.
 *
 * @param inputBoard Das zu testende Spielfeld.
 * @param expected Der erwartete Gewinner.
 * @param testNumber Nummer des laufenden Tests
 * @return True wenn der berechnete Gewinner und der erwartete Gewinner
 * uebereinstimmen. False ansonsten.
 */
bool winnerTest(const int inputBoard[HEIGHT][WIDTH], const int expected,
                const int testNumber) {
  printTestInit((char *)"winner", testNumber);
  int result = winner(inputBoard);
  if (result == expected) {
    printf("Test %d bestanden!\n\n", testNumber + 1);
    return true;
  } else {
    printf("Test %d fehlgeschlagen\n\n", testNumber + 1);
    if (VERBOSE == 1) {
      showBoard(inputBoard);
      printf("\nBerechnetes Ergebnis: %d\nRichtiges Ergebnis: %d\n\n", result,
             expected);
    }
    return false;
  }
}

/**
 * @brief Funktion zum Testen der onBoard() Funktion
 *
 * @param posX Index Spalte
 * @param posY Index Zeile
 * @param expected Das erwartete Ergebnis
 * @param testNumber Nummer des laufenden Tests
 * @return True wenn Test bestanden, ansonsten false
 */
bool onBoardTest(const int posX, const int posY, const bool expected,
                 const int testNumber) {
  printTestInit((char *)"onBoard", testNumber);
  // Hier erfolgt jetzt Ihre Implementierung ...
  bool result = onBoard(posX, posY);
  if (result == expected) {
    printf("Test %d bestanden!\n\n", testNumber + 1);
    return true;
  } else {
    printf("Test %d fehlgeschlagen\n\n", testNumber + 1);
    if (VERBOSE == 1) {
      printf("\nBerechnetes Ergebnis: %d\nRichtiges Ergebnis: %d\n\n", result,
             expected);
    }
    return false;
  }

  return 0;
}

bool isValidMoveTest(const int inputBoard[HEIGHT][WIDTH], const int player,
                     const int posX, const int posY, const bool expected,
                     const int testNumber) {
  // ueberprueft, ob der Zug fuer eine gegebene Position gueltig ist
  // wenn VERBOSE gleich 1 wird zusaetzlich das Spielfeld und die ungueltige
  // Position ausgegeben
  //
  // Hier erfolgt jetzt Ihre Implementierung ...

  printTestInit((char *)"isValidMove", testNumber);
  bool result = isValidMove(inputBoard, player, posX, posY);
  if (result == expected) {
    printf("Test %d bestanden!\n\n", testNumber + 1);
    return true;
  } else {
    printf("Test %d fehlgeschlagen\n\n", testNumber + 1);
    if (VERBOSE == 1) {
      showBoard(inputBoard);
      printf("\nplayer = %c; X = %c; Y = %d\n", player == 1 ? 'X' : 'O',
             posX + 'A', posY + 1);
      printf("\nBerechnetes Ergebnis: %d\nRichtiges Ergebnis: %d\n\n", result,
             expected);
    }
    return false;
  }

  return 0;
}

bool executeMoveTest(int inputBoard[HEIGHT][WIDTH],
                     const int resultBoard[HEIGHT][WIDTH], const int player,
                     const int posX, const int posY, const int testNumber) {
  // ueberprueft, ob fuer ein gegebenes Spielfeld der Zug fuer einen gegebenen
  // Spieler korrekt ausgefuehrt wird wenn VERBOSE gleich 1 werden zusaetzlich
  // beide Spielfelder ausgegeben
  //
  // Hier erfolgt jetzt Ihre Implementierung ...

  printTestInit((char *)"executeMove", testNumber);
  executeMove(inputBoard, player, posX, posY);

  bool result = true;

  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      if (inputBoard[row][col] != resultBoard[row][col]) {
        result = false;
        break;
      }
    }
  }

  if (result) {
    printf("Test %d bestanden!\n\n", testNumber + 1);
    return true;
  } else {
    printf("Test %d fehlgeschlagen\n\n", testNumber + 1);
    if (VERBOSE == 1) {
      printf("Result board:\n");
      showBoard(inputBoard);
      printf("Expected board:\n");
      showBoard(resultBoard);
      printf("\nplayer = %c; X = %c; Y = %d\n", player == 1 ? 'X' : 'O',
             posX + 'A', posY + 1);
    }
    return false;
  }

  return 0;
}

bool possibleMovesTest(const int inputBoard[HEIGHT][WIDTH], const int player,
                       const int expected, const int testNumber) {
  // ueberprueft, ob alle moeglichen Zuege fuer einen Spieler gefunden werden
  // wenn VERBOSE gleich 1 wird zusaetzlich das Spielfeld, der berechnete
  // falsche und der richtige Wert ausgegeben
  //
  // Hier erfolgt jetzt Ihre Implementierung ...

  printTestInit((char *)"possibleMoves", testNumber);
  int result = possibleMoves(inputBoard, player);

  if (result == expected) {
    printf("Test %d bestanden!\n\n", testNumber + 1);
    return true;
  } else {
    printf("Test %d fehlgeschlagen\n\n", testNumber + 1);
    if (VERBOSE == 1) {
      showBoard(inputBoard);
      printf("\nBerechnetes Ergebnis: %d\nRichtiges Ergebnis: %d\n\n", result,
             expected);
    }
    return false;
  }

  return 0;
}

/**
 * @brief Funktion to print the initial header of each test
 *
 * @param fnName Name of the function
 * @param testNumber Active test number
 */
void printTestInit(char *fnName, int testNumber) {
  printf("Fuehre Test %d fuer '%s()' aus ...\n", testNumber + 1, fnName);
  printf("----------------------------------\n\n");
}

/**
 * @brief Funktion, die alle Tests ausfuehrt
 *
 * @return True, wenn alle Tests bestanden wurden, ansonsten false
 */
bool runAllTests() {
  bool overallResult = true;

  // Jeder Test steht in einem eigenen Block {}, damit es keine Namenskonflikte
  // gibt z.B. inputBoard oder expectedResult

  // ---------- TESTE GEWINNER ---------- //
  {
    int inputBoard[3][8][8] = {{{1, 2, 1, 2, 1, 2, 1, 2},
                                {1, 2, 1, 2, 1, 2, 1, 2},
                                {1, 2, 1, 2, 1, 2, 1, 2},
                                {1, 2, 1, 2, 1, 2, 1, 2},
                                {1, 2, 1, 2, 1, 2, 1, 2},
                                {1, 2, 1, 2, 1, 2, 1, 2},
                                {1, 2, 1, 2, 1, 2, 1, 2},
                                {1, 2, 1, 2, 1, 2, 1, 2}},

                               {{1, 1, 2, 1, 1, 2, 1, 1},
                                {2, 1, 1, 2, 1, 1, 2, 1},
                                {1, 2, 1, 1, 2, 1, 1, 2},
                                {1, 1, 2, 1, 1, 2, 1, 1},
                                {2, 1, 1, 2, 1, 1, 2, 1},
                                {1, 2, 1, 1, 2, 1, 1, 2},
                                {1, 1, 2, 1, 1, 2, 1, 1},
                                {2, 1, 1, 2, 1, 1, 2, 1}},

                               {{1, 2, 2, 1, 2, 2, 1, 2},
                                {2, 1, 2, 2, 1, 2, 2, 1},
                                {2, 2, 1, 2, 2, 1, 2, 2},
                                {1, 2, 2, 1, 2, 2, 1, 2},
                                {2, 1, 2, 2, 1, 2, 2, 1},
                                {2, 2, 1, 2, 2, 1, 2, 2},
                                {1, 2, 2, 1, 2, 2, 1, 2},
                                {2, 1, 2, 2, 1, 2, 2, 1}}};

    int expectedResult[3] = {0, 1, 2};

    for (int i = 0; i < 3; i++) {
      bool tmpResult = winnerTest(inputBoard[i], expectedResult[i], i);
      if (overallResult == true && tmpResult == false) {
        overallResult = false;
      }
    }

    printf("Ende des Tests fuer 'winner()'\n\n");
  }

  // ---------- TESTE POSITION IM FELD---------- //
  {
    int position[6][2] = {{2, 3},  {0, 8}, {-1, 7},
                          {2, -1}, {8, 5}, {-1, 8}}; // posX, posY
    bool expectedResult[6] = {true, false, false, false, false, false};

    for (int i = 0; i < 6; i++) {
      // Hier erfolgt jetzt Ihre Implementierung (entsprechende Testfunktion
      // aufrufen) ...
      bool tmpResult =
          onBoardTest(position[i][0], position[i][1], expectedResult[i], i);
      if (overallResult == true && tmpResult == false) {
        overallResult = false;
      }
    }

    printf("Ende des Tests fuer 'onBoard()'\n\n");
  }

  // ---------- TESTE ZUG GUELTIG ---------- //
  {
    int inputBoard[7][8][8] = {{{1, 0, 2, 0, 0, 1, 1, 1},
                                {0, 0, 2, 0, 0, 0, 0, 1},
                                {0, 0, 0, 0, 0, 1, 2, 2},
                                {2, 2, 0, 2, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 2, 2, 0},
                                {0, 0, 0, 2, 1, 1, 0, 2},
                                {1, 0, 0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 1, 0, 1}},

                               {{1, 0, 2, 0, 0, 1, 1, 1},
                                {0, 0, 2, 0, 0, 1, 0, 0},
                                {0, 0, 2, 0, 0, 2, 1, 1},
                                {0, 0, 0, 2, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 2, 2, 0},
                                {0, 0, 0, 2, 1, 1, 0, 2},
                                {1, 0, 0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 1, 0, 1}},

                               {{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 1, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 2, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0}},

                               {{0, 1, 0, 0, 2, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 1, 0},
                                {2, 0, 1, 2, 0, 2, 0, 0},
                                {0, 2, 0, 2, 2, 2, 2, 2},
                                {0, 0, 0, 0, 0, 0, 0, 1},
                                {1, 0, 0, 0, 0, 2, 2, 2},
                                {0, 2, 0, 0, 0, 0, 0, 0},
                                {0, 1, 0, 1, 1, 1, 0, 0}},

                               {{2, 1, 0, 0, 2, 1, 1, 1},
                                {0, 2, 0, 0, 0, 0, 0, 0},
                                {1, 0, 0, 2, 0, 0, 0, 1},
                                {0, 1, 1, 1, 0, 1, 0, 0},
                                {1, 0, 0, 1, 1, 0, 0, 2},
                                {0, 0, 0, 0, 0, 0, 0, 1},
                                {1, 1, 0, 0, 0, 0, 2, 0},
                                {1, 1, 2, 0, 0, 2, 2, 1}},

                               {{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 1, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0}},

                               {
                                   {1, 2, 2, 2, 2, 2, 2, 2},
                                   {1, 2, 1, 1, 2, 2, 2, 2},
                                   {1, 1, 1, 2, 2, 2, 2, 2},
                                   {1, 1, 1, 2, 2, 2, 2, 2},
                                   {1, 1, 1, 1, 2, 2, 2, 2},
                                   {1, 1, 1, 0, 2, 2, 2, 2},
                                   {1, 0, 0, 0, 2, 0, 0, 2},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                               }};

    int player[7] = {1, 2, 2, 1, 2, 1, 1};
    int position[7][2] = {{2, 3}, {0, 3}, {4, 3}, {3, 4},
                          {3, 5}, {3, 4}, {5, 7}}; // posX, posY
    bool expectedResult[7] = {false, false, false, true, true, false, false};

    for (int i = 0; i < 7; i++) {
      // Hier erfolgt jetzt Ihre Implementierung (entsprechende Testfunktion
      // aufrufen) ...
      bool tmpResult = isValidMoveTest(inputBoard[i], player[i], position[i][0],
                                       position[i][1], expectedResult[i], i);

      if (overallResult == true && tmpResult == false) {
        overallResult = false;
      }
    }

    printf("Ende des Tests fuer 'isValidMove()'\n\n");
  }

  // ---------- TESTE ZUG AUSFUEHREN ---------- //
  {
    int inputBoard[10][8][8] = {{{0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 1, 2, 2},
                                 {2, 2, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}},

                                {{0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 2, 1, 1},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}},

                                {{0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 1, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 2, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}},

                                {{0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 1, 0},
                                 {0, 0, 0, 2, 0, 2, 0, 0},
                                 {0, 0, 0, 2, 2, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}},

                                {{0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 2, 0, 0, 0, 0},
                                 {0, 0, 0, 1, 0, 1, 0, 0},
                                 {0, 0, 0, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}},

                                {{0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 1, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 1, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}},

                                {{0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 1, 0, 0, 1, 0},
                                 {0, 0, 0, 2, 0, 2, 0, 0},
                                 {0, 0, 0, 2, 2, 0, 0, 0},
                                 {0, 1, 2, 0, 2, 2, 1, 0},
                                 {0, 0, 0, 2, 2, 0, 0, 0},
                                 {0, 0, 0, 1, 0, 1, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}},

                                {{0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 2, 0, 0},
                                 {0, 0, 0, 0, 1, 0, 0, 0},
                                 {0, 0, 0, 1, 0, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 1, 1, 0},
                                 {0, 0, 1, 0, 0, 0, 0, 0},
                                 {0, 0, 2, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}},

                                {{0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 1, 0, 0, 0, 0, 0, 0},
                                 {0, 1, 0, 0, 0, 0, 2, 1},
                                 {1, 0, 1, 1, 2, 0, 0, 0},
                                 {0, 0, 1, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 1, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}},

                                {{0, 0, 0, 0, 0, 1, 0, 1},
                                 {0, 0, 0, 0, 0, 2, 2, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 2, 2, 0, 0},
                                 {0, 0, 0, 1, 0, 1, 0, 0},
                                 {0, 0, 2, 0, 0, 2, 0, 0},
                                 {0, 1, 0, 0, 0, 1, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0}}};

    int resultBoard[10][8][8] = {{{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 1, 2, 2},
                                  {2, 2, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}},

                                 {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 2, 1, 1},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}},

                                 {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 1, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 2, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}},

                                 {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 1, 0},
                                  {0, 0, 0, 2, 0, 1, 0, 0},
                                  {0, 0, 0, 2, 1, 0, 0, 0},
                                  {0, 0, 0, 1, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}},

                                 {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 2, 0, 0, 0, 0},
                                  {0, 0, 0, 2, 0, 1, 0, 0},
                                  {0, 0, 0, 2, 1, 0, 0, 0},
                                  {0, 0, 0, 2, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}},

                                 {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 1, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 1, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}},

                                 {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 1, 0, 0, 1, 0},
                                  {0, 0, 0, 1, 0, 1, 0, 0},
                                  {0, 0, 0, 1, 1, 0, 0, 0},
                                  {0, 1, 1, 1, 1, 1, 1, 0},
                                  {0, 0, 0, 1, 1, 0, 0, 0},
                                  {0, 0, 0, 1, 0, 1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}},

                                 {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 2, 0, 0},
                                  {0, 0, 0, 0, 2, 0, 0, 0},
                                  {0, 0, 0, 2, 0, 0, 0, 0},
                                  {0, 0, 2, 1, 1, 1, 1, 0},
                                  {0, 0, 2, 0, 0, 0, 0, 0},
                                  {0, 0, 2, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}},

                                 {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 0, 0, 2, 1},
                                  {1, 2, 2, 2, 2, 0, 0, 0},
                                  {0, 0, 1, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 1, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}},
                                 {{0, 0, 0, 0, 0, 1, 0, 1},
                                  {0, 0, 0, 0, 0, 1, 1, 0},
                                  {0, 0, 0, 0, 0, 1, 0, 0},
                                  {0, 0, 0, 0, 1, 1, 0, 0},
                                  {0, 0, 0, 1, 0, 1, 0, 0},
                                  {0, 0, 2, 0, 0, 2, 0, 0},
                                  {0, 1, 0, 0, 0, 1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0}}};

    int player[10] = {0, 0, 0, 1, 2, 0, 1, 2, 2, 1};
    int position[10][2] = // eine andere, moegliche Darstellung
        {                 // der gegebenen Positionen posX, posY
         {0, 0}, {0, 0}, {0, 0}, {3, 4}, {3, 5},
         {0, 0}, {3, 4}, {2, 4}, {1, 4}, {5, 2}};

    for (int i = 0; i < 10; i++) {
      // Hier erfolgt jetzt Ihre Implementierung (entsprechende Testfunktion
      // aufrufen) ...
      bool tmpResult = executeMoveTest(inputBoard[i], resultBoard[i], player[i],
                                       position[i][0], position[i][1], i);

      if (overallResult == true && tmpResult == false) {
        overallResult = false;
      }
    }

    printf("Ende des Tests fuer 'executeMove()'\n\n");
  }

  // ---------- TESTE MOEGLICHE ZUEGE ---------- //
  {
    int inputBoard[2][8][8] = {{{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 1, 2, 0, 0, 0},
                                {0, 0, 0, 2, 1, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0}},

                               {{0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 2, 1, 0, 0, 0},
                                {0, 0, 0, 2, 1, 1, 0, 0},
                                {0, 0, 0, 2, 1, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0}}};

    int player[2] = {1, 1};
    int expectedResult[2] = {4, 5};

    for (int i = 0; i < 2; i++) {
      // Hier erfolgt jetzt Ihre Implementierung (entsprechende Testfunktion
      // aufrufen) ...

      bool tmpResult =
          possibleMovesTest(inputBoard[i], player[i], expectedResult[i], i);

      if (overallResult == true && tmpResult == false) {
        overallResult = false;
      }
    }

    printf("Ende des Tests fuer 'possibleMoves()'\n\n");
  }

  return overallResult;
}
