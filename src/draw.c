/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:43:22 by orahmoun          #+#    #+#             */
/*   Updated: 2022/04/17 16:23:09 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "vector.h"
#define PI 3.141592654
#define MOVEMENT_SPEED 50
#define ROTATION_ANGLE 10
#define SCALE_UP 1.2
#define SCALE_DOWN 0.8

float minf(float x, float y) { return (x < y ? x : y); }
float maxf(float x, float y) { return (x > y ? x : y); }
int min(int x, int y) { return (x < y ? x : y); }
int max(int x, int y) { return (x > y ? x : y); }

void draw_line(t_vec v1, t_vec v2, t_mlx info) {
  float x;
  float y;
  float m;
  float b;

  x = 0;
  y = 0;
  m = (v2.y - v1.y) / (v2.x - v1.x);
  b = v1.y - m * v1.x;
  while (y < info.resolution.height) {
    while (x < info.resolution.width) {
      if ((y == round(m * x + b) || y == floor(m * x + b)) &&
          (vec_distance((t_vec){{x, y, 0}}, v1, sqrtf) <=
           vec_distance(v1, v2, sqrtf)) &&
          (vec_distance((t_vec){{x, y, 0}}, v2, sqrtf) <=
           vec_distance(v1, v2, sqrtf))) {
        mlx_pixel_put(info.win, info.win, x, y, 0x0000FFFF);
      }
      x += 1;
    }
    x = 0;
    y += 1;
  }
}



void draw_cube(t_object cube, t_mlx info) {
  draw_line(cube.points[0], cube.points[1], info); // a -> b
  draw_line(cube.points[1], cube.points[2], info); // b -> c
  draw_line(cube.points[2], cube.points[3], info); // c -> d
  draw_line(cube.points[3], cube.points[0], info); // d -> a

  draw_line(cube.points[4], cube.points[5], info); // e -> f
  draw_line(cube.points[5], cube.points[6], info); // f -> g
  draw_line(cube.points[6], cube.points[7], info); // g -> h
  draw_line(cube.points[7], cube.points[4], info); // h -> e

  draw_line(cube.points[0], cube.points[4], info); // a -> e
  draw_line(cube.points[1], cube.points[5], info); //

  draw_line(cube.points[3], cube.points[7], info); // d -> h
  draw_line(cube.points[2], cube.points[6], info); // c -> g
}


t_vec get_direction_vector(t_key key)
{
  t_vec direction;

  if (key == W_KEY)
      direction = (t_vec){{0, -1, 0}};
  if (key == S_KEY)
      direction = (t_vec){{0, +1, 0}};
  if (key == D_KEY)
      direction = (t_vec){{1, 0, 0}};
  if (key == A_KEY)
      direction = (t_vec){{-1, 0, 0}};
  return direction;
}

t_pos move(t_pos pos, int keycode, float speed)
{
  t_pos new_pos;
  t_vec direction;

  direction = get_direction_vector(keycode);
  new_pos = vec_sum(pos, vec_scalar(direction, speed));
  return (new_pos);
}

typedef enum e_axis {x_axis, y_axis, z_axis} t_axis;
t_matrix3 get_rotation_matrix(t_axis axis, float angle)
{
  float     rad;
  t_matrix3 rot_matrix; 

  rad = (angle * PI) / 180;
  if (axis == x_axis)
    rot_matrix = (t_matrix3){{
      1, 0, 0,
      0, cosf(rad), sinf(rad),
      0, -sinf(rad), cosf(rad)
    }};
  if (axis == y_axis)
    rot_matrix = (t_matrix3){{
      cosf(rad), 0, -sinf(rad),
      0, 1, 0,
      sinf(rad), 0, cosf(rad)
    }};
  if (axis == z_axis)
    rot_matrix = (t_matrix3){{
      cosf(rad), sinf(rad), 0,
      -sinf(rad), cosf(rad), 0,
      0, 0, 1
    }};
  return (rot_matrix);
}

t_pos rotate(t_pos pos, t_pos origin, int axis, float angle)
{
  t_pos     new_pos;
  t_matrix3 rot_matrix; 

  new_pos = vec_sub(pos, origin);
  rot_matrix = get_rotation_matrix(axis, angle);
  new_pos = vec3_multi_mat3(new_pos, rot_matrix);
  new_pos = vec_sum(new_pos, origin);
  return (new_pos);
}

t_pos scale(t_pos pos, t_pos center, int keycode)
{
  t_pos new_pos;
  t_matrix3 scale_matrix;

  new_pos = vec_sub(pos, center);
  if (keycode == PLUS_KEY)
    scale_matrix = (t_matrix3){{
      SCALE_UP, 0, 0,
      0, SCALE_UP, 0,
      0, 0, SCALE_UP
    }};
  if (keycode == MINUS_KEY)
    scale_matrix = (t_matrix3){{
      SCALE_DOWN, 0, 0,
      0, SCALE_DOWN, 0,
      0, 0, SCALE_DOWN
    }};
  new_pos = vec3_multi_mat3(new_pos, scale_matrix);
  new_pos = vec_sum(new_pos, center);
  return (new_pos);
}

void  move_each(t_object *object, t_key key)
{
  size_t i;

  i = 0;
  while (i < object->size) 
  {
      object->points[i] = move(object->points[i], key, MOVEMENT_SPEED);
      i++;
  }
}

void  scale_each(t_object *object, t_key key)
{
  size_t  i;
  t_pos   origin;

  i = 0;
  origin = (t_pos) {{0, 0, 0}};
  while (i < object->size)
  {
    origin.x += object->points[i].x;
    origin.y += object->points[i].y;
    origin.z += object->points[i].z;
    i++;
  }
  i = 0;
  origin = vec_scalar(origin, (float)(1 / (float)object->size));
  while (i < object->size) 
  {
      object->points[i] = scale(object->points[i], origin, key);
      i++;
  }
}

static void key_management(int keycode, t_object *object)
{
  if (keycode == W_KEY || keycode == S_KEY
    || keycode == D_KEY || keycode == A_KEY)
      move_each(object, keycode);
  if (keycode == RIGHT_ARROW || keycode == LEFT_ARROW)
      rotate_each(object, keycode, z_axis, (keycode == RIGHT_ARROW ? ROTATION_ANGLE : -ROTATION_ANGLE));
  if (keycode == UP_ARROW || keycode == DOWN_ARROW)
      rotate_each(object, keycode, x_axis, (keycode == UP_ARROW ? ROTATION_ANGLE : -ROTATION_ANGLE));
  if (keycode == PLUS_KEY || keycode == MINUS_KEY)
    scale_each(object, keycode);
}

// int routine(t_object *cube)
// {
//   t_data *data = my_data(NULL);
//   draw_cube(*cube, data->mlx_info);
//   return 0;
// }

static int key_hook(int keycode, t_data *data) 
{
  static bool begin;
  t_assets assets;
  t_mlx mlx_info;
  // static t_pos pos[1024];
  // static t_pos center;
  my_data(data);
  mlx_info = data->mlx_info;
  assets = data->assets;
  mlx_clear_window(mlx_info.mlx, mlx_info.win);
  if (keycode == ESC)
    exit(1);

  static t_object cube = {.size = 8};
  if (begin == false)
  {
    cube.points[0] = vec_init(0, 0, -50);   // A
    cube.points[1] = vec_init(100, 0, -50); // B
    cube.points[2] = vec_init(100, 0, -50); // C
	 cube.points[3] = vec_init(0, 0, -50);   // D

    cube.points[4] = vec_init(0, 100, 50);   // E
    cube.points[5] = vec_init(100, 100, 50); // F
    cube.points[6] = vec_init(100, 100, 50); // G
    cube.points[7] = vec_init(0, 100, 50);   // H

	 cube.points[2] = vec_sum(cube.points[2], (t_vec){{35, 35, 0}});
	 cube.points[3] = vec_sum(cube.points[3], (t_vec){{35, 35, 0}});
	 cube.points[6] = vec_sum(cube.points[6], (t_vec){{35, 35, 0}});
	 cube.points[7] = vec_sum(cube.points[7], (t_vec){{35, 35, 0}});
    // center = cube_center(pos);
    // mlx_loop_hook(mlx_info.mlx, routine, &cube);
    begin = true;
  }
  key_management(keycode, &cube);
  draw_cube(cube, mlx_info);

  draw_line_dda((t_vec) {0, 0, 0}, (t_vec) {500, 500, 0}, mlx_info);
  return (0);
}

static int destroy_window(t_data *data)
{
  mlx_destroy_window(data->mlx_info.mlx, data->mlx_info.win);
  exit(1);
}

void handling_events(t_data *data)
{
  t_mlx mlx_info;

  mlx_info = data->mlx_info;
  mlx_hook(mlx_info.win, 2, 1L << 0, key_hook, data);
  mlx_hook(mlx_info.win, 17, 1L << 0, destroy_window, data);
}
