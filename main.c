/* JEANNE-ROSE Méven
    02/05/22
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdint.h>

#include "fonctions.h"

GtkWidget **array_entry;

/*uint8_t ti [9][9] =   {{0, 0, 9, 0, 0, 2, 0, 0, 5},
                    {5, 3, 8, 0, 6, 4, 0, 0, 9},
                    {1, 6, 2, 0, 0, 0, 0, 3, 0},
                    {0, 0, 3, 0, 2, 7, 0, 0, 0},
                    {0, 5, 4, 6, 0, 0, 1, 0, 0},
                    {0, 0, 7, 0, 1, 5, 3, 4, 0},
                    {3, 0, 0, 8, 0, 1, 9, 0, 6},
                    {7, 0, 0, 3, 0, 0, 8, 5, 0},
                    {0, 9, 1, 0, 0, 0, 4, 7, 0}
  };*/

  static uint8_t ti [9][9] = {0};
  static struct Cellule tableau[9][9];
  
  void button_clicked(GtkWidget *widget, gpointer data) {
    int row, col;
      gtk_text_buffer_set_text (data,"Checking Values... ",-1);
      if(0){
          gtk_text_buffer_insert_at_cursor (data,"Fail\n",-1);
          return;
      }
      gtk_text_buffer_insert_at_cursor (data,"Ok\n",-1);
    init_array(tableau, ti);
    Affichage(tableau);
    resolution(tableau);
  //g_print("clicked\n");
}

void text_entered(GtkWidget *widget, gpointer data) {
  const gchar* text;
  int col, row;
  row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget),"row"));
  col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget),"col"));
  
  text = gtk_entry_get_text((GtkEntry*)widget);
  /*Entry field is empty or contain a number*/
  if((text[0] >= 48 && text[0] <=57) || text[0] == '\0'){
    g_print("Nombre : %s %d %d\n",text, col, row);
    ti[row][col] = text[0]-48;
  }
  /*Entry field contain an invalid value*/
  else{
    g_print("Invalid entry at :\nrow : %d\ncolumn : %d\n",row, col);
  }
}

int main (int argc, char **argv)
{
  GtkWidget *fenetre_principale = NULL;
  GtkBuilder *builder = NULL;
  GError *error = NULL;
  gchar *filename = NULL;
  gchar entry_name[8];

  
  GtkWidget *button;
  GtkWidget *view;
  GtkTextBuffer *buffer;

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
  g_signal_connect (G_OBJECT (fenetre_principale), "destroy", (GCallback)gtk_main_quit, NULL);

  view = GTK_WIDGET(gtk_builder_get_object(builder, "TextView"));
  buffer = gtk_text_view_get_buffer((GtkTextView*)view);
  gtk_text_buffer_insert_at_cursor (buffer,"Fill the array and click on compute...\n",-1);

  button = GTK_WIDGET(gtk_builder_get_object(builder, "button_compute"));
  g_signal_connect (G_OBJECT (button), "clicked", (GCallback)button_clicked, buffer);

  /* Regroupe toutes les entries et init le tableau des entrees*/
  array_entry = g_new0(GtkWidget*, 82);
  int i;
  for(int col = 0; col < 9; col++){
    for(int row = 0; row < 9; row++){
      i = row + col*9;
      g_snprintf(entry_name,8,"entry%02d",i);
      array_entry[i]=GTK_WIDGET(gtk_builder_get_object(builder,entry_name));
    g_object_set_data(G_OBJECT(array_entry[i]),"row",GINT_TO_POINTER(row));
    g_object_set_data(G_OBJECT(array_entry[i]),"col",GINT_TO_POINTER(col));
    g_signal_connect (G_OBJECT (array_entry[i]), "changed",(GCallback)text_entered, NULL);
    }
  }

  /* Affichage de la fenêtre principale. */
  gtk_widget_show_all (fenetre_principale);

  gtk_main();

  g_free(array_entry);

  return 0;
}
