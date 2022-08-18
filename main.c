/* JEANNE-ROSE Méven
    02/05/22
*/

#include <stdio.h>
#include <stdint.h>

#include <gtk/gtk.h>

#include "fonctions.h"
#include "fonctions_gtk.h"

#define USE_GTK 1

/*Use this array for debug*/
/*
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
  */

  uint8_t ti [9][9] = {0};
  struct Cellule tableau[9][9];

int main (int argc, char **argv)
{
#if USE_GTK
  main_gtk(argc, argv);
#else
 main_console();
#endif

  return 0;
}
