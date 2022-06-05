#include "main.h"
#include "vector.h"
#include <stdio.h>
#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000
// #define WIN_WIDTH 256
// #define WIN_HEIGHT 256

typedef struct s_ray {
    t_pos origin;
    t_vec direction;
}               t_ray;

typedef struct s_sphere {
    t_pos center;
    double radius;
}               t_sphere;

t_vec vec_normal_product(t_vec v1, t_vec v2) {
  t_vec v;

  v = (t_vec) {{
    v1.x * v2.x,
    v1.y * v2.y,
    v1.z * v2.z,
  }};
  return v;
}

// center of the sphere, radius of the sphere, the ray
bool hit_sphere(const t_sphere sphere, const t_ray r) {
  // e is the origin of the ray and d is the direction
  // p(t) = e + td
  // (p - c).(p - c) - R^2 = 0
  // (d.d)t^2 + 2d.(e - c)t + (e - c).(e - c) - R^2 = 0
  // discriminant  = B^2 - 4AC if there is a solution then discriminant >= 0
    t_vec e_c = vec_sub(r.origin, sphere.center); // e - c
    double a = vec_dot_product(r.direction, r.direction);
    double b = 2.0 * vec_dot_product(e_c, r.direction);
    double c = vec_dot_product(e_c, e_c) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;
    printf("dis %f\n", discriminant);
    return (discriminant > 0);
}

t_rgb ray_color(const t_ray ray) {
    if (hit_sphere((t_sphere) {{0, 0, -1}, 0.1}, ray))
      return (t_rgb) {1, 0, 0};

    t_vec unit_direction = vec_normalize(ray.direction, sqrt);
    double t = 0.5 * (unit_direction.y + 1.0);
    return rgb_sum(rgb_scalar((t_rgb) {1.0, 1.0, 1.0},  1.0 - t)
                  , rgb_scalar((t_rgb) {0.5, 0.7, 1.0}, t));
}

t_pos ray_at(t_ray ray, double t) {
   return vec_sub(ray.origin, vec_scalar(ray.direction, t));
}

int main() {

    t_data	data;

    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = (int)(image_width / aspect_ratio);
    printf("image_width %d ; image_height %d\n", image_width, image_height);

    // INIT MLX
    data.mlx_info = init_mlx((t_res) {image_width, image_height});

    // Camera
    double viewport_height = 0.5;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 4.0;

    t_pos origin = {0, 0, 0};
    t_vec horizontal = {viewport_width, 0, 0};
    t_vec vertical = {0, viewport_height, 0};
    t_pos lower_left_corner = vec_sub(origin
                                      , vec_sub(vec_sub(vec_scalar(horizontal, 0.5)
                                                        , vec_scalar( vertical, 0.5))
                                                , (t_vec) {0, 0, focal_length}));

    // Render
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            double u = (double)(i) / (image_width - 1);
            double v = (double)(j) / (image_height - 1);
            t_ray r = {origin
                      , vec_sum(lower_left_corner
                                , vec_sub(vec_sum(vec_scalar(horizontal, u)
                                                  , vec_scalar(vertical, v))
                                          , origin))};
            t_rgb pixel_color = ray_color(r);
            mlx_pixel_put(data.mlx_info.mlx, data.mlx_info.win
                          , i, j, make_color(pixel_color, 0));
        }
    }
	  mlx_loop(data.mlx_info.mlx);
}

// int main() {

// 	t_data	data;

// 	// INIT MLX

// 	data.mlx_info = init_mlx((t_res){{ WIN_WIDTH, WIN_HEIGHT }});

//   // Image

//   const int image_width = WIN_WIDTH;
//   const int image_height = WIN_HEIGHT;

//   // Render

//   for (int j = image_height-1; j >= 0; --j) {
//       for (int i = 0; i < image_width; ++i) {
//           double r = (double)(i) / (image_width - 1);
//           double g = (double)(j) / (image_height - 1);
//           double b = 0.25;

//           int ir = (int)(255.999 * r);
//           int ig = (int)(255.999 * g);
//           int ib = (int)(255.999 * b);
//           t_rgb color = {{.blue = ib, .green = ig, .red = ir, .alpha = 0}};

//           mlx_pixel_put(data.mlx_info.mlx, data.mlx_info.win
//                         , i, j, color.svalue);
//       }
//   }
// 	mlx_loop(data.mlx_info.mlx);
// }
