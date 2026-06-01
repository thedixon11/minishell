#include "minishell_xecution.h"

//NOTE: ce fichier est obsolete (il est utilise nulle part)

int  fill_array(char **new_array, char *array, int ynew)
{
  int y;

  y = 0;
  while (array[y] != NULL)
  {
    new_array[ynew] = ft_strdup(array[y]);
    ynew++;
    y++;
  }
  return (ynew);
}

char  **ft_arrayjoin(char **array1, char **array2)
{
  char  **new_array;
  int y1;
  int y2;
  int ynew;

  y1 = 0;
  y2 = 0;
  ynew = 0;
  while (array1[y1] != NULL)
    y1++;
  while (array2[y2]) != NULL)
    y2++;
  new_array == ft_calloc((y1 + y2 + 1), sizeof(char *));
  ynew = fill_array(new_array, array1, 0);
  ynew = fill_array(new_array, array2, ynew);
  return (new_array); 
}

