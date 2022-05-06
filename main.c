/* JEANNE-ROSE Méven
    02/05/22
*/

//#include <gtk/gtk.h>
#include <stdio.h>
#include <stdint.h>

#include "fonctions.h"


/*static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}*/

/*static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  //gtk_window_set_child (GTK_WINDOW (window), button);

  gtk_window_present (GTK_WINDOW (window));
}*/

uint8_t ti [9][9] =   {0, 0, 9, 0, 0, 2, 0, 0, 5,
                    5, 3, 8, 0, 6, 4, 0, 0, 9,
                    1, 6, 2, 0, 0, 0, 0, 3, 0,
                    0, 0, 3, 0, 2, 7, 0, 0, 0,
                    0, 5, 4, 6, 0, 0, 1, 0, 0,
                    0, 0, 7, 0, 1, 5, 3, 4, 0,
                    3, 0, 0, 8, 0, 1, 9, 0, 6,
                    7, 0, 0, 3, 0, 0, 8, 5, 0,
                    0, 9, 1, 0, 0, 0, 4, 7, 0
  };

int main (int argc, char **argv)
{
  /*GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;*/

  struct Cellule tableau[9][9];

  init_array(tableau, ti);
  
  printf("*****TI*****\n");
  Affichage(tableau);

resolution(tableau);

  return 0;
}
