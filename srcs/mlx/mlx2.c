/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:37:55 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/15 13:00:28 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_pixel(t_pair pos, t_rgb rgb)
{
	const t_mlx	m = get_mlx_info(NULL);

	mlx_pixel_put(m.mlx, m.win, pos.x, pos.y, make_color(rgb, 0));
}

void	put_image(t_pair pos, t_image img)
{
	const t_mlx	m = get_mlx_info(NULL);

	mlx_put_image_to_window(m.mlx, m.win, img.img, pos.x, pos.y);
}

void	put_pixel_to_image(t_image img, t_pair p, t_rgb color)
{
	if (p.x >= 0 && p.x < img.res.x)
	{
		if (p.y >= 0 && p.y < img.res.y)
			img.buffer[p.x + (p.y * img.res.x)] = make_color(color, 0);
	}
}

int	pixel_at(t_image img, t_pair p)
{
	return (img.buffer[p.x + (p.y * img.res.x)]);
}

void	put_string(int x, int y, char *string)
{
	const t_mlx	m = get_mlx_info(NULL);

	mlx_string_put(m.mlx, m.win, x,
		y, make_color(color(0.5, 0.5, 0.5), 0), string);
}
