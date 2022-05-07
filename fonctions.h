/* JEANNE-ROSE Méven
    04/05/22
*/

#ifndef _FONCTION_H
#define _FONCTION_H

#include <stdint.h>

struct Cellule{
  uint16_t valeurs_possibles : 9;
  uint16_t nombre_possibilites : 7;
  uint8_t valeur;
  uint8_t padding;
};

/********DISPLAY*******/

/*Display 9*9 array values*/
void Affichage(struct Cellule[9][9]);

/*Init first param array with 2nd param */
void init_array(struct Cellule[9][9], uint8_t tab[9][9]);

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
void affiche_valeurs_possibles(struct Cellule);

/*Entry point
@return 0: SUCCESS i otherwise*/
uint8_t resolution(struct Cellule[9][9]);

/*Set value for a celle when it has only one possibility or to try a branch*/
void set_value(struct Cellule*);
#endif