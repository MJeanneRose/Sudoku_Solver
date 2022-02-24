/* JEANNE-ROSE Méven
    30/12/21
*/
#include <stdio.h>
#include "fonctions.h"

void Affichage(char tab[9][9])
{
    for (char i = 0; i < 9; i++)
    {
        for (char j = 0; j < 9; j++)
            printf("%d", tab[i][j]);
        printf("\n");
    }
    printf("\n");
}