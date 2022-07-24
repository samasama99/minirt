/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:52:58 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/18 21:32:13 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


t_mlx get_mlx_info(t_mlx *mlx)
{
  static t_mlx static_mlx;

  if (mlx)
    static_mlx = *mlx;
  return static_mlx;
}

void start()
{
  const t_mlx m = get_mlx_info(NULL);
  mlx_loop(m.mlx);
}


win_ptr init_win(mlx_ptr mlx, t_res resolution, char *title) {
  win_ptr win;

  if (mlx == NULL) {
    perror("Error ");
    exit(1);
  }
  win = mlx_new_window(mlx,
                       resolution.width, resolution.height,
                       title);
  if (win == NULL)
  {
	  perror("Error ");
	  exit(1);
  }
  return (win);
}

t_mlx init(t_res resolution, char *title) {
  t_mlx mlx_info;
  mlx_ptr mlx;
  win_ptr win;

  mlx = mlx_init();
  win = init_win(mlx, resolution, title);
  mlx_info = (t_mlx){
	  .mlx = mlx,
	  .win = win,
	  .resolution = resolution,
  };
  get_mlx_info(&mlx_info);
  return (mlx_info);
}

int make_color(t_rgb c, float alpha) {
  t_color color;

  c.blue = clamp(c.blue, 0, 1);
  c.green = clamp(c.green, 0, 1);
  c.red = clamp(c.red, 0, 1);
  color.blue = c.blue * 255.0;
  color.green = c.green * 255.0;
  color.red = c.red * 255.0;
  color.alpha = alpha * 255.0;
  return color.color;
}

void put_pixel(t_pair pos, t_rgb rgb) {
  const t_mlx m = get_mlx_info(NULL);
  mlx_pixel_put(m.mlx, m.win, pos.x, pos.y,
				make_color(rgb, 0));
}

void put_image(t_pair pos, t_image img) {
  const t_mlx m = get_mlx_info(NULL);
  mlx_put_image_to_window(m.mlx, m.win, img.img, pos.x, pos.y);
}

void put_pixel_to_image(t_image img, t_pair p, t_rgb color) {
  const t_mlx m = get_mlx_info(NULL);
  if (p.x >= 0 && p.x < img.res.x) {
    if (p.y >= 0 && p.y < img.res.y) {
      img.buffer[p.x + (p.y * img.res.x)] = make_color(color, 0);
    }
  }
}

int pixel_at(t_image img, t_pair p) {
	return img.buffer[p.x + (p.y * img.res.x)];
}

void put_string(int x, int y, char *string)
{
  const t_mlx m = get_mlx_info(NULL);
  mlx_string_put(m.mlx, m.win, x, y,
                 make_color(color(0.5,0.5,0.5), 0),
                 string);
}

void fill_image(t_image img, t_pair start, t_pair finish, t_rgb color) {
  const t_mlx m = get_mlx_info(NULL);
  int x;
  int y;
  int c;

  c = make_color(color, 0);
  x = start.x;
  y = start.y;
  while (y < finish.height && y < img.res.height) {
    while (x < finish.width && x < img.res.width) {
      img.buffer[x + (y * (img.res.x))] = c;
      x++;
    }
    x = start.x;
    y++;
  }
}

t_image create_image(t_res res) {
  const t_mlx m = get_mlx_info(NULL);
  t_image img;
  int x;
  int y;
  int pixel_bits;
  int endian;
  int line_bytes;

  x = 0;
  y = 0;
  img.img = mlx_new_image(m.mlx, res.width, res.height);
  img.buffer =
	  (int *)mlx_get_data_addr(img.img, &pixel_bits, &line_bytes, &endian);
  while (y < res.height) {
	while (x < res.width) {
	  img.buffer[x + (y * (line_bytes / 4))] = 0x00000000;
	  x++;
	}
	x = 0;
	y++;
  }
  img.res = res;
  return (img);
}

void full_fill_image(t_image img, t_rgb color) {
  int x;
  int y;
  int c;

  c = make_color(color, 0);
  x = 0;
  y = 0;
  while (y < img.res.height) {
    while (x < img.res.width) {
      img.buffer[x + (y * (img.res.x))] = c;
      x++;
    }
	x = 0;
	y++;
  }
}

void listen_to(t_event type, int (*func)(), void *param)
{
  const t_mlx m = get_mlx_info(NULL);
  mlx_hook(m.win, type, 0, func, param);
}

void update(int (*funct_ptr)(), void *param) {
  const t_mlx m = get_mlx_info(NULL);
  mlx_loop_hook(m.mlx, funct_ptr, param);
}

void clear_window() {
  const t_mlx m = get_mlx_info(NULL);
  mlx_clear_window(m.mlx, m.win);
}
