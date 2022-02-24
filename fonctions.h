/* JEANNE-ROSE Méven
    30/12/21
*/

#ifndef _FONCTION_H
#define _FONCTION_H

#include <stdbool.h>

/********DISPLAY*******/

void Affichage(char[9][9]);
/*Display 9*9 array : ti, tLigne and tCol*/

void AffichageTblock(char tab[3][3][9]);
/*Display 3*3*9 array tBlock*/

void AffichageTp(char tab[9][9][9]);
/*Display 9*9*9 array tp*/

int Resolution(char caseLi, char caseCi, char caseVidei, char valeur);

void RemplirtLigne(char tLigne[9][9]);
//ligne contenant déjà des valeurs

void RemplirtCol(char tCol[9][9]);
//Colonne contenant déjà des valeurs

char RemplirTp(char tp[9][9][9], char tBlock[3][3][9], char tLigne [9][9], char tCol[9][9]);
//array of possibilities

void RemplirtBlock(char tBlock[3][3][9]);

bool IsPossible(char col, char li, char val, char tBlock[3][3][9], char tLigne [9][9], char tCol[9][9]);
//check if a given value is possible for a given case

#endif