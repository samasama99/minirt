/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:00:58 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 15:01:26 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_rgb	rgb_product(t_rgb c1, t_rgb c2)
{
	return ((t_rgb){
		.blue = c1.blue * c2.blue,
		.green = c1.green * c2.green,
		.red = c1.red * c2.red,
	});
}

bool	rgb_is_equal(t_rgb v1, t_rgb v2)
{
	return (
		is_equal_double(v1.blue, v2.blue)
		&& is_equal_double(v1.green, v2.green)
		&& is_equal_double(v1.red, v2.red)
	);
}

t_rgb	color(float r, float g, float b)
{
	return ((t_rgb){
		.red = r,
		.green = g,
		.blue = b,
	});
}

t_rgb	black(void)
{
	return ((t_rgb){0, 0, 0});
}
