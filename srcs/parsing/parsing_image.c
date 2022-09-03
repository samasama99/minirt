/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:01:24 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/03 12:38:34 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"
#include <parsing.h>

t_optional_image	parse_image_path(const char *path)
{
	const t_optional_image	error = {.error = true};
	char					*dot;
	t_image					img;

	if (path == NULL || *path == '\0')
		return (error);
	dot = strrchr(path, '.');
	if (dot == NULL || is_equal_str(dot, ".xpm") == false)
		return (error);
	img = load_image(path);
	if (img.buffer == NULL || img.img == NULL)
		return (error);
	return ((t_optional_image){.value = img});
}
