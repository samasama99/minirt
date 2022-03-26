/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:53:37 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/21 17:45:27 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// #define WIN_WIDTH 1920
// #define WIN_HEIGHT 1080
#define WIN_WIDTH 1000
#define WIN_HEIGHT 1000

t_data *my_data(t_data *data)
{
	static t_data *in_data;

	if (data == NULL)
		return in_data;
	else
	{
		in_data = data;
		return (data);
	}
}

image	make_point(const uint16_t width
						, const uint16_t height
						, const uint32_t color
						, const t_mlx mlx_info)
{
	uint_fast16_t x;	
	uint_fast16_t y;
	image				img;
	int				pixel_bits;
	int				endian;
	int				line_bytes;
	int				*buffer;

	x = 0;	
	y = 0;
	img = mlx_new_image(mlx_info.mlx
								, width, height);
	buffer = (int *)mlx_get_data_addr(img
						, &pixel_bits, &line_bytes, &endian);
	while (y < height)
	{
		while (x < width)
		{
				// buffer[x + (y * (line_bytes / 4))] = color;
			if (powf(x - ((float)width / 2), 2)
            + powf(y - ((float)height / 2), 2) <= width * 2)
				buffer[x + (y * (line_bytes / 4))] = color;
			else
				buffer[x + (y * (line_bytes / 4))] = 0xFF000000;
			x++;
		}
		x = 0;
		y++;
	}
	return (img);
}


int	main(void)
{
	t_data	data;

	// INIT MLX
	data.mlx_info = init_mlx((t_res){{
			WIN_WIDTH, WIN_HEIGHT
			}});

	// IMAGE INFO
	const uint16_t image_width = 8;
	const uint16_t image_height = 8;
	
	image img1 = make_point(image_width
						, image_height
						, 0x00FF00FF
						, data.mlx_info);

	image img2 = make_point(image_width
						, image_height
						, 0x00FF0000
						, data.mlx_info);
	image img3 = make_point(image_width
						, image_height
						, 0x00000FF
						, data.mlx_info);

	image img4 = make_point(image_width
						, image_height
						, 0x00000FF00
						, data.mlx_info);

	data.assets.imgs[0] = img1;
	data.assets.imgs[1] = img2;
	data.assets.imgs[2] = img3;
	data.assets.imgs[3] = img4;
	// loop
	handling_events(&data);
	my_data(&data);
	mlx_loop(data.mlx_info.mlx);
}





	// uint32_t pixel = 0;

	// while (y < image_height)
	// {
		// while (x < image_width)
		// {
			// pixel = (y * line_bytes) + (x * 4);
			// buffer[pixel + 0] = (color) & 0xFF;
			// buffer[pixel + 1] = (color >> 8) & 0xFF;
			// buffer[pixel + 2] = (color >> 16) & 0xFF;
			// buffer[pixel + 3] = (color >> 24);
			// x++;
		// }
		// x = 0;
		// y++;
	// }
