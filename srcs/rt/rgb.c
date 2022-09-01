/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:39:57 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/28 15:01:31 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_rgb(char *vec_name, t_rgb a)
{
	printf("color %s\n|red x = %f %f|\n|green y = %f %f|\n|blue = %f %f|\n",
		vec_name,
		a.red, a.red * 255.999,
		a.green, a.green * 255.999,
		a.blue, a.blue * 255.999
		);
}

t_rgb	rgb_sum(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		.red = a.red + b.red,
		.green = a.green + b.green,
		.blue = a.blue + b.blue,
	});
}

t_rgb	rgb_sums(t_rgb a, t_rgb b, t_rgb c)
{
	return ((t_rgb){
		.red = a.red + b.red + c.red,
		.green = a.green + b.green + c.green,
		.blue = a.blue + b.blue + c.blue,
	});
}

t_rgb	rgb_sub(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		.red = a.red - b.red,
		.green = a.green - b.green,
		.blue = a.blue - b.blue,
	});
}

t_rgb	rgb_scalar(t_rgb a, double k)
{
	return ((t_rgb){
		.red = a.red * k,
		.green = a.green * k,
		.blue = a.blue * k,
	});
}
