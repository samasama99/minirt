#include "src/main.h"

int main()
{
  const t_res res = pair(400, 400);
  init_mlx(res, pair(0, 0));

  t_shape sp = (t_shape)make_sphere(point(0, 0, 0), 1); 
  sp.super.t = scaling(9, 9, 9);
  sp.super.material.color = color(0, 0, 1);
  t_shape sp2 = (t_shape)make_sphere(point(0, 0, 0), 1); 
  sp2.super.t = transform(scaling(3, 3, 3), translation(0,0,0.5), identity());
  sp2.super.material.color = color(1, 0, 1);
  // t_material plane_material = material();
  // plane_material.color = color(1, 0.9, 0.9);
  // plane_material.specular = 0;

  // t_sphere s = sphere();
  // s.material.color = color(1, 0, 1);
  // // s.t = translation(0, 0, 0);
  // t_sphere s2 = sphere();
  // s2.material.color = color(0, 1, 0);
  // s2.t = mat4_mult(scaling(0.3, 0.3, 0.3), translation(0, 5, -3));
  // t_plane floor = plane();
  // floor.material = plane_material;
  // floor.t = translation(0, -2, 0);
  // floor.normal = apply_transformation(translation(0,-5,0), floor.normal);
  // floor.position = apply_transformation(translation(0,-5,0), floor.position);
  // t_plane ceil = plane();
  // ceil.material = plane_material;
  // ceil.position = point(0, 1, 0);
  // LIGHT
  t_light light = point_light(point(0, 0, -6), color(1, 1, 1));
  // CAMERA ::
  t_camera c = camera(res.x, res.y, radians(85));
  c.transform = view_transform(point(0, 0, -8),
                               point(0, 0, 0),
                               vector(0, 1, 0));
  // WORLD
  t_world w = world();
  w = add_light(w, light);
  w = add_shape(w, sp);
  w = add_shape(w, sp2);
  // w = add_shape(w, (t_shape)ceil);
  // w = add_shape(w, (t_shape)s);
  // w = add_shape(w, (t_shape)s2);
  printf("num of shapes %d num of lights %d\n", w.amount_of_shapes, w.amount_of_lights);
  t_image canvas = render(c, w);
  put_image(pair(0, 0), canvas);
  start_mlx();
}
