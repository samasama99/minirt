/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:32:37 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/21 15:33:30 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	end_minirt_destroy(void)
{
	destroy_window();
	ft_free();
	exit(0);
}

int	end_minirt(int key)
{
	if (key == ESC)
	{
		destroy_window();
		ft_free();
		exit(0);
	}
	return (0);
}
