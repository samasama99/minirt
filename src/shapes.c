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

t_plane plane()
{
  return make_plane(point(0, 0, 0), vector(0, 1, 0));
}

t_shape sphere_shape(t_sphere s)
{
  t_shape ss;

  ss.sphere = s;
  return ss;
}

t_shape plane_shape(t_plane s)
{
  t_shape ss;

  ss.plane = s;
  return ss;
}
