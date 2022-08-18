/* JEANNE-ROSE Méven
    04/05/22
    fonctions.h
    Performs calculations on array and display in the console
*/

#ifndef _FONCTION_H
#define _FONCTION_H

#include <stdint.h>
#include <stdio.h>

/* Structure représentant une case contenant une valeur, nombre de possibilités, etc.*/
struct Cellule{
  uint16_t valeurs_possibles : 9;
  uint16_t nombre_possibilites : 7;
  uint8_t valeur;
  uint8_t padding;
};

extern uint8_t ti [9][9];
extern struct Cellule tableau[9][9];

void main_console();

/********DISPLAY*******/

/*Display Stuct Cellule array values in the console*/
void Affichage(const struct Cellule[9][9]);

/*Init struct Cellule array with an array */
void init_array(struct Cellule[9][9], const uint8_t tab[9][9]);

/*calculate and Fill "valeurs_possibles" field of the struct
@return minimum number of possibilities*/
uint8_t calcul_valeurs_possibles(struct Cellule[9][9], uint8_t *ligne, uint8_t *colonne);

/*Update number of possibilities thanks to number of bits set in "valeurs_possibles" field
@return number of possibilities
*/
uint8_t update_nb_possibilites(struct Cellule);

/*Compute possible value of each element line by line
@return minimum number of possibility*/
void calcul_valeurs_possibles_selon_ligne(struct Cellule[9][9], struct Cellule*, uint8_t*, uint8_t*);

/*Compute possible value of each element column by column
@return minimum number of possibility*/
void calcul_valeurs_possibles_selon_colonne(struct Cellule[9][9], struct Cellule*, uint8_t*, uint8_t*);

/*Compute possible value of each element block by block
@return minimum number of possibility*/
void calcul_valeurs_possibles_selon_block(struct Cellule[9][9], struct Cellule*, uint8_t*, uint8_t*);

/*compute possible value of a cell following line elements value
@return number of possibilities*/
uint8_t calcul_valeurs_possibles_cellule_selon_ligne(uint8_t ligne, uint8_t col, struct Cellule[9][9]);

/*compute possible value of a cell following column elements value
@return number of possibilities*/
uint8_t calcul_valeurs_possibles_cellule_selon_colonne(uint8_t ligne, uint8_t col, struct Cellule[9][9]);

/*Compute possible value of cells inside block
@return min number of possibilities of the corresponding block*/
uint8_t update_block(uint8_t block_number,uint8_t *ligne, uint8_t *colonne, struct Cellule array[9][9]);

/*display bits field "valeurs possibles"*/
void affiche_valeurs_possibles(const struct Cellule);

/*Entry point with console mode
@return 0: SUCCESS i otherwise
*/
uint8_t resolution(struct Cellule[9][9]);

/*Set value for a cell when it has only one possibility or to try a branch
@return The value set, 0 otherwise*/
uint8_t set_value(struct Cellule*);
#endif