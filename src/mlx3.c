/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:40:30 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/09 21:31:28 by orahmoun         ###   ########.fr       */
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

typedef struct s_image_info {
	int			pixel_bits;
	int			endian;
	int			line_bytes;
}		t_image_info;

t_image	create_image(t_res res)
{
	const t_mlx		m = get_mlx_info(NULL);
	t_image			img;
	int				x;
	int				y;
	t_image_info	info;

	x = 0;
	y = 0;
	img.img = mlx_new_image(m.mlx, res.width, res.height);
	img.buffer = (int *)mlx_get_data_addr(img.img, &info.pixel_bits,
			&info.line_bytes, &info.endian);
	while (y < res.height)
	{
		while (x < res.width)
		{
			img.buffer[x + (y * (info.line_bytes / 4))] = 0x00000000;
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
