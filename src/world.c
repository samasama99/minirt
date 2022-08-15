/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:07:31 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/15 13:04:34 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_world	add_shape(const t_world w, const t_shape s)
{
	t_world	new_w;
	int		i;

	new_w = w;
	new_w.shapes = ft_malloc(sizeof(t_shape) * (w.amount_of_shapes + 1));
	new_w.amount_of_shapes = w.amount_of_shapes + 1;
	i = 0;
	while (i < w.amount_of_shapes)
	{
		new_w.shapes[i] = w.shapes[i];
		++i;
	}
	new_w.shapes[w.amount_of_shapes] = s;
	return (new_w);
}

t_world	add_light(const t_world w, const t_light l)
{
	volatile t_world	new_w;
	int					i;

	new_w.lights = ft_malloc(sizeof(t_light) * (w.amount_of_lights + 1));
	i = 0;
	while (i < w.amount_of_lights)
	{
		new_w.lights[i] = w.lights[i];
		++i;
	}
	new_w.lights[w.amount_of_lights] = l;
	new_w.amount_of_shapes = w.amount_of_shapes;
	new_w.amount_of_lights = w.amount_of_lights + 1;
	new_w.shapes = w.shapes;
	return (new_w);
}

t_hit	intersect_world(t_world w, t_ray r)
{
	t_intersection	min;
	t_intersection	tmp;
	int				i;

	i = 1;
	min = hit(intersect(w.shapes[0], r));
	while (i < w.amount_of_shapes)
	{
		tmp = hit(intersect(w.shapes[i], r));
		if ((tmp.t > 0 && tmp.t < min.t) || min.t < 0)
			min = tmp;
		++i;
	}
	if (min.t < 0)
		return (no_intersection());
	return ((t_hit){{min}, 1});
}
