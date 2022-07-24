#include "main.h"
#include "vector.h"

int main (int argc, char *argv[])
{
  t_transform m = rotation_x(radians(30));  
  t_transform x;

  for (int i = 0 ; i < 1000000 ; ++i)
        x = inverse(m);

  printf ("%f %f %f\n", x.l1_c1, x.l1_c2, x.l1_c3);
  return 0;
}
