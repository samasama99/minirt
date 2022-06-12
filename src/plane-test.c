#include "main.h"

int main()
{
  const t_res res = pair(200, 100);
  init_mlx(res, pair(0, 0));

  t_sphere s = sphere();
  s.t = scaling(2, 2, 2);
  t_plane floor = plane();
  floor.material = material();
  floor.material.color = color(1, 0.9, 0.9);
  floor.material.specular = 0;
  t_world w = world();
  t_light light = point_light(point(0, 5, 0), color(1, 1, 1));
  t_camera c = camera(res.x, res.y, 60);
  c.transform = view_transform(point(0, +3, 0),
                               point(0, 0, 0),
                               vector(0, 0, 1));
  w = add_light(w, light);
  w = add_shape(w, (t_shape)floor);
  w = add_shape(w, (t_shape)s);
  printf("num of shapes %d num of lights %d\n", w.amount_of_shapes, w.amount_of_lights);
  t_image canvas = render(c, w);
  put_image(pair(0, 0), canvas);
  start_mlx();
}
