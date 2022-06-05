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

win_ptr init_win(mlx_ptr mlx, t_res resolution) {
  win_ptr win;

  if (mlx == NULL) {
    perror("Error ");
    exit(1);
  }
  win = mlx_new_window(mlx, resolution.width, resolution.height, "mlx");
  if (win == NULL) {
    {
      perror("Error ");
      exit(1);
    }
  }
  return (win);
}

t_mlx init_mlx(t_res resolution) {
  t_mlx mlx_info;
  mlx_ptr mlx;
  win_ptr win;

  mlx = mlx_init();
  win = init_win(mlx, resolution);
  mlx_info = (t_mlx){
      .mlx = mlx,
      .win = win,
      .resolution = resolution,
  };
  return (mlx_info);
}

int make_color(t_rgb c, float alpha) {
  t_color color;

  color.blue = c.blue * 255.999;
  color.green = c.green * 255.999;
  color.red = c.red * 255.999;
  color.alpha = alpha * 255.999;
  return color.color;
}

void put_pixel(t_data data, t_pair pos, t_rgb rgb) {
  mlx_pixel_put(data.mlx_info.mlx, data.mlx_info.win, pos.x, pos.y,
                make_color(rgb, 0));
}

void put_image(t_data data, t_pair pos, image img) {
  printf("x %d y %d\n", pos.x, pos.y);
  mlx_put_image_to_window(data.mlx_info.mlx, data.mlx_info.win, img, pos.x,
                          pos.y);
}

void put_pixel_to_image(t_image img, t_pos p, t_rgb color) {
  t_pair pos;

  pos.x = p.x;
  pos.y = p.y;
  if (pos.x >= 0 && pos.x < img.res.x) {
    if (pos.y >= 0 && pos.y < img.res.y) {
      printf("x %d y %d\n", pos.x, pos.y);
      img.buffer[pos.x + (pos.y * img.res.x)] = make_color(color, 0);
    }
  }
}

void fill_image(t_image img, t_pair start, t_pair finish, t_rgb color) {
  int x;
  int y;
  int c;

  c = make_color(color, 0);
  x = start.x;
  y = start.y;
  while (y < finish.height && y < img.res.height) {
    while (x < finish.width && x < img.res.width) {
      // printf ("index %d %d\n", canvas.res.x * 4,x + (y * (canvas.res.x)));
      img.buffer[x + (y * (img.res.x))] = c;
      x++;
    }
    x = start.x;
    y++;
  }
}

t_image create_image(t_mlx mlx, t_res res) {
  t_image img;
  int x;
  int y;
  int pixel_bits;
  int endian;
  int line_bytes;

  x = 0;
  y = 0;
  img.img = mlx_new_image(mlx.mlx, res.width, res.height);
  img.buffer =
      (int *)mlx_get_data_addr(img.img, &pixel_bits, &line_bytes, &endian);
  while (y < res.height) {
    while (x < res.width) {
      // printf ("index (line bytes %d) bytes : %d\n", line_bytes,x + (y *
      // (line_bytes / 4)));
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
      // printf ("index %d %d\n", canvas.res.x * 4,x + (y * (canvas.res.x)));
      img.buffer[x + (y * (img.res.x))] = c;
      x++;
    }
    x = 0;
    y++;
  }
}
