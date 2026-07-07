#include "libft.h"

void  ft_free(void **ptr)
{
  if (*ptr != NULL)
  {
    free(*ptr);
    *ptr = NULL;
  }
}
