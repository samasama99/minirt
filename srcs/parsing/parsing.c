/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:41:23 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/23 21:22:44 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

void	parse(t_data *data, int fd, t_res res, t_optional_array lines)
{
	t_optional_array	arr;
	t_optional_int		type;
	size_t				i;

	i = 0;
	if (lines.error || lines.size == 0)
		(close(fd), ft_exit(parse_string("minirt :: invalid file\n"), 2));
	printf(" \033[0;32m[MiniRT] :: parsing :\033[0m\n");
	while (i < lines.size)
	{
		arr = split_space(lines.value[i++]);
		type = parse_type(arr.value[0]);
		if (arr.error || type.error == true)
			(close(fd), ft_exit(parse_string("parsing error"), 1));
		if (type.value == e_camera)
			data->c = unwarp_camera(arr, res);
		if (type.value == e_light)
			data->w = add_light(data->w, unwrap_light(arr));
		if (type.value == e_ambient)
			data->ambient = unwrap_ambient(arr);
		if (type.value == e_sphere || type.value == e_plane
			|| type.value == e_cylinder || type.value == e_cone)
			data->w = add_shape(data->w, unwrap_shape(arr, type.value));
	}
}
