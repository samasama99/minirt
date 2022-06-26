#include "libft.h"

int main()
{
  char **array = ft_split("test hello", ' ');
  printf ("%s %s\n", array[0], array[1]);
}
