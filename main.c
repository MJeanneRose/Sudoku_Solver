/* JEANNE-ROSE Méven
    02/05/22
*/

#include <stdio.h>
#include <stdint.h>

#include "fonctions.h"
#include "fonctions_gtk.h"

#define USE_GTK 1

#if !USE_GTK
/*Global ti array (used to get values)*/
  uint8_t g_ti [9][9] =   {{0, 0, 9, 0, 0, 2, 0, 0, 5},
                    {5, 3, 8, 0, 6, 4, 0, 0, 9},
                    {1, 6, 2, 0, 0, 0, 0, 3, 0},
                    {0, 0, 3, 0, 2, 7, 0, 0, 0},
                    {0, 5, 4, 6, 0, 0, 1, 0, 0},
                    {0, 0, 7, 0, 1, 5, 3, 4, 0},
                    {3, 0, 0, 8, 0, 1, 9, 0, 6},
                    {7, 0, 0, 3, 0, 0, 8, 5, 0},
                    {0, 9, 1, 0, 0, 0, 4, 7, 0}
  };
#else
/*Global ti array (used to get values)*/
  uint8_t g_ti [9][9] = {0};
#endif

/*Global array (used to find values)*/
struct Cellule g_tableau[9][9];

/*Global variable to keep track of recursivity*/
uint8_t recurs = 255;

int main (__attribute__((unused))int argc, __attribute__((unused))char **argv)
{
  #if USE_GTK
    main_gtk(argc, argv);
  #else
  main_console();
  #endif

  return 0;
}
