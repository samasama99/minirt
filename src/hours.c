#include "main.h"
#include <stdio.h>

t_pair pp(t_pos p) {
  printf("avv %f %f\n", p.x, p.y);
  return (t_pair) {
    p.x,
    p.y,
  };
}

t_pair vc(t_pair p, t_pair center) {
  return (t_pair) {
    p.x + center.x,
    p.y + center.y,
  };
}

int main() {
  t_data data;
  data.mlx_info = init_mlx((t_res) {500, 500});
  // t_image canvas = create_image(data.mlx_info, data.mlx_info.resolution);
  t_image dot = create_image(data.mlx_info, (t_res) {6, 6});
  full_fill_image(dot, (t_rgb) {1, 0, 0});
  // t_pair p = {.x = 447, .y = 247};
  // put_image(data, p, dot.img);
  t_pos point = {0, -200, 0};
  t_rad rad = radians(30);
  t_deg deg = 0;
  t_matrix4 rotate = rotation_z(rad);
  t_pair p;
  while (deg != 360) {
    p = vc(pp(point), (t_pair){250, 250});
    put_image(data, p, dot.img);
    deg += 30;
    rotate = rotation_z(rad);
    point = mat4_multi_pos3(rotate, point);
  }
  mlx_loop(data.mlx_info.mlx);
}

