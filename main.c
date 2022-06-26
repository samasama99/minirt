#include "src/main.h"

int main()
{
  const t_res res = pair(1200, 600);
  init_mlx(res, pair(0, 0));

  t_plane floor = plane();
  floor.material = material();
  floor.material.color = color(1, 0.9, 0.9);
  floor.material.specular = 0;
  floor.material.ambient_light_color = black();
  t_plane left_wall = plane();
  left_wall.material = material();
  left_wall.t = transform(
                          identity(),
                          mat4_mult(rotation_y(-M_PI_4), rotation_x(M_PI_2)),
                          translation(0, 0, 5)
    );
  left_wall.material = floor.material;
  t_plane right_wall = plane();
  right_wall.material = material();
  right_wall.t = transform(
                          identity(),
                          mat4_mult(rotation_y(+M_PI_4), rotation_x(M_PI_2)),
                          translation(0, 0, 5)
    );
  right_wall.material = floor.material;

  t_sphere middle = sphere();
  middle.t = translation(-0.5, 1, 0.5);
  middle.material = material();
  middle.material.color = color(0.1, 1, 0.5);
  middle.material.diffuse = 0.7;
  middle.material.specular = 0.3;
  middle.material.shininess = 10;
  middle.material.ambient_ratio = 0;
  middle.material.ambient_light_color = black();

  t_sphere right = sphere();
  right.t = mat4_mult(translation(1.5, 0.5, -0.5),
                      scaling(0.5, 0.5, 0.5));
  right.material = material();
  right.material.color = color(0.5, 1, 0.1);
  right.material.diffuse = 0.7;
  right.material.specular = 0.3;
  right.material.ambient_light_color = black();

  t_sphere left = sphere();
  left.material = material();
  left.t = mat4_mult(translation(-1.5, 0.33, -0.75),
                      scaling(0.33, 0.33, 0.33));
  left.material.color = color(1, 0.8, 0.1);
  left.material.diffuse = 0.7;
  left.material.specular = 0.3;
  left.material.ambient_light_color = black();

  t_world w = set_amount_of_shapes(6);
  
  t_light light = point_light(point(-1, 1, -1), color(1, 1, 1));
  t_camera c = camera(res.x, res.y, M_PI / 3);
  c.transform = view_transform(point(0, 1.5, -5),
                               point(0, 1, 0),
                               vector(0, 1, 0));
  w.light = light;

  w = add_shape(w, (t_shape)floor);
  w = add_shape(w, (t_shape)left_wall);
  w = add_shape(w, (t_shape)right_wall);

  w = add_shape(w, (t_shape)middle);
  w = add_shape(w, (t_shape)right);
  w = add_shape(w, (t_shape)left);
  printf("num of shapes %d\n", w.amount_of_shapes);
  render(c, w);
  start_mlx();
}
