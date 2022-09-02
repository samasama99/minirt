/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:30:03 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 16:30:18 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>

t_rgb	checkerboard(t_uv uv, t_rgb color1, t_rgb color2, t_pair ab)
{
	const double	u = floor(uv.u * ab.x);
	const double	v = floor(uv.v * ab.y);

	if ((int)(u + v) % 2)
		return (color1);
	return (color2);
}
