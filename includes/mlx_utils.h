/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:51:59 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/03 14:17:41 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H
# include <linear_algebra.h>

typedef struct s_rgb	t_rgb;
typedef void			*t_mlx_ptr;
typedef void			*t_win_ptr;
typedef void			*t_image_ptr;

typedef int				t_key;
typedef bool			t_error;

typedef struct s_image_info {
	int			pixel_bits;
	int			endian;
	int			line_bytes;
}		t_image_info;

typedef enum e_event {
	keydown = 2,
	keyup = 3,
	mousedown = 4,
	mouseup = 5,
	mousemove = 6,
	destroy = 17
}	t_event;

typedef struct s_mlx {
	t_mlx_ptr	mlx;
	t_win_ptr	win;
	t_res		resolution;
}	t_mlx;

typedef struct s_image {
	t_image_ptr	*img;
	t_res		res;
	int			*buffer;
}	t_image;

t_mlx			init(t_res resolution, char *title);
void			put_black_bar(t_res res, t_pair pos);
void			put_string(int x, int y, char *string);
int				make_color(t_rgb c, float alpha);
void			put_pixel(t_pair pos, t_rgb rgb);
t_mlx			get_mlx_info(t_mlx *mlx);
void			put_image(t_pair pos, t_image img);
t_image			create_image(t_res res);
void			put_pixel_to_image(t_image img, t_pair pos, t_rgb color);
void			update(int (*funct_ptr)(), void *param);
void			clear_window(void);
int				pixel_at(t_image img, t_pair p);
void			listen_to(t_event type, int (*func)(), void *param);
void			start(void);
void			destroy_window(void);
void			destroy_image(t_image_ptr img);
int				end_minirt_destroy(void);
int				end_minirt(int key);
t_image			load_image(const char *path);
#endif
