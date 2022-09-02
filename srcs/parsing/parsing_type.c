/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:31:55 by zsarir            #+#    #+#             */
/*   Updated: 2022/09/01 18:59:39 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_optional_int	parse_type(char *target)
{
	const t_optional_string	string = parse_string(target);

	if (string.is_null)
		return ((t_optional_int){.error = true});
	if (is_equal_str(string.value, "#") || string.value[0] == '#')
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
