/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:15:25 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 16:16:02 by zsarir           ###   ########.fr       */
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
