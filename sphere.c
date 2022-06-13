#include "main.h"
#include <stdio.h>

const double wall_z = 20;
const double wall_size_x = 48;
const double wall_size_y = 27;
const double canvas_pixel_x = 400;
const double canvas_pixel_y = canvas_pixel_x / (16.0 / 9.0);
const double pixel_size_x = wall_size_x / canvas_pixel_x;
const double pixel_size_y = wall_size_y / canvas_pixel_y;
const double half_x = wall_size_x / 2;
const double half_y = wall_size_y / 2;
const t_point ray_origin = {0, 0, -15, 1};
const t_res res = {canvas_pixel_x, canvas_pixel_y }; 
const t_pair center = {0, 0}; 

int f(void *ptr) {
  static bool start;
  static t_image canvas;
  static t_sphere s1;
  static t_sphere s2;
  static t_sphere s3;
  static double deg;
  static double deg2;
  static double scale = 1;
  const t_light light = {point(10, 10, -15), (t_rgb) {1, 1, 1}};
  const t_light light2 = {point(-10, -10, -15), (t_rgb) {0, 0, 0}};

  if (start == false) {
    canvas = create_image(res);
    s1 = sphere();
    t_material m = {
        .color = {1, 0.2, 1},
        .ambient = 0.1,
        .diffuse = 0.9,
        .specular = 0.0,
        .shininess = 200.0,
    };
    s2 = sphere();
    s3 = sphere();
    s1.material = m;
    s2.material = m;
    s3.material = m;
    start = true;
  }
  s1.t = identity();
  s2.t = identity();
  s3.t = identity();
  s1.t = transform(translation(0, 0, 6), scaling(0.5, 0.5, 0.5), rotation_y(radians(deg)));
  s2.t = transform(translation(0, 0, 8), scaling(0.6, 0.6, 0.6), rotation_y(radians(deg2)));
  s3.t = scaling(2, 2, 2);
  deg += 15;
  deg2 += 20;
  for (int y = 0;y < canvas_pixel_y - 1;++y) {
    double world_y = half_y - pixel_size_y * y; 
    for (int x = 0;x < canvas_pixel_x - 1;++x) {
      double world_x = -half_x + pixel_size_x * x;
      t_point position = {world_x, world_y, wall_z, 1};
      t_ray r = {ray_origin, normalize(sub(position, ray_origin))};
      t_hit h = intersect_sphere(s1, r);
      t_hit h2 = intersect_sphere(s2, r);
      t_hit h3 = {{hit(h), hit(h2)}, 2};
      t_hit h4 = intersect_sphere(s3, r);
      t_hit h5 = {{hit(h3), hit(h4)}, 2};
      t_intersection inter = hit(h5);
      if (inter.sphere.id == 0 && inter.t > 0) {
          t_point p = ray_position(r, inter.t);
          t_norm normal = normal_at(inter.sphere, p);
          t_vec eye = opose(r.direction);
          t_rgb color = lighting(inter.sphere.material, light, p, eye, normal);
          t_rgb color2 = lighting(inter.sphere.material, light2, p, eye, normal);
          color = rgb_sum(color, color2);
          put_pixel_to_image(canvas, pair(x, y), color);
      } else if (inter.sphere.id == 1 && inter.t > 0) {
          t_point p = ray_position(r, inter.t);
          t_norm normal = normal_at(inter.sphere, p);
          t_vec eye = opose(r.direction);
          t_rgb color = lighting(inter.sphere.material, light, p, eye, normal);
          t_rgb color2 = lighting(inter.sphere.material, light2, p, eye, normal);
          color = rgb_sum(color, color2);
          put_pixel_to_image(canvas, pair(x, y), color);
      } else if (inter.sphere.id == 2 && inter.t > 0) {
          t_point p = ray_position(r, inter.t);
          t_norm normal = normal_at(inter.sphere, p);
          t_vec eye = opose(r.direction);
          t_rgb color = lighting(inter.sphere.material, light, p, eye, normal);
          t_rgb color2 = lighting(inter.sphere.material, light2, p, eye, normal);
          color = rgb_sum(color, color2);
          put_pixel_to_image(canvas, pair(x, y), color);
      } else
          put_pixel_to_image(canvas, pair(x, y), black());
        
    }
  }
  clear_window();
  put_image((t_pair) {0, 0}, canvas);
  return 0;
}

int main()
{
  init_mlx(res, center);
  // f(NULL);
  loop_hook(f, NULL);
  start_mlx();
}
