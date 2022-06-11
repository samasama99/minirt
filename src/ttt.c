#include "main.h"

int main()
{
  init_mlx(pair(400, 400), pair(0, 0));
  t_world w = default_world();
  w.spheres[0].t = translation(0, 0, 2);
  w.spheres[0].material.color = color(1,1,1);
  // w.spheres[0].material.color = color(1, 0, 1);
  // w.spheres[1].t = scaling(200, 200, 200);
  // w.spheres[1].material.color = color(0, 0, 1);
  // w.spheres[1].t = translation(0, 200, -200);
  w.lights[0].position = point(0, 3, -5);
  t_camera c = camera(400, 400, radians(20));
  const t_point from = point(0, 3, -5);
  const t_point to = point(0, 0, 0);
  const t_point up = vector(0, 1, 0);
  // 
  c.transform = view_transform(from, to, up);
  t_image canvas = render(c, w);
  put_image(pair(0, 0), canvas);
  start_mlx();
}
