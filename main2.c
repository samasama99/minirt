#include "src/parsing.h"

int main()
{
  t_res res = pair(800, 600);
  int fd = open("src/test.rt", O_RDONLY);
  if (fd < 0)
	exit(2);
  t_data data;
  data.w = set_amount_of_shapes(100);
  parse(&data, fd, res);
  close(fd);
  correct_ambient(data.w, data.ambient);
  init_mlx(res, pair(0, 0));
  // t_plane floor = plane();
  // floor.material = material();
  // floor.material.color = color(1, 0.9, 0.9);
  // floor.material.specular = 0;
  // floor.material.ambient_color = black();
  // t_plane left_wall = plane();
  // left_wall.material = material();
  // left_wall.t = transform(
  //                         identity(),
  //                         mat4_mult(rotation_y(-M_PI_4), rotation_x(M_PI_2)),
  //                         translation(0, 0, 5)
  //   );
  // left_wall.material = floor.material;
  // t_plane right_wall = plane();
  // right_wall.material = material();
  // right_wall.t = transform(
  //                         identity(),
  //                         mat4_mult(rotation_y(+M_PI_4), rotation_x(M_PI_2)),
  //                         translation(0, 0, 5)
  //   );
  // right_wall.material = floor.material;
  // data.w = add_shape(data.w, (t_shape)floor);
  // data.w = add_shape(data.w, (t_shape)left_wall);
  // data.w = add_shape(data.w, (t_shape)right_wall);
  printf ("%d\n", data.w.amount_of_shapes);
  render(data.c, data.w);
  ft_free();
  start_mlx();
}

