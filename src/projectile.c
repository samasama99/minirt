#include "main.h"
#include <stdio.h>

typedef struct s_projectile {
  t_pos position;
  t_vec velocity;
} t_projectile;

typedef struct s_environment {
  t_pos gravity;
  t_vec wind;
} t_environment;

int main() {
  t_data data;
  data.mlx_info = init_mlx((t_res) {1280, 720});
  t_canvas canvas = create_canvas(data.mlx_info, data.mlx_info.resolution);
  // t_canvas canvas = create_canvas(data.mlx_info, (t_res) {20, 10});
  fill_canvas(canvas, (t_res) {0, 0}, (t_res) {100, 200}, (t_rgb) {1, 0, 0});
  fill_canvas(canvas, (t_res) {0, 0}, (t_res) {50, 50}, (t_rgb) {0, 1, 0});

  printf ("%d %d\n", canvas.res.x, canvas.res.y);
  printf ("%d %d\n", data.mlx_info.resolution.x, data.mlx_info.resolution.y);
  t_pos start = {0, data.mlx_info.resolution.y - 1, 0};
  // t_vec velocity = vec_scalar(vec_normalize((t_vec){+1, -1.8, 0}, sqrt), 11.25);
  t_vec velocity = vec_scalar(vec_normalize((t_vec){+1, -1.8, 0}, sqrt), 20);
  t_projectile proj = {start, velocity};

  // t_vec gravity = {0, +0.1, 0};
  t_vec gravity = {0, +0.4, 0};
  t_vec wind = {-0.04, 0, 0};
  t_environment env = {gravity, wind};

  int ticks = 0;
  while (proj.position.y < data.mlx_info.resolution.y) {
    proj.position = vec_sum(proj.position, proj.velocity);
    put_pixel_to_canvas(canvas, proj.position, (t_rgb){1, 1, 1});
    proj.velocity = vec_sum(proj.velocity, vec_sum(env.gravity, env.wind));
    ++ticks;
  }
  printf("amount of ticks is %d\n", ticks);
  put_image(data, (t_pair){0, 0}, canvas.img);
  mlx_loop(data.mlx_info.mlx);
}

// start ← point(0, 1, 0)
// velocity ← normalize(vector(1, 1.8, 0)) * 11.25 p ← projectile(start,
// velocity) gravity ← vector(0, -0.1, 0) wind ← vector(-0.01, 0, 0) e ←
// environment(gravity, wind) c ← canvas(900, 550) Putting It Together • 23
