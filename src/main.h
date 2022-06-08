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
// # include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/stat.h>

# define ESC 53

# define MINUS_KEY 78
# define PLUS_KEY 69

# define W_KEY 13
# define S_KEY 1
# define D_KEY 2
# define A_KEY 0

# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

#define DEBUG(f_, ...) printf((f_), __VA_ARGS__)

typedef void* mlx_ptr;
typedef void* win_ptr;
typedef void* image;

typedef int t_key;
typedef bool error;

/******* GENERAL  UTILS ********/

char		*ft_strjoin_free(char *s1, char *s2);
void	panic(bool con, const char *msg, const char *func, const char *file, const int line);
// void		panic(bool con, const char *msg, const char *func);
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

/*rgb*/

typedef struct s_rgb {
		float	red;
		float	green;
		float	blue;
}	t_rgb;

typedef union u_color {
  struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char alpha;
  };
  int color;
} t_color;

t_rgb	rgb_sum(t_rgb a, t_rgb b);
t_rgb	rgb_sub(t_rgb a, t_rgb b);
t_rgb	rgb_scalar(t_rgb a, double k);
bool rgb_is_equal(t_rgb v1, t_rgb v2);
t_rgb rgb_hadamard_product(t_rgb c1, t_rgb c2);
t_rgb color(float r, float g, float b);
t_rgb black();

/******* MLX *******/

// typedef t_pair t_pos;

typedef struct s_mlx {
	mlx_ptr	mlx;
	win_ptr	win;
	t_res		resolution;
	t_res		center;
}	t_mlx;

typedef struct s_data {
	t_mlx			mlx_info;
	t_assets		assets;
}	t_data;

// typedef struct s_object {
// 	size_t		size;
// 	t_pos			points[1024];
// }	t_object;


typedef struct s_image {
  image img;
  t_res res;
  int *buffer;
} t_image;

t_data *my_data(t_data *data);
t_mlx	init_mlx(t_res resolution, t_res center);
void	handling_events(t_data *data);
int make_color(t_rgb c, float alpha);
void put_pixel(t_pair pos, t_rgb rgb);
void put_image(t_pair pos, t_image img);
t_image create_image(t_res res);
void put_pixel_to_image(t_image img, t_pair pos, t_rgb color);
void fill_image(t_image img, t_pair start, t_pair finish, t_rgb color);
void full_fill_image(t_image img, t_rgb color);
void fill_image_con(t_image img, t_rgb color, bool (*functor)(t_point p));
void loop_hook(int (*funct_ptr)(), void *param);
void clear_window();
void start_mlx();

// RAY TRACING
typedef struct s_ray {
    t_point origin;
    t_vec direction;
}               t_ray;

typedef struct s_light {
    t_point position;
    t_rgb intensity;
}               t_light;

typedef struct s_material {
  t_rgb color;
  double ambient;
  double diffuse;
  double specular;
  double shininess;
}               t_material;

typedef struct s_sphere {
    int id;
    t_point center;
    double radius;
    t_matrix4 t;
    t_material material;
}               t_sphere;
// 1. The t value of the intersection
// 2. The object that was intersected
typedef struct s_intersection {
  double t;
  t_sphere sphere;
} t_intersection;

typedef struct s_hit {
    t_intersection intersection[1024];
    int count;
}               t_hit;

typedef union u_object {
  t_sphere sphere;
}             t_object;


typedef struct s_comp {
    double t;
    t_object object;
    t_point point; 
    t_vec eyev;
    t_vec normalv;
    bool inside;
}               t_comp;


t_ray ray(t_point origin, t_vec direction);
t_point ray_position(t_ray r, double t);
t_sphere make_sphere(t_point origin, double radius);
t_sphere sphere();
t_hit intersect_sphere(const t_sphere sphere, const t_ray r);
t_intersection hit(t_hit h);
t_ray ray_transform(t_ray ray, t_matrix4 m);
bool is_hit(const t_sphere sp, const t_ray r);
t_vec normal_at(t_sphere s, t_point p);
t_vec reflect(t_vec in, t_vec norm);
t_light point_light(t_point position, t_rgb color);
t_rgb lighting(t_material m, t_light l, t_point point, t_vec eyev, t_vec normalv);
t_material material();
t_comp prepare_computations(t_intersection i, t_ray r);
t_transform view_transform(t_point from, t_point to, t_vec up);

// THE WORLD
typedef struct s_world {
  t_sphere spheres[1024];
  t_light lights[1024];
  int amount_of_spheres;
  int amount_of_lights;
}               t_world;

t_world world();
t_world add_sphere(const t_world w, const t_sphere s);
t_world default_world();
t_hit intersect_world(t_world w, t_ray r);
t_rgb shade_hit(t_world w, t_comp comps);
t_rgb color_at(t_world w, t_ray r);
#endif
