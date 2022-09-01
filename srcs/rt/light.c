/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:38:32 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/21 15:50:17 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_light	point_light(t_point position, t_rgb intensity)
{
	return ((t_light){
		.position = position,
		.intensity = intensity,
	});
}

t_rgb	ambient(t_material m, t_light l)
{
	const t_rgb	effective_color = rgb_product(m.ambient_color, l.intensity);

	return (rgb_scalar(effective_color, m.ambient_ratio));
}

t_rgb	diffuse(t_material m, t_light l, double light_dot_normal)
{
	const t_rgb	effective_color = rgb_product(m.color, l.intensity);

	return (rgb_scalar(effective_color, m.diffuse * light_dot_normal));
}

t_rgb	specular(t_material m, t_light l, double reflect_dot_eye)
{
	double	factor;

	if (reflect_dot_eye <= 0)
		return (black());
	factor = pow(reflect_dot_eye, m.shininess);
	return (rgb_scalar(l.intensity, m.specular * factor));
}

t_rgb	lighting(t_material m, t_light l, double light_norm, double reflect_eye)
{
	return (rgb_sums(
			ambient(m, l),
			diffuse(m, l, light_norm),
			specular(m, l, reflect_eye)));
}
