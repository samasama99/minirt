/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:05:53 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/23 19:44:33 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char  *read_file(int fd);

#endif
