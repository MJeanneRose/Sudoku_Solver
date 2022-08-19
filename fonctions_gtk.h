/* JEANNE-ROSE Méven
    18/8/22
    fonctions_gtk.h
    Display in GTK and use fonctions.* to calculate
*/

#ifndef _FONCTION_GTK_H
#define _FONCTION_GTK_H

#include <gtk/gtk.h>

#include "fonctions.h"

extern uint8_t g_ti [9][9];
extern struct Cellule g_tableau[9][9];
extern uint8_t recurs;

/*Main to use GTK*/
int main_gtk(int argc, char **argv);

/*Entry point with GTK, display some info in the textView*/
uint8_t resolution_gtk(struct Cellule tableau[9][9], gpointer data);

/*Check fields and begins computation when main button is clicked*/
void button_clicked(GtkWidget *widget, gpointer data);

/*Input is checked before building the main Cellule array*/
void text_entered(GtkWidget *widget, gpointer data);

/*Used to check the entiere Cellule array before performing computation*/
uint8_t gtk_check_values(void);

/*Display the array in the GTK' window*/
void Affichage_gtk(struct Cellule const tab[9][9]);

#endif