#include "main.h"

t_sphere make_sphere(t_point origin, double radius)
{
  static int id;

  return (t_sphere) {
    .type = Sphere,
    .id = ++id,
    .center = origin,
    .radius = radius,
    .t = identity(),
    .material = material(),
  };
}

t_sphere sphere()
{
  return make_sphere(point(0, 0, 0), 1);
}

t_plane make_plane(t_point pos, t_norm norm) {
  static int id;

  return (t_plane) {
    .type = Plane,
    .id = ++id,
    .t = identity(),
    .material = material(),
    .position = pos,
    .normal = norm,
  };
}
