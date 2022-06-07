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
  init_mlx((t_res) {1280, 720}, (t_pair){1280 * 0.5, 720 * 0.5});
  t_image canvas = create_image((t_res) {1280, 720});
  fill_image(canvas, (t_res) {0, 0}, (t_res) {100, 200}, (t_rgb) {1, 0, 0});
  fill_image(canvas, (t_res) {0, 0}, (t_res) {50, 50}, (t_rgb) {0, 1, 0});

  t_pos start = {0, 0, 0};
  t_vec velocity = vec_scalar(vec_normalize((t_vec){+1, -1.8, 0}, sqrt), 20);
  t_projectile proj = {start, velocity};

  t_vec gravity = {0, +0.4, 0};
  t_vec wind = {-0.04, 0, 0};
  t_environment env = {gravity, wind};

  int ticks = 0;
  while (proj.position.y < 720 * 0.5) {
    printf ("%f %f\n", proj.position.x, proj.position.y);
    proj.position = vec_sum(proj.position, proj.velocity);
    put_pixel_to_image(canvas, proj.position, (t_rgb){1, 1, 1});
    proj.velocity = vec_sum(proj.velocity, vec_sum(env.gravity, env.wind));
    ++ticks;
  }
  printf("amount of ticks is %d\n", ticks);
  put_image((t_pair){- 1280, 0}, canvas);
  start_mlx();
}

// start ← point(0, 1, 0)
// velocity ← normalize(vector(1, 1.8, 0)) * 11.25 p ← projectile(start,
// velocity) gravity ← vector(0, -0.1, 0) wind ← vector(-0.01, 0, 0) e ←
// environment(gravity, wind) c ← canvas(900, 550) Putting It Together • 23
