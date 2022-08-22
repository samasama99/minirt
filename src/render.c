/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:58:58 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/21 15:39:04 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <pthread.h>

static t_thread_data	create_thread_data(int y,
										t_camera c,
										t_world w,
										t_image canvas)
{
	return ((t_thread_data){
		.y = y,
		.camera = c,
		.world = w,
		.canvas = canvas});
}

static void	*render_thread(void *d)
{
	const t_thread_data	*data = d;
	size_t				x;
	t_ray				r;
	t_rgb				c;

	x = 0;
	while (x < data->camera.hsize - 1)
	{
		r = ray_for_pixel(data->camera, x, data->y);
		c = color_at(data->world, r);
		put_pixel_to_image(data->canvas, pair(x, data->y), c);
		++x;
	}
	return (NULL);
}

void	render(t_camera c, t_world w)
{
	const t_image	canvas = create_image(pair(c.hsize, c.vsize));
	const long		start = time_now();
	t_thread_data	*data;
	pthread_t		*id;
	size_t			y;

	id = malloc(sizeof(t_thread_data) * (int)c.vsize - 1);
	data = malloc(sizeof(t_thread_data) * (int)c.vsize - 1);
	y = 0;
	while (y < c.vsize - 1)
	{
		data[y] = create_thread_data(y, c, w, canvas);
		pthread_create(&id[y], NULL, render_thread, &data[y]);
		++y;
	}
	y = 0;
	while (y < c.vsize - 1)
		pthread_join(id[y++], NULL);
	put_image(pair(0, 0), canvas);
	put_string(10, 10, ft_strjoin("it took (ms) ",
			ft_itoa((int)time_now() - start)));
	destroy_image(canvas.img);
}
