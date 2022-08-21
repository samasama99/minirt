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
