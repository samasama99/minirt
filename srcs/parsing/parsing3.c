/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:31:55 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/09 21:33:27 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_optional_string	parse_string(char *target)
{
	if (target == NULL)
		return ((t_optional_string){.is_null = true});
	return ((t_optional_string){
		.value = target,
		.size = ft_strlen(target),
		.is_null = false,
	});
}

t_optional_int	parse_type(char *target)
{
	const t_optional_string	string = parse_string(target);

	if (string.is_null)
		return ((t_optional_int){.error = true});
	if (is_equal_str(string.value, "#"))
		return ((t_optional_int){.value = e_comment});
	if (is_equal_str(string.value, "l"))
		return ((t_optional_int){.value = e_light});
	if (is_equal_str(string.value, "C"))
		return ((t_optional_int){.value = e_camera});
	if (is_equal_str(string.value, "A"))
		return ((t_optional_int){.value = e_ambient});
	if (is_equal_str(string.value, "sp"))
		return ((t_optional_int){.value = e_sphere});
	if (is_equal_str(string.value, "pl"))
		return ((t_optional_int){.value = e_plane});
	if (is_equal_str(string.value, "cy"))
		return ((t_optional_int){.value = e_cylinder});
	if (is_equal_str(string.value, "co"))
		return ((t_optional_int){.value = e_cone});
	return ((t_optional_int){.error = true});
}

void	correct_ambient(t_world w, t_material ambient)
{
	int	i;

	i = 0;
	while (i < w.amount_of_shapes)
	{
		w.shapes[i].super.material.ambient_color = ambient.ambient_color;
		w.shapes[i].super.material.ambient_ratio = ambient.ambient_ratio;
		++i;
	}
}
