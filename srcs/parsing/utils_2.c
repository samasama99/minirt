/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:59:13 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 16:04:23 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <parsing.h>

void	ft_exit(t_optional_string err, int err_status)
{
	if (err.is_null == false)
		write(1, err.value, err.size);
	exit(err_status);
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

t_optional_array	split_string(const char *line, const char delimiter)
{
	char	**array;

	if (line == NULL)
		return ((t_optional_array){.error = true});
	array = ft_split(line, delimiter);
	if (array == NULL)
		return ((t_optional_array){.error = true});
	return ((t_optional_array){
		.value = array,
		.size = array_len(array),
		.error = false,
	});
}

t_optional_array	split_space(const char *line)
{
	char	**array;

	if (line == NULL)
		return ((t_optional_array){.error = true});
	array = ft_split_space(line);
	if (array == NULL)
		return ((t_optional_array){.error = true});
	return ((t_optional_array){
		.value = array,
		.size = array_len(array),
		.error = false,
	});
}
