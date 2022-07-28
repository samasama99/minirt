/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:40:30 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 16:16:00 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	fill_image(t_image img, t_pair start, t_pair finish, t_rgb color)
{
	const t_mlx	m = get_mlx_info(NULL);
	int			x;
	int			y;
	int			c;

	c = make_color(color, 0);
	x = start.x;
	y = start.y;
	while (y < finish.height && y < img.res.height)
	{
		while (x < finish.width && x < img.res.width)
		{
			img.buffer[x + (y * (img.res.x))] = c;
			x++;
		}
		x = start.x;
		y++;
	}
}

t_image	create_image(t_res res)
{
	const t_mlx	m = get_mlx_info(NULL);
	t_image		img;
	int			x;
	int			y;
	int			pixel_bits;
	int			endian;
	int			line_bytes;

	x = 0;
	y = 0;
	img.img = mlx_new_image(m.mlx, res.width, res.height);
	img.buffer = (int *)mlx_get_data_addr(img.img, &pixel_bits,
			&line_bytes, &endian);
	while (y < res.height)
	{
		while (x < res.width)
		{
			img.buffer[x + (y * (line_bytes / 4))] = 0x00000000;
			x++;
		}
		x = 0;
		y++;
	}
	img.res = res;
	return (img);
}

void	full_fill_image(t_image img, t_rgb color)
{
	int	x;
	int	y;
	int	c;

	c = make_color(color, 0);
	x = 0;
	y = 0;
	while (y < img.res.height)
	{
		while (x < img.res.width)
		{
			img.buffer[x + (y * (img.res.x))] = c;
			x++;
		}
		x = 0;
		y++;
	}
}
