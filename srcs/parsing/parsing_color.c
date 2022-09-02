/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:59:30 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 15:59:31 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_optional_rgb	parse_rgb(const char *target)
{
	char				**splited;
	t_optional_double	*colors;

	if (target == NULL)
		return ((t_optional_rgb){.error = true});
	if (count_char(target, ',') != 2)
		return ((t_optional_rgb){.error = true});
	splited = ft_split(target, ',');
	if (array_len(splited) != 3)
		return ((t_optional_rgb){.error = true});
	colors = (t_optional_double[3]){
		parse_color_ratio(splited[0]),
		parse_color_ratio(splited[1]),
		parse_color_ratio(splited[2])};
	if (colors[0].error || colors[1].error || colors[2].error)
		return ((t_optional_rgb){.error = true});
	return ((t_optional_rgb){
		.value = color(colors[0].value, colors[1].value, colors[2].value),
		.error = false,
	});
}
