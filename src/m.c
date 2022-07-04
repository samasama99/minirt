#include <stdio.h>

void repeat(int times, void (func)(), void *data)
{
  if (times == 0)
    return;
  func(data); 
  return repeat(times - 1, func, data);;
}

void square(int *x)
{
  *x = *x * *x;
}

int main()
{
  int x = 2;
  printf ("%d\n", x);
  repeat(2, square, &x);
  printf ("%d\n", x);
}
