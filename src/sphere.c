#include "main.h"
#include <stdio.h>

const double wall_z = 20;
const double wall_size_x = 48;
const double wall_size_y = 48 / (16.0 / 9.0);
const double canvas_pixel_x = 600;
const double canvas_pixel_y = canvas_pixel_x  / (16.0 / 9.0);
const double pixel_size_x = wall_size_x / canvas_pixel_x;
const double pixel_size_y = wall_size_y / canvas_pixel_y;
const double half_x = wall_size_x / 2;
const double half_y = wall_size_y / 2;
const t_pos ray_origin = {0, 0, -12, 1};
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
  if (start == false) {
    canvas = create_image(res);
    s1 = sphere();
    s2 = sphere();
    s3 = sphere();
    start = true;
  }
  s1.t = identity();
  s2.t = identity();
  s3.t = identity();
  s1.t = transform(translation(0, 0, 10), scaling(1, 1, 1), rotation_y(radians(deg)));
  s2.t = transform(translation(0, 0, 14), scaling(1, 1, 1), rotation_y(radians(deg2)));
  s3.t = scaling(2, 2, 2);
  deg += 15;
  deg2 += 20;
  // scale += 0.1;
  printf ("%f\n", deg); 
  printf ("%f %f %f\n", s1.t.l1_c1, s1.t.l1_c2, s1.t.l1_c3);
  printf ("%f %f %f\n", s2.t.l1_c1, s2.t.l1_c2, s2.t.l1_c3);
  // printf ("%d %d\n", s.id, s2.id);

    for (int y = 0;y < canvas_pixel_y - 1;++y) {
      double world_y = half_y - pixel_size_y * y; 
      for (int x = 0;x < canvas_pixel_x - 1;++x) {
        double world_x = -half_x + pixel_size_x * x;
        t_pos position = {world_x, world_y, wall_z, 1};
        t_ray r = {ray_origin, vec_normalize(vec_sub(position, ray_origin), sqrt)};
        t_hit h = intersect_sphere(s1, r);
        t_hit h2 = intersect_sphere(s2, r);
        t_hit h3 = {{hit(h), hit(h2)}, 2};
        t_hit h4 = intersect_sphere(s3, r);
        t_hit h5 = {{hit(h3), hit(h4)}, 2};
        t_intersection inter = hit(h5);
        if (inter.sphere.id == 0 && inter.t > 0) {
            put_pixel_to_image(canvas, (t_pos) {x, y, 0, 1}, (t_rgb) {1, 0, 0});
        } else if (inter.sphere.id == 1 && inter.t > 0) {
            put_pixel_to_image(canvas, (t_pos) {x, y, 0, 1}, (t_rgb) {0, 1, 0});
        } else if (inter.sphere.id == 2 && inter.t > 0) {
            put_pixel_to_image(canvas, (t_pos) {x, y, 0, 1}, (t_rgb) {1, 1, 1});
        } else
            put_pixel_to_image(canvas, (t_pos) {x, y, 0, 1}, (t_rgb) {0, 0, 0});
          
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
