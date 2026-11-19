/**
 * Praktikum Informatik 1 MMXXVI
 *
 * @file config.h
 *
 * Beinhaltet globale Konfiguration.
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/** Definiert die Anzahl der Spalten des Spielfelds */
static const int WIDTH = 4;

/** Definiert die Anzahl der Zeilen des Spielfelds */
static const int HEIGHT = 4;

/** Definiert, ob die Tests ausgefuehrt werden. 1 ja, 0 nein */
static const int TEST = 0;

/** Definiert, ob die Ausgabe der Test ausfuehrlicher sein soll */
static const int VERBOSE = 1;

/**Definiert die Art eines Spielers */
static const int HUMAN = 1;
static const int COMPUTER = 2;

#endif /* CONFIG_H_ */
