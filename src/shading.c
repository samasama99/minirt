#include "main.h"
#include <stdio.h>

const double wall_z = 10;
const double wall_size_x = 7;
const double wall_size_y = 7;
const double canvas_pixel_x = 300.0;
const double canvas_pixel_y = 300.0;
const double pixel_size_x = wall_size_x / canvas_pixel_x;
const double pixel_size_y = wall_size_y / canvas_pixel_y;
const double half_x = wall_size_x / 2;
const double half_y = wall_size_y / 2;
const t_pos ray_origin = {0, 0, -5, 1};
const t_res res = {canvas_pixel_x, canvas_pixel_y}; 
const t_pair center = {0, 0}; 

int f(void *ptr) {
  t_image canvas;
  t_sphere s;
  const t_light light = point_light(point(10, 0, 0), (t_rgb) {1, 1, 1});

  canvas = create_image(res);
  s = sphere();
  s.t = transform(scaling(-1, 1, -1), identity(), identity());
  for (int y = 0;y < canvas_pixel_y - 1;++y) {
    double world_y = half_y - pixel_size_y * y; 
    for (int x = 0;x < canvas_pixel_x - 1;++x) {
      double world_x = -half_x + pixel_size_x * x;
      t_pos position = {world_x, world_y, wall_z, 1};
      t_ray r = {ray_origin, vec_normalize(vec_sub(position, ray_origin), sqrt)};
      t_hit h = intersect_sphere(s, r);
      t_intersection inter = hit(h);
      if (inter.t > 0) {
          t_pos p = ray_position(r, inter.t);
          t_norm normal = normal_at(inter.sphere, p);
          t_vec eye = vec_opose(r.direction);
          t_rgb color = lighting(inter.sphere.material, light, p, eye, normal);
          put_pixel_to_image(canvas, point(x, y, 0), color);
      } else
          put_pixel_to_image(canvas, point(x, y, 0), (t_rgb) {0, 0, 0});
        
    }
  }
  clear_window();
  put_image((t_pair) {0, 0}, canvas);
  return 0;
}

int main()
{
  init_mlx(res, center);
  f(NULL);
  // loop_hook(f, NULL);
  start_mlx();
}
