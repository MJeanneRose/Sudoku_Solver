/* JEANNE-ROSE Méven
    30/12/21
*/
#include <stdio.h>
#include "fonctions.h"

extern char profondeur;
extern char ti[9][9];

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

void AffichageTblock(char tab[3][3][9]){
    for(char colonne = 0; colonne <3; colonne++){
        for(char ligne = 0; ligne<3; ligne++){
            printf("\nColonne %d Ligne %d\n", colonne, ligne);
            for(char deep = 0; deep<9; deep++)
                printf("%d",tab[colonne][ligne][deep]);
        }
        printf("\n");
    }
}

void AffichageTp(char tab[9][9][9]){
    for(char colonne = 0; colonne <9; colonne++){
        for(char ligne = 0; ligne<9; ligne++){
            printf("\nColonne %d Ligne %d\n", colonne, ligne);
            for(char deep = 0; deep<9; deep++)
                printf("%d",tab[colonne][ligne][deep]);
        }
        printf("\n");
    }
}

void RemplirtLigne(char tLigne[9][9]){
    char valeur;
    for(char ligne = 0; ligne <9; ligne++){
        for(char colonne = 0; colonne <9; colonne++){
            valeur = ti[ligne][colonne];
            if(valeur)
                tLigne[ligne][valeur-1] = valeur;
        }
    }
}

void RemplirtCol(char tLigne[9][9]){
    char valeur;
    for(char ligne = 0; ligne <9; ligne++){
        for(char colonne = 0; colonne <9; colonne++){
            valeur = ti[ligne][colonne];
            if(valeur)
                tLigne[valeur-1][colonne] = valeur;
        }
    }
}

void RemplirtBlock(char tBlock[3][3][9]){
    char valeur;
    for(char colonne = 0; colonne <3; colonne++)
        for(char ligne = 0; ligne <3; ligne++)
            for(char i = 0; i<3; i++)
                for(char j = 0; j<3; j++){
                    valeur = ti[colonne*3+i][ligne*3+j];
                    if(valeur){
                        tBlock[colonne][ligne][valeur-1] = valeur;
                        //printf("Valeur : %d presente, mise dans case [%d][%d]\n", valeur, colonne, ligne);
                    }
                }
}

char RemplirTp(char tp[9][9][9], char tBlock[3][3][9], char tLigne [9][9], char tCol[9][9]){
    for(int c = 0; c<9; c++)
        for(int l = 0; l<9; l++){
            printf("COLONNE %d LIGNE %d\n", c, l);
            if(ti[c][l]!=0){
                printf("Aucune possiblité \n");
                for(char deep = 0; deep<9; deep++)
                    tp[c][l][deep] = deep+1;
            }
            else{
                for(char i = 0; i<9; i++)
                    if(IsPossible( c, l, i+1, tBlock, tLigne, tCol)){
                        printf("%d possible \n",i);
                        tp[c][l][i] = 0;
                        return 66;
                    }
                    else{
                        printf("%d impossible\n",i);
                        tp[c][l][i] = i+1;
                    }
            }
        }
}

bool IsPossible(char col, char li, char val, char tBlock[3][3][9], char tLigne [9][9], char tCol[9][9]){
    printf("Valeur : %d col : %d li : %d\n", val, col, li);
    printf("tBlock[%d][%d][%d] = %d\n",col/3, li/3, val-1, tBlock[col/3][li/3][val-1]);
    if(!tBlock[col/3][li/3][val-1]){
        printf("tLigne[%d][%d] = %d\n",col, li);
        if(!tLigne[col][li])
        {
            printf("tCol[%d][%d] = %d\n",col, li, tCol[col][li]);
            if(!tCol[col][li]){
                
                return true;
            }
        }
    }
    return false;
}

int Resolution(char caseLi, char caseCi, char caseVidei, char valeur)
{

    profondeur += 1;
    printf("Profondeur : %d\n", profondeur);

    char tBlock[3][3][9]={0}; //valeurs non autorisées par block
    char tLigne[9][9]={0};    //valeurs non autorisées par ligne
    char tCol[9][9]={0};      //valeurs non autorisées par colonne
    char tP[9][9][9];     //valeurs non autorisées par case

    char caseL;                //ligne de la case cible
    char caseC;                //colonne case cible
    char nbPossible;           //nombre minimum de possibilité
    char caseVide = caseVidei; //nombre de case vide

    RemplirtLigne(tLigne);
    printf("*****TLIGNE*****\n");
    Affichage(tLigne);

    RemplirtCol(tCol);
    printf("*****TCOLONNE*****\n");
    Affichage(tCol);

    RemplirtBlock(tBlock);
    printf("*****TBLOCK*****\n");
    AffichageTblock(tBlock);

    nbPossible = RemplirTp(tP, tBlock, tLigne, tCol);
    if(nbPossible == 66){
        printf("Stop fonctionnement : \n");
        printf("*****Tp*****\n");
        AffichageTp(tP);
    }
    else
    printf("Pas d arret\n");

    return 0;
}