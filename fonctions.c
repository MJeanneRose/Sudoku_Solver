/* JEANNE-ROSE Méven
    30/12/21
*/
#include <stdio.h>
#include "fonctions.h"

void Affichage(struct Cellule tab[9][9])
{
    for (uint8_t i = 0; i < 9; i++)
    {
        for (uint8_t j = 0; j < 9; j++){
            printf("%d", tab[i][j].valeur);
        }
        printf("\n");
    }
    printf("\n");
}

void init_array(struct Cellule array[9][9], uint8_t tab[9][9]){
    for(uint8_t i = 0; i<9; i++){
        for(uint8_t j=0; j<9; j++){
            array[i][j].valeur=tab[i][j];
            if(array[i][j].valeur == 0){
            array[i][j].valeurs_possibles = 0x1FF;/*assume everything is possible if there isn't any value*/
            array[i][j].nombre_possibilites = 9;
            }
            else{ /*value is present, nothing is possible*/
                array[i][j].nombre_possibilites = 0;
                array[i][j].valeurs_possibles = 0;
            }
        }
    }
}

uint8_t resolution(struct Cellule tableau[9][9]){
    calcul_valeurs_possibles(tableau);
}

uint8_t calcul_valeurs_possibles(struct Cellule array[9][9]){
    struct Cellule max;
    max.nombre_possibilites = 9;
    max.valeurs_possibles = 0x1FF;
    uint8_t nb_possiblities;
    uint8_t ligne, colonne;

    for(uint8_t i=0; i<1;i++){//remettre à 9 pour faire tout le tableau
        for(uint8_t j=0; j<9;j++){
            nb_possiblities = calcul_valeurs_possibles_ligne(i, j, array);
            if(nb_possiblities == 1){
                set_value(array[i][j]);
                //return to recompute array
            }
            else if((nb_possiblities <= max.nombre_possibilites) && nb_possiblities != 0){
                max.nombre_possibilites = nb_possiblities;
                max.valeurs_possibles = array[i][j].valeurs_possibles;
                ligne = i;
                colonne = j;
            }
            printf("default : %d [%d][%d]\t [%d][%d] : %d\n", max.nombre_possibilites, ligne, colonne, i, j, nb_possiblities);
        }
    }
}

uint8_t calcul_valeurs_possibles_ligne(uint8_t ligne, uint8_t col, struct Cellule array[9][9]){
    uint8_t val;
    
    for(uint8_t column = 0; column <9; column++){
        val = array[ligne][column].valeur;
        if((column == col) || (val==0))
            continue;

        array[ligne][col].valeurs_possibles &= ~(0x100 >> (val-1));
        //printf("%d detecte, masque : %x\n", val, ~(0x100 >> (val-1)));
    }
    //printf("nb possibilities : %d",update_nb_possibilites(array[ligne][col]));
    return update_nb_possibilites(array[ligne][col]);

}

uint8_t update_nb_possibilites(struct Cellule cell){
    cell.nombre_possibilites = 0;
    for(uint8_t i = 0; i<9; i++){
        if(cell.valeurs_possibles & (1 << i)){
            cell.nombre_possibilites++;
        }
    }
    return cell.nombre_possibilites;
}

void set_value(struct Cellule cell){
    cell.nombre_possibilites = 0;
    for(uint8_t i = 0; i< 9; i++){
       if(cell.valeurs_possibles & (0x100 >> i)){
            cell.valeur = i+1;
            cell.valeurs_possibles = 0;
            return;
        }
    }
}

void affiche_valeurs_possibles(struct Cellule cell){
    for(uint8_t i=0; i<9;i++){
        if(cell.valeurs_possibles & (0x100 >> i)){
            printf("1");
        }
        else{
            printf("0");
        }
    }
    printf("\n");
}
