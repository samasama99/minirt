#include "main.h"

t_sphere make_sphere(t_point origin, double radius)
{
  static int id;
  const t_sphere sphere = {
    .id = ++id,
    .center = origin,
    .radius = radius,
    .t = identity(),
    .material = material(),
  };

  return sphere;
}

t_sphere sphere()
{
  return make_sphere(point(0, 0, 0), 1);
}

// t_plane make_plane() {

// }
