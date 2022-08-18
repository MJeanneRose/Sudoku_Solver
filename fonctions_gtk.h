/* JEANNE-ROSE Méven
    18/8/22
    fonctions_gtk.h
    Display in GTK and use fonctions.* to calculate
*/

#ifndef _FONCTION_GTK_H
#define _FONCTION_GTK_H

#include <gtk/gtk.h>

#include "fonctions.h"

extern uint8_t ti [9][9];
extern struct Cellule tableau[9][9];

int main_gtk(int argc, char **argv);

uint8_t resolution_gtk(struct Cellule tableau[9][9], gpointer data);

void button_clicked(GtkWidget *widget, gpointer data);

void text_entered(GtkWidget *widget, gpointer data);

uint8_t gtk_check_values();

#endif