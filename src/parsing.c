/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:41:23 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/22 20:41:24 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stddef.h>

// void	parse(t_data *data, int fd, t_res res)
// {
// 	t_optional_string	line;
// 	t_optional_array	array;
// 	t_optional_int		type;

// 	line.is_null = false;
// 	while (line.is_null == false)
// 	{
// 		line = get_line(fd);
//     if (line.is_null)
//       break;
//     puts(line.value);
// 		if (is_equal_str(line.value, "\n"))
// 			continue ;
// 		array = split_string_space(line.value);
// 		type = parse_type(array.value[0]);
// 		if (line.is_null || array.error || type.error)
// 			ft_exit(parse_string("parsing error"), 1);
// 		if (type.value == e_camera)
// 			data->c = unwarp_camera(array, res);
// 		if (type.value == e_light)
// 			data->w = add_light(data->w, unwrap_light(array));
// 		if (type.value == e_ambient)
// 			data->ambient = unwrap_ambient(array);
// 		if (type.value == e_sphere || type.value == e_plane
// 			|| type.value == e_cylinder || type.value == e_cone)
// 			data->w = add_shape(data->w, unwrap_shape(array, type.value));
// 	}
// }

void	parse(t_data *data, int fd, t_res res)
{
	t_optional_array  lines;
	t_optional_array	array;
	t_optional_int		type;
  size_t            i;

  i = 0;
  lines = split_string(read_file(fd), '\n'); 
  // printf("%zu %d\n", lines.size, lines.error);
  if (lines.error || lines.size == 0)
  {
    ft_putendl_fd("minirt :: invalid file\n", 2);
    exit(1);
  }
	while (i < lines.size)
	{
    puts(lines.value[i]);
		array = split_string_space(lines.value[i++]);
		type = parse_type(array.value[0]);
    if (type.error == false && type.value == e_comment)
        continue;
		if (array.error || type.error)
			ft_exit(parse_string("parsing error"), 1);
		if (type.value == e_camera)
			data->c = unwarp_camera(array, res);
		if (type.value == e_light)
			data->w = add_light(data->w, unwrap_light(array));
		if (type.value == e_ambient)
			data->ambient = unwrap_ambient(array);
		if (type.value == e_sphere || type.value == e_plane
			|| type.value == e_cylinder || type.value == e_cone)
			data->w = add_shape(data->w, unwrap_shape(array, type.value));
	}
}

