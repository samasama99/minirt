#include "main.h"

int main()
{
  init_mlx(pair(400, 400), pair(0, 0));
  t_world w = world();
  // sphere
  // t_sphere s = make_sphere(point(0,0,15), 20);
  t_sphere s = sphere();
  s.t = mat4_mult(translation(0, 0, 10), scaling(20, 20, 20));
  s.material.color = color(1, 0, 0);
  s.material.specular = 0;
  s.material.ambient = 0.9;
  w = add_sphere(w, s);
  ///////////////////////////////////////////
  // light
  t_light l = point_light(point(-40, 0, 30), color(1, 1, 1));
  w = add_light(w, l);
  ///////////////////////////////////////////
  // camera
  t_camera c = camera(400, 400, radians(70));
  const t_point from = point(-50, 0, 20);
  const t_point to = point(0, 0, 0);
  const t_point up = vector(0, 1, 0);
  c.transform = view_transform(from, to, up);
  //////////////////////////////////////////
  t_image canvas = render(c, w);
  put_image(pair(0, 0), canvas);
  start_mlx();
}
