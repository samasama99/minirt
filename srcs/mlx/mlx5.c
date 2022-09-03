/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:45:18 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/03 12:37:44 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"

t_image	load_image(const char *path)
{
	const t_mlx_ptr		mlx = get_mlx_info(NULL).mlx;
	t_pair				img_res;
	const t_image_ptr	img = mlx_xpm_file_to_image(mlx,
			(char *)path, &img_res.width, &img_res.height);
	t_image_info		info;
	int					*buffer;

	if (img == NULL)
	{
		return ((t_image){.buffer = NULL, .img = 0, .res = pair(0, 0)});
		exit(1);
	}
	buffer = (int *)mlx_get_data_addr(img, &info.pixel_bits,
			&info.line_bytes, &info.endian);
	return ((t_image){.img = img, .buffer = buffer, .res = img_res});
}
