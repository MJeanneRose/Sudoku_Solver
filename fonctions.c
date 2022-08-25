/* JEANNE-ROSE Méven
    4/5/22
    fonctions.c
    Performs calculations on array and display in the console
*/

#include "fonctions.h"

void main_console(void){
    uint8_t to_find;
    to_find = init_array(g_tableau, g_ti);
    printf("Indices begin at 0 [line][column]\n");
    Affichage(g_tableau);
    printf("Values to find : %d/81\n", to_find);
    resolution(g_tableau);
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

uint8_t resolution(struct Cellule tableau[9][9]){
    if(++recurs >= MAX_NB_RECURS){
        recurs--;
        return REACH_MAX_NB_RECURS;
    }
    uint8_t ligne, colonne, rvalue, value_set;
    printf("Computing step %d...\n", recurs);
    do{
        //clean_array(tableau);
        rvalue = calcul_valeurs_possibles(tableau, &ligne, &colonne);
        if(rvalue == 0){//All values found

        }
        else if(rvalue == 1){//Only one value possible
            printf("Step %d - Value found at [%d][%d] : ",recurs,ligne, colonne);
            affiche_valeurs_possibles(tableau[ligne][colonne]);
            Affichage(tableau);
            set_value(&tableau[ligne][colonne]);
        }
        else if(rvalue > 1 && rvalue < 10){//Many possibilities     
            printf("Step %d - %d possibilities at [%d][%d] : ", recurs, rvalue, ligne, colonne);
            affiche_valeurs_possibles(tableau[ligne][colonne]);
            struct Cellule new_tableau[9][9];
            do{
                copy_cell_array(tableau,new_tableau);
                value_set = set_value(&new_tableau[ligne][colonne]);
                rvalue = resolution(new_tableau);
                if (rvalue == NO_POSSIBILITY_AND_NO_VALUE){
                    tableau[ligne][colonne].valeurs_possibles &= ~(0x100 >> (value_set-1));
                    if(tableau[ligne][colonne].valeurs_possibles == 0){
                        recurs--;
                        return NO_POSSIBILITY_AND_NO_VALUE;
                    }
                    printf("step %d try with value %d\n",recurs,tableau[ligne][colonne].valeurs_possibles);
                }
                else if(rvalue == REACH_MAX_NB_RECURS){
                    return REACH_MAX_NB_RECURS;
                }
            }while(rvalue == NO_POSSIBILITY_AND_NO_VALUE);
            copy_cell_array(new_tableau, tableau);
        }
        else{
            recurs--;
            if(rvalue == NO_POSSIBILITY_AND_NO_VALUE){
                printf("Wrong branch\n");
            }
            else{
                printf("Unknow : Program fail\n");
            }
            return rvalue;
        }
    }while(rvalue == 1);
    printf("End of depth %d\n",recurs);
    if(recurs == 0){
        Affichage(tableau);
    }
    recurs--;
    return rvalue;
}

uint8_t calcul_valeurs_possibles(struct Cellule array[9][9], uint8_t *ligne, uint8_t *colonne){
    struct Cellule minimum;
    minimum.nombre_possibilites = NB_POSSIBLE_VALUES_UNINIT;
    minimum.valeurs_possibles = 0x1FF;
    uint16_t rvalue;

    DEBUG_LOG("Line calculation...\n")
    rvalue = calcul_valeurs_possibles_selon_ligne(array);
    DEBUG_LOG("Ok\n");
    if(rvalue == NO_POSSIBILITY_AND_NO_VALUE){
        return rvalue;
    }

    DEBUG_LOG("Column calculation...\n");
    rvalue = calcul_valeurs_possibles_selon_colonne(array);
    DEBUG_LOG("Ok\n");
    if(rvalue == NO_POSSIBILITY_AND_NO_VALUE){
        return rvalue;
    }

    DEBUG_LOG("Block calculation...\n");
    calcul_valeurs_possibles_selon_block(array, &minimum, ligne, colonne);
    DEBUG_LOG("Ok\n");
    if(minimum.nombre_possibilites == 1 || minimum.nombre_possibilites == NO_POSSIBILITY_AND_NO_VALUE){
        return minimum.nombre_possibilites;
    }

/* Init value didn't change -> Array is full */
    if(minimum.nombre_possibilites == NB_POSSIBLE_VALUES_UNINIT){
        return 0;
    }
    else{
        return minimum.nombre_possibilites;
    }
}

uint16_t calcul_valeurs_possibles_selon_ligne(struct Cellule array[9][9]){
    uint8_t nb_possibilites;
    for(uint8_t i=0 ; i<9 ; i++){
        for(uint8_t j=0 ; j<9 ; j++){
            /* Cell contains a value, don't compute the possibilities */
            if(array[i][j].valeur){
                continue;
            }
            nb_possibilites = calcul_valeurs_possibles_cellule_selon_ligne(i, j, array);
            if(nb_possibilites == 0){
                /* Problem : 0 possibility and cell doesn't contain a value */
                return NO_POSSIBILITY_AND_NO_VALUE;
            }
        }
    }
    return 0;
}

uint16_t calcul_valeurs_possibles_selon_colonne(struct Cellule array[9][9]){
    uint8_t nb_possibilites;
    for(uint8_t i=0 ; i<9 ; i++){
        for(uint8_t j=0 ; j<9 ; j++){
            /* Cell contains a value, don't compute the possibilities */
            if(array[i][j].valeur){
                continue;
            }
            nb_possibilites = calcul_valeurs_possibles_cellule_selon_colonne(i, j, array);
            if(nb_possibilites == 0){
                /* Problem : 0 possibility and cell doesn't contain a value */
                return NO_POSSIBILITY_AND_NO_VALUE;
            }
        }
    }
    return 0;
}

void calcul_valeurs_possibles_selon_block(struct Cellule array[9][9], struct Cellule *min, uint8_t *ligne, uint8_t *colonne){
    uint8_t nb_possibilites;
    for(uint8_t i = 1; i<10; i++){
        nb_possibilites = update_block(i, ligne, colonne, array, min);
        if(nb_possibilites == 1 || nb_possibilites == NO_POSSIBILITY_AND_NO_VALUE){
            return;
        }
    }
}

uint8_t calcul_valeurs_possibles_cellule_selon_ligne(uint8_t ligne_fixe, uint8_t colonne_fixe, struct Cellule array[9][9]){
    uint8_t val;
    for(uint8_t column = 0; column <9; column++){
        val = array[ligne_fixe][column].valeur;
        if((column == colonne_fixe) || (val==0)){
            continue;
        }
        array[ligne_fixe][colonne_fixe].valeurs_possibles &= ~(0x100 >> (val-1));
    }
    return update_nb_possibilites(&array[ligne_fixe][colonne_fixe]);
}

uint8_t calcul_valeurs_possibles_cellule_selon_colonne(uint8_t ligne_fixe, uint8_t colonne_fixe, struct Cellule array[9][9]){
    uint8_t val;
    for(uint8_t line = 0; line <9; line++){
        val = array[line][colonne_fixe].valeur;
        if((line == ligne_fixe) || (val==0)){
            continue;
        }
        array[ligne_fixe][colonne_fixe].valeurs_possibles &= ~(0x100 >> (val-1));
    }
    return update_nb_possibilites(&array[ligne_fixe][colonne_fixe]);
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
            /* Cell doesn't contain value, nothing to add to the mask */
            if(val == 0){
                continue;
            }
            masque &= ~(0x100 >> (val-1)); 
        }
    }
    for(i = ligne_start; i<ligne_start+3; i++){/*Apply mask*/
        for(j = colonne_start; j<colonne_start+3; j++){
            if(array[i][j].valeur != 0){/* Cell contains a value, don't apply mask */
                continue;
            }
            array[i][j].valeurs_possibles &= masque;
            nb_possibilites = update_nb_possibilites(&array[i][j]);
            if(nb_possibilites == 0){
                /* Cell doesn't contain a value and possibility = 0 */
                min->nombre_possibilites = NO_POSSIBILITY_AND_NO_VALUE;
                return NO_POSSIBILITY_AND_NO_VALUE;
            }
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

void copy_cell_array(const struct Cellule origin[9][9], struct Cellule new_tab[9][9]){
    for(uint8_t i=0; i<9;i++){
        for(uint8_t j=0; j<9;j++){
            new_tab[i][j].nombre_possibilites = origin[i][j].nombre_possibilites;
            new_tab[i][j].valeurs_possibles = origin[i][j].valeurs_possibles;
            new_tab[i][j].valeur = origin[i][j].valeur;
            new_tab[i][j].padding = origin[i][j].padding;
        }
    }
}

void clean_array(struct Cellule array[9][9]){
    for(uint8_t i = 0; i < 9; i++){
        for(uint8_t j=0; j<9; j++){
            if(array[i][j].valeur == 0){
                array[i][j].valeurs_possibles = 0x1FF;
                array[i][j].nombre_possibilites = 9;
            }
            else{ /*value is present, nothing is possible*/
                array[i][j].nombre_possibilites = 0;
                array[i][j].valeurs_possibles = 0;
            }
        }
    }
}