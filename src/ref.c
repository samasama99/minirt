#include "main.h"
#include <stdio.h>

const double wall_z = 10;
const double wall_size_x = 7;
const double wall_size_y = 7;
const double canvas_pixel_x = 500.0;
const double canvas_pixel_y = 500.0;
const double pixel_size_x = wall_size_x / canvas_pixel_x;
const double pixel_size_y = wall_size_y / canvas_pixel_y;
const double half_x = wall_size_x / 2;
const double half_y = wall_size_y / 2;
const t_point ray_origin = {0, 0, -5, 1};
const t_res res = {canvas_pixel_x, canvas_pixel_y}; 
const t_pair center = {0, 0}; 

int draw_in_canvas(t_image canvas, t_world w) {
  for (int y = 0;y < canvas_pixel_y - 1;++y) {
    double world_y = half_y - pixel_size_y * y;
    for (int x = 0;x < canvas_pixel_x - 1;++x) {
      const double world_x = -half_x + pixel_size_x * x;
      const t_point position = point(world_x, world_y, wall_z);
      const t_ray r = {ray_origin, normalize(sub(position, ray_origin))};
      const t_rgb c = color_at(w, r);
      put_pixel_to_image(canvas, (t_pair){x ,y}, c);
    }
  }
  clear_window();
  put_image((t_pair) {0, 0}, canvas);
  return 0;
}

int main()
{
  init_mlx(res, center);
  t_image canvas = create_image(res);;
  t_world w = default_world();
  draw_in_canvas(canvas, w);
  start_mlx();
}
