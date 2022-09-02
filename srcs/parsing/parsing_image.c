/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:01:24 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 16:03:15 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_optional_image	parse_image_path(const char *path)
{
	const t_optional_image	error = {.error = true};
	char					*dot;

	if (path == NULL || *path == '\0')
		return (error);
	dot = strrchr(path, '.');
	if (dot == NULL || is_equal_str(dot, ".xpm") == false)
		return (error);
	return ((t_optional_image){.value = load_image(path)});
}
