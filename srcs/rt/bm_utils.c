/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:20:22 by zsarir            #+#    #+#             */
/*   Updated: 2022/09/02 16:30:45 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linear_algebra.h>
#include <main.h>
#include <math.h>

t_fpair	ij_of_map(t_res res, t_uv uv)
{
	const double	u = uv.u;
	const double	v = uv.v;

	return ((t_fpair){{u * res.width, v * res.height}});
}
