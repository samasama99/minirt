/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:40:30 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/15 15:54:07 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	fill_image(t_image img, t_pair start, t_pair finish, t_rgb color)
{
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
	const t_mlx		m = get_mlx_info(NULL);
	t_image			img;
	t_image_info	info;

	img.img = mlx_new_image(m.mlx, res.width, res.height);
	img.buffer = (int *)mlx_get_data_addr(img.img, &info.pixel_bits,
			&info.line_bytes, &info.endian);
	ft_bzero(img.buffer, (res.width * res.height) * sizeof(int));
	img.res = res;
	return (img);
}
