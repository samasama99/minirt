/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:59:45 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/01 18:59:46 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

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
