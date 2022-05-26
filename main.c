/* JEANNE-ROSE Méven
    02/05/22
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdint.h>

#include "fonctions.h"

uint8_t ti [9][9] =   {{0, 0, 9, 0, 0, 2, 0, 0, 5},
                    {5, 3, 8, 0, 6, 4, 0, 0, 9},
                    {1, 6, 2, 0, 0, 0, 0, 3, 0},
                    {0, 0, 3, 0, 2, 7, 0, 0, 0},
                    {0, 5, 4, 6, 0, 0, 1, 0, 0},
                    {0, 0, 7, 0, 1, 5, 3, 4, 0},
                    {3, 0, 0, 8, 0, 1, 9, 0, 6},
                    {7, 0, 0, 3, 0, 0, 8, 5, 0},
                    {0, 9, 1, 0, 0, 0, 4, 7, 0}
  };
  

int main (int argc, char **argv)
{

  GtkWidget *fenetre_principale = NULL;
  GtkBuilder *builder = NULL;
  GError *error = NULL;
  gchar *filename = NULL;
  GtkWidget **array_entry;

  gtk_init(&argc, &argv);

  builder = gtk_builder_new();

  /* Création du chemin complet pour accéder au fichier test.glade. */
  /* g_build_filename(); construit le chemin complet en fonction du système */
  /* d'exploitation. ( / pour Linux et \ pour Windows) */
  filename =  g_build_filename ("window_main.glade", NULL);

  gtk_builder_add_from_file (builder, filename, &error);
  g_free (filename);

  if (error)
  {
    gint code = error->code;
    g_printerr("%s\n", error->message);
    g_error_free (error);
    return code;
  }

    /* Récupération du pointeur de la fenêtre principale */
  fenetre_principale = GTK_WIDGET(gtk_builder_get_object (builder, "MainWindow"));

  /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
  /* fermeture de la fenêtre. */
  g_signal_connect (G_OBJECT (fenetre_principale), "destroy", (GCallback)gtk_main_quit, NULL);

  /* Regroupe toutes les entries*/
  array_entry = g_new0(GtkWidget*, 81);


  /* Affichage de la fenêtre principale. */
  gtk_widget_show_all (fenetre_principale);

  gtk_main();

  g_free(array_entry);


  struct Cellule tableau[9][9];

  init_array(tableau, ti);
  
  Affichage(tableau);

  resolution(tableau);

  return 0;
}
