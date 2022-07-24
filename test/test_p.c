#include "src/main.h"

int main()
{
  t_plane plane = make_plane(point(0, 0, 0),
                             vector(0, 1, 0));
  t_ray r = ray(point(0, -2, 0),
                vector(0, 1, 0));
  t_hit h = intersect((t_shape)plane, r);
  printf ("%d\n", h.count);
}
