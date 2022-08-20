/* JEANNE-ROSE Méven
    4/5/22
    fonctions.c
    Performs calculations on array and display in the console
*/

#include "fonctions.h"

void main_console(void){
    uint8_t to_find;
    to_find = init_array(g_tableau, g_ti);
    Affichage(g_tableau);
    resolution(g_tableau, to_find);
}

void Affichage(struct Cellule const tab[9][9])
{
    printf("*****ARRAY*****\n");
    for (uint8_t i = 0; i < 9; i++)
    {
        for (uint8_t j = 0; j < 9; j++){
            printf("%d", tab[i][j].valeur);
        }
        printf("\n");
    }
    printf("\n");
}

uint8_t init_array(struct Cellule array[9][9], uint8_t const tab[9][9]){
    uint8_t to_find = 0;
    for(uint8_t i = 0; i<9; i++){
        for(uint8_t j=0; j<9; j++){
            array[i][j].valeur=tab[i][j];
            if(array[i][j].valeur == 0){
            array[i][j].valeurs_possibles = 0x1FF;/*assume everything is possible if there isn't any value*/
            array[i][j].nombre_possibilites = 9;
            to_find++;
            }
            else{ /*value is present, nothing is possible*/
                array[i][j].nombre_possibilites = 0;
                array[i][j].valeurs_possibles = 0;
            }
        }
    }
    return to_find;
}

uint8_t resolution(struct Cellule tableau[9][9], uint8_t to_find){
    if(++recurs >= MAX_NB_RECURS){
    return 42;
  }
    printf("Recurse step : %d\n",recurs);
    uint8_t ligne, colonne, rvalue;
    printf("Computing...\n");
    do{
        rvalue = calcul_valeurs_possibles(tableau, &ligne, &colonne);
        if(rvalue == 1){
            printf("Value found at [%d][%d] : ",ligne, colonne);
            affiche_valeurs_possibles(tableau[ligne][colonne]);
            set_value(&tableau[ligne][colonne]);
            to_find--;
            Affichage(tableau);
        }
        else if(rvalue > 1){
            printf("%d possibilities at [%d][%d] : ", rvalue, ligne, colonne);
            affiche_valeurs_possibles(tableau[ligne][colonne]);
            struct Cellule new_tableau[9][9];
            copy_cell_array(tableau,new_tableau);
            set_value(&new_tableau[ligne][colonne]);
            rvalue = resolution(new_tableau, to_find-1);
        }
    }while(rvalue == 1);
    printf("End of the resolution depth %d :\n",recurs);
    Affichage(tableau);
    recurs--;
    return to_find;
    
}

uint8_t calcul_valeurs_possibles(struct Cellule array[9][9], uint8_t *ligne, uint8_t *colonne){
    struct Cellule minimum;
    minimum.nombre_possibilites = 9;
    minimum.valeurs_possibles = 0x1FF;

    printf("Line calculation...\n");
    calcul_valeurs_possibles_selon_ligne(array, &minimum, ligne, colonne);
    printf("Ok\n");
    if(minimum.nombre_possibilites == 1){
        return 1;
    }
    printf("Number of possibilities min : %d at [%d][%d] : ", minimum.nombre_possibilites, *ligne, *colonne);
    affiche_valeurs_possibles(array[*ligne][*colonne]);

    printf("Column calculation...\n");
    calcul_valeurs_possibles_selon_colonne(array, &minimum, ligne, colonne);
    printf("Ok\n");
    if(minimum.nombre_possibilites == 1){
        return 1;
    }
    printf("Number of possibilities min : %d at [%d][%d]\n", minimum.nombre_possibilites, *ligne, *colonne);
    affiche_valeurs_possibles(array[*ligne][*colonne]);

    printf("Block calculation...\n");
    calcul_valeurs_possibles_selon_block(array, &minimum, ligne, colonne);
    printf("Ok\n");
    if(minimum.nombre_possibilites == 1){
        return 1;
    }
    printf("Number of possibilities min : %d at [%d][%d]\n", minimum.nombre_possibilites, *ligne, *colonne);

    return minimum.nombre_possibilites;
}

void calcul_valeurs_possibles_selon_ligne(struct Cellule array[9][9], struct Cellule *min, uint8_t *ligne, uint8_t *colonne){
    uint8_t nb_possibilites;
    for(uint8_t i=0 ; i<9 ; i++){
        for(uint8_t j=0 ; j<9 ; j++){
            if(array[i][j].valeur){//cell contains a value, don't compute the possibilities
                continue;
            }
            nb_possibilites = calcul_valeurs_possibles_cellule_selon_ligne(i, j, array);
            if(nb_possibilites == 0){
                // TODO: Problem : 0 possibility and cell doesn't contain a value
            }
            if((nb_possibilites <= min->nombre_possibilites) || (min->nombre_possibilites == 0)){
                *ligne = i;
                *colonne = j;
                if(nb_possibilites == 1){
                    min->nombre_possibilites = 1;
                    return;
                }
                else{
                    min->nombre_possibilites = nb_possibilites;
                    min->valeurs_possibles = array[i][j].valeurs_possibles;
                }
            }
        }
        printf("Possibilites sur la ligne %d: ",i);
        affiche_valeurs_possibles(array[i][8]);
    }
}

void calcul_valeurs_possibles_selon_colonne(struct Cellule array[9][9], struct Cellule *min, uint8_t *ligne, uint8_t *colonne){
    uint8_t nb_possibilites;
    for(uint8_t i=0 ; i<9 ; i++){
        for(uint8_t j=0 ; j<9 ; j++){
            if(array[i][j].valeur){//cell contains a value, don't compute the possibilities
                continue;
            }
            nb_possibilites = calcul_valeurs_possibles_cellule_selon_colonne(i, j, array);
            if(nb_possibilites == 0){
                // TODO: Problem : 0 possibility and cell doesn't contain a value
            }
            if((nb_possibilites <= min->nombre_possibilites) || (min->nombre_possibilites == 0)){
                *ligne = i;
                *colonne = j;
                if(nb_possibilites == 1){
                    min->nombre_possibilites = 1;
                    return;
                }
                else{
                    min->nombre_possibilites = nb_possibilites;
                    min->valeurs_possibles = array[i][j].valeurs_possibles;
                }
            }
        }
        printf("Possibilites sur la colonne %d: ",i);
        affiche_valeurs_possibles(array[i][8]);
    }
}

void calcul_valeurs_possibles_selon_block(struct Cellule array[9][9], struct Cellule *min, uint8_t *ligne, uint8_t *colonne){
    uint8_t nb_possibilites;
    for(uint8_t i = 1; i<10; i++){
        nb_possibilites = update_block(i, ligne, colonne, array, min);
        printf("Number min of possibilities in block %d is %d at [%d][%d]\n",i, nb_possibilites, *ligne, *colonne);
        if(nb_possibilites == 1){
            return;
        }
    }
}

uint8_t calcul_valeurs_possibles_cellule_selon_ligne(uint8_t ligne, uint8_t col, struct Cellule array[9][9]){
    uint8_t val;
    for(uint8_t column = 0; column <9; column++){
        val = array[ligne][column].valeur;
        if((column == col) || (val==0))
            continue;

        array[ligne][col].valeurs_possibles &= ~(0x100 >> (val-1));
        //printf("%d detecte, masque : %x\n", val, ~(0x100 >> (val-1)));
    }
    return update_nb_possibilites(&array[ligne][col]);
}

uint8_t calcul_valeurs_possibles_cellule_selon_colonne(uint8_t ligne, uint8_t colonne, struct Cellule array[9][9]){
    uint8_t val;
    
    for(uint8_t line = 0; line <9; line++){
        val = array[line][colonne].valeur;
        if((line == ligne) || (val==0))
            continue;

        array[ligne][colonne].valeurs_possibles &= ~(0x100 >> (val-1));
        //printf("%d detecte, masque : %x\n", val, ~(0x100 >> (val-1)));
    }
    return update_nb_possibilites(&array[ligne][colonne]);
}

uint8_t update_block(uint8_t block_number,uint8_t *ligne, uint8_t *colonne, struct Cellule array[9][9], struct Cellule *min){
    uint8_t val, nb_possibilites;
    uint8_t ligne_start, colonne_start;
    uint8_t i, j;
    uint16_t masque = 0x1FF;
    if(block_number < 4){
        ligne_start = 0;
    }
    else if(block_number < 7){
        ligne_start = 3;
    }
    else{
        ligne_start = 6;
    }

    if(block_number%3 == 1 ){
        colonne_start = 0;
    }
    else if(block_number%3 == 2 ){
        colonne_start = 3;
    }
    else{
        colonne_start = 6;
    }
    for(i = ligne_start; i<ligne_start+3; i++){/*Compute mask*/
        for(j = colonne_start; j<colonne_start+3; j++){
            val = array[i][j].valeur;
            if(val == 0){
                continue;
            }
            masque &= ~(0x100 >> (val-1)); 
        }
    }
    for(i = ligne_start; i<ligne_start+3; i++){/*Apply mask*/
        for(j = colonne_start; j<colonne_start+3; j++){
            if(array[i][j].valeur != 0){
                continue;
            }
            array[i][j].valeurs_possibles &= masque;
            nb_possibilites = update_nb_possibilites(&array[i][j]);
            if(nb_possibilites <= min->nombre_possibilites){
                *ligne = i;
                *colonne = j;
                min->nombre_possibilites = nb_possibilites;
                min->valeurs_possibles = array[i][j].valeurs_possibles;
                if(nb_possibilites == 1){
                    return 1;
                }
            }
        }
    }
    return min->nombre_possibilites;
}

uint8_t update_nb_possibilites(struct Cellule *cell){
    cell->nombre_possibilites = 0;
    for(uint8_t i = 0; i<9; i++){
        if(cell->valeurs_possibles & (1 << i)){
            cell->nombre_possibilites++;
        }
    }
    return cell->nombre_possibilites;
}

uint8_t set_value(struct Cellule *cell){
    for(uint8_t i = 0; i< 9; i++){
       if(cell->valeurs_possibles & (0x100 >> i)){
            cell->valeur = i+1;
            return cell->valeur;
        }
    }
    return 0;
}

void affiche_valeurs_possibles(const struct Cellule cell){
    for(uint8_t i=0; i<9;i++){
        if(cell.valeurs_possibles & (0x100 >> i)){
            printf("%d ",i+1);
        }
    }
    printf("\n");
}

void copy_cell_array(const struct Cellule origin[9][9], struct Cellule new[9][9]){
    for(uint8_t i=0; i<9;i++){
        for(uint8_t j=0; j<9;j++){
            new[i][j].nombre_possibilites = origin[i][j].nombre_possibilites;
            new[i][j].valeurs_possibles = origin[i][j].valeurs_possibles;
            new[i][j].valeur = origin[i][j].valeur;
            new[i][j].padding = origin[i][j].padding;
        }
    }
}