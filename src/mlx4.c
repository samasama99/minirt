/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:15:25 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/21 14:43:17 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	listen_to(t_event type, int (*func)(), void *param)
{
	const t_mlx	m = get_mlx_info(NULL);

	mlx_hook(m.win, type, 0, func, param);
}

void	update(int (*funct_ptr)(), void *param)
{
	const t_mlx	m = get_mlx_info(NULL);

	mlx_loop_hook(m.mlx, funct_ptr, param);
}

void	clear_window(void)
{
	const t_mlx	m = get_mlx_info(NULL);

	mlx_clear_window(m.mlx, m.win);
}

void	destroy_window(void)
{
	const t_mlx	m = get_mlx_info(NULL);

	mlx_destroy_window(m.mlx, m.win);
}

void	destroy_image(t_image_ptr img)
{
	const t_mlx	m = get_mlx_info(NULL);

	mlx_destroy_image(m.mlx, img);
}

t_image load_image(char *path)
{
  const t_mlx_ptr mlx = get_mlx_info(NULL).mlx;
  int x;
  int y;
  const t_image_ptr img = mlx_xpm_file_to_image(mlx, path, &x, &y);
	t_image_info	info;
	int *buffer = (int *)mlx_get_data_addr(img, &info.pixel_bits,
			&info.line_bytes, &info.endian);

  return (t_image) {.img = img, .buffer = buffer, .res = pair(x, y)};
}


