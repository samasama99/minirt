/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:49:06 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/21 09:02:33 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "../libft/libft.h"
# include "vector.h"

// # include <mlx.h>
# include </usr/local/include/mlx.h>
# include <math.h>

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/stat.h>

# define ESC 53
# define UP_KEY 13
# define DOWN_KEY 1
# define RIGHT_KEY 2
# define LEFT_KEY 0

#define DEBUG(f_, ...) printf((f_), __VA_ARGS__)

typedef void* mlx_ptr;
typedef void* win_ptr;
typedef void* image;

typedef int t_key;
typedef bool error;

/******* GENERAL  UTILS ********/

char		*ft_strjoin_free(char *s1, char *s2);
void		panic(bool con, char *msg, const char *func);
bool		is_equal_str(const char *s1, const char *s2);

/******* 2D_ARRAY *******/

void		free_2d_array(char **array);
size_t		size_of_2d_array(char **array);
int			find_in_2d_array(char **array, char *str);

char		**init_2d_array(void);
char		**add_element_2d_array_last(char **array, char *elem);
char		**add_element_2d_array(char **array, char *elem, size_t index);

/******* GAME_DATA *******/

typedef struct s_assets {
	image imgs[1024];
}	t_assets;

/******* MLX *******/

typedef union u_pair_int
{
	struct { int16_t width; int16_t height; };
	struct { int16_t x; int16_t y; };
	struct { int16_t i; int16_t j; };
}	t_pair;

typedef t_pair t_res;
// typedef t_pair t_pos;

typedef struct s_mlx {
	mlx_ptr	mlx;
	win_ptr	win;
	t_res		resolution;
}	t_mlx;

typedef struct s_data {
	t_mlx			mlx_info;
	t_assets		assets;

}	t_data;

t_data *my_data(t_data *data);
t_mlx	init_mlx(t_res resolution);
void	handling_events(t_data *data);

#endif
