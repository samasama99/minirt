/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:58:58 by zsarir            #+#    #+#             */
/*   Updated: 2022/09/02 16:28:24 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <pthread.h>

void	*wait_dots(void *nothing)
{
	static int	current = 0;

	(void)nothing;
	while (true)
	{
		if (current % 8 == 0)
			ft_putstr_fd (" \033[0;32m[MiniRT]\033[0m :: rendring .\r", 1);
		if (current % 8 == 1)
			ft_putstr_fd (" \033[0;32m[MiniRT]\033[0m :: rendring ..\r", 1);
		if (current % 8 == 2)
			ft_putstr_fd (" \033[0;32m[MiniRT]\033[0m :: rendring ...\r", 1);
		if (current % 8 == 3)
			ft_putstr_fd (" \033[0;32m[MiniRT]\033[0m :: rendring ....\r", 1);
		if (current % 8 == 4)
			ft_putstr_fd (" \033[0;32m[MiniRT]\033[0m :: rendring .....\r", 1);
		if (current % 8 == 5)
			ft_putstr_fd (" \033[0;32m[MiniRT]\033[0m :: rendring ......\r", 1);
		if (current % 8 == 6)
			ft_putstr_fd (" \033[0;32m[MiniRT]\033[0m :: rendring .......\r", 1);
		if (current % 8 == 7)
			ft_putstr_fd (" \033[0;32m[MiniRT]\033[0m :: rendring ........\r\n", 1);
		current = (current + 1) % 8;
		sleep(1);
	}
	return (NULL);
}

static t_thread_data	create_thread_data(int y,
										t_camera c,
										t_world w,
										t_image canvas)
{
	return ((t_thread_data){
		.line = y,
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
		r = ray_for_pixel(data->camera, x, data->line);
		c = color_at(data->world, r);
		put_pixel_to_image(data->canvas, pair(x, data->line), c);
		++x;
	}
	return (NULL);
}

#define THREAD_COUNT 8

void	render(const t_camera c, const t_world w, const t_image canvas)
{
	t_thread_data	data[8];
	pthread_t		id[8 + 1];
	int				y;
	int				i;

	y = 0;
	pthread_create(&id[THREAD_COUNT], NULL, wait_dots, NULL);
	while (y < c.vsize - 1)
	{
		data[y % THREAD_COUNT] = create_thread_data(y, c, w, canvas);
		pthread_create(&id[y % THREAD_COUNT], NULL,
			render_thread, &data[y % THREAD_COUNT]);
		++y;
		if ((y == (c.vsize - 1))
			|| (y % THREAD_COUNT == 0 && y >= THREAD_COUNT))
		{
			i = THREAD_COUNT;
			while (--i >= 0)
				pthread_join(id[i], NULL);
		}
	}
	pthread_cancel(id[THREAD_COUNT]);
	put_image(pair(0, 0), canvas);
	destroy_image(canvas.img);
}
