/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:52:58 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/18 21:32:13 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

win_ptr	init_win(mlx_ptr mlx, t_res resolution)
{
	win_ptr	win;

	if (mlx == NULL)
	{
		perror ("Error ");	
		exit (1);
	}
	win = mlx_new_window(mlx
						, resolution.width
						, resolution.height
						, "mlx");
	if (win == NULL)
	{
		{
			perror ("Error ");	
			exit (1);
		}
	}
	return (win);
}

t_mlx	init_mlx(t_res resolution)
{
	t_mlx		mlx_info;
	mlx_ptr	mlx;
	win_ptr	win;

	mlx = mlx_init();
	win = init_win(mlx, resolution);
	mlx_info = (t_mlx) {
		mlx,
		win,
		resolution,
	};
	return (mlx_info);
}
