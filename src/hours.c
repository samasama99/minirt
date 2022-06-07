#include "main.h"
#include <stdio.h>

t_pair pp(t_pos p) {
  return (t_pair) {p.x, p.y};
}

int main() {
  const t_res window_res = {500, 500};
  const t_res center = {250, 250};
  init_mlx(window_res, center);
  // t_image dot = create_image((t_res) {6, 6});
  // full_fill_image(dot, (t_rgb) {1, 0, 0});
  // t_pos point = {0, -200, 0};
  // t_deg deg = 0;
  // t_matrix4 rotate_30deg = rotation_z(radians(30));
  // t_pair p;
  // while (deg != 360) {
  //   p = pp(point);
  //   put_image(p, dot);
  //   deg += 30;
  //   point = mat4_multi_pos3(rotate_30deg, point);
  // }
  start_mlx();
}

