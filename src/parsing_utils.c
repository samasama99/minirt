#include "parsing.h"

int count_char(const char *str, const char c)
{
  int i;
  int count;

  i = 0;
  count = 0;
  while (str[i]) {
	if (str[i] == c)
	  ++count;
	++i;
  }
  return count;
}

size_t array_len(char **array)
{
  size_t i;

  i = 0;
  while (array[i])
	++i;
  return i;
}

bool ft_isnumber(const char *num)
{
  size_t i;

  i = 0;
  while (num[i])
  {
	if (ft_isdigit(num[i]) != 1)
		return false;
	++i;
  }
  return true;
}
 
size_t int_len(int num)
{
  int i;

  i = 0;
  while (num)
  {
	num = num / 10;
	++i;
  }
  return i;
}

