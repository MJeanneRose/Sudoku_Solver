/* JEANNE-ROSE Méven
    18/8/22
    fonctions_gtk.h
    Display in GTK and use fonctions.* to calculate
*/

#include "fonctions_gtk.h"

static GtkEntry **array_entry;

int main_gtk(int argc, char ** argv){
  
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
  /* d'exploitation. */
  filename =  g_build_filename ("../window_main.glade", NULL);

  gtk_builder_add_from_file (builder, filename, &error);
  g_free (filename);

  if (error)
  {
    g_printerr("%s\n", error->message);
    g_error_free (error);
    return error->code;
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
  array_entry = g_new0(GtkEntry*, 81);
  int i;
  for(int col = 0; col < 9; col++){
    for(int row = 0; row < 9; row++){
      i = row + col*9;
      g_snprintf(entry_name,8,"entry%02d",i);
      array_entry[i]=GTK_ENTRY(gtk_builder_get_object(builder,entry_name));
    g_object_set_data(G_OBJECT(array_entry[i]),"row",GINT_TO_POINTER(row));
    g_object_set_data(G_OBJECT(array_entry[i]),"col",GINT_TO_POINTER(col));
    g_signal_connect (G_OBJECT (array_entry[i]), "changed",(GCallback)text_entered, buffer);
    }
  }

  /* Affichage de la fenêtre principale. */
  gtk_widget_show_all (fenetre_principale);

  gtk_main();

  g_free(array_entry);
  return 0;
}

  void button_clicked(__attribute__((unused))GtkWidget *widget, gpointer data) {
    gtk_text_buffer_set_text (data,"Checking Values... ",-1);
    if(gtk_check_values()){
        gtk_text_buffer_insert_at_cursor (data,"Fail\n",-1);
        return;
    }
    gtk_text_buffer_insert_at_cursor (data,"Ok\n",-1);
    init_array(tableau, ti);
    resolution_gtk(tableau, data);
}

void text_entered(GtkWidget *widget, gpointer data) {
  const gchar* text;
  int col, row;
  row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget),"row"));
  col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget),"col"));
  
  text = gtk_entry_get_text((GtkEntry*)widget);
  /*Entry field is empty or contain a number*/
  if((text[0] >= 48 && text[0] <=57) || text[0] == '\0'){
    ti[row][col] = text[0]-48;
  }
  /*Entry field contain an invalid value*/
  else{
    gtk_text_buffer_insert_at_cursor (data,"Invalid entry !\n",-1);
  }
}

uint8_t resolution_gtk(struct Cellule tableau[9][9], gpointer data){
    uint8_t ligne, colonne, rvalue;
    /* Conversion ligne-colonne en un seul indice : [x][y] = [z]*/
    uint8_t indice;
    uint8_t value_set;
    do{
        gtk_text_buffer_insert_at_cursor (data,"Computing...\n",-1);
        rvalue = calcul_valeurs_possibles(tableau, &ligne, &colonne);
        indice = 9*colonne + ligne;
        if(rvalue == 1){
            value_set = set_value(&tableau[ligne][colonne]);
            gtk_entry_set_text(array_entry[indice],GUINT_TO_POINTER(value_set));
        }
        else if(rvalue > 1){
            gtk_text_buffer_insert_at_cursor (data,"Number of possibilities > 1\n",-1);
        }
    }while(rvalue == 1);
    gtk_text_buffer_insert_at_cursor (data,"End of computation.\n",-1);
    return rvalue; 
}

uint8_t gtk_check_values(){
    
    for(uint8_t i = 0; i < 81; i++){
        const gchar* text = gtk_entry_get_text(array_entry[i]);
        /*Entry field doesn't contian a number*/
        if((text[0] < 48 || text[0] > 57) && (text[0] != '\0')){
            return 1;
        }
    }
    return 0;
}