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
# include "linear_algebra.h"
# include "get_next_line.h"

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

# define BUFFER 1
# define ESC 53

// # define MINUS_KEY 78
// # define PLUS_KEY 69

// # define W_KEY 13
// # define S_KEY 1
// # define D_KEY 2
// # define A_KEY 0

# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

#define EPSILON 0.00001
#define HEIGHT 600
#define WIDTH 600

#ifdef D
#define DEBUG(f_, ...) printf((f_), __VA_ARGS__)
#else
#define DEBUG(f_, ...) 
#endif


typedef void* mlx_ptr;
typedef void* win_ptr;
typedef void* image;

typedef int t_key;
typedef bool error;

/******* GENERAL  UTILS ********/

// char		*ft_strjoin_free(char *s1, char *s2);
void		panic(bool con, const char *msg, const char *func);
bool		is_equal_str(const char *s1, const char *s2);
float clamp(float n, float min, float max);
long time_now();

/******* 2D_ARRAY *******/

void		free_2d_array(char **array);
size_t		size_of_2d_array(char **array);
int			find_in_2d_array(char **array, char *str);

char		**init_2d_array(void);
char		**add_element_2d_array_last(char **array, char *elem);
char		**add_element_2d_array(char **array, char *elem, size_t index);

/******* GAME_DATA *******/

// typedef struct s_assets {
// 	image imgs[1024];
// }	t_assets;

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
t_rgb	rgb_sums(t_rgb a, t_rgb b, t_rgb c);
t_rgb	rgb_sub(t_rgb a, t_rgb b);
t_rgb	rgb_scalar(t_rgb a, double k);
bool rgb_is_equal(t_rgb v1, t_rgb v2);
t_rgb rgb_product(t_rgb c1, t_rgb c2);
t_rgb color(float r, float g, float b);
t_rgb black();

/******* MLX *******/

typedef struct s_mlx {
	mlx_ptr	mlx;
	win_ptr	win;
	t_res		resolution;
	t_res		center;
}	t_mlx;

// typedef struct s_data {
// 	t_mlx			mlx_info;
// 	t_assets		assets;
// }	t_data;

// typedef struct s_object {
// 	size_t		size;
// 	t_pos			points[1024];
// }	t_object;


typedef struct s_image {
  image img;
  t_res res;
  int *buffer;
} t_image;

// t_data *my_data(t_data *data);
t_mlx	init_mlx(t_res resolution, t_res center);
// void	handling_events(t_data *data);
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
int pixel_at(t_image img, t_pair p);
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
  double ambient_ratio;
  t_rgb ambient_color;
  double diffuse;
  double specular;
  double shininess;
}               t_material;

typedef enum e_shape_type {
  Error,
  SuperShape,
  Sphere,
  Plane,
} t_shape_type;

typedef struct s_super_shape
{
    t_shape_type type;
    int id;
    t_matrix4 t;
    t_material material;
} t_super_shape;

typedef struct s_sphere {
    t_shape_type type;
    int id;
    t_matrix4 t;
    t_material material;
    t_point center;
    double radius;
}               t_sphere;

typedef struct s_plane {
    t_shape_type type;
    int id;
    t_matrix4 t;
    t_material material;
    t_point position;
    t_norm normal;
}               t_plane;

typedef union u_shape {
  t_shape_type type;
  t_super_shape super;
  t_sphere sphere;
  t_plane plane;
}             t_shape;


typedef struct s_intersection {
  double t;
  t_shape shape;
} t_intersection;

typedef struct s_hit {
    t_intersection intersections[2];
    int count;
}               t_hit;

typedef struct s_comp {
    double t;
    t_shape shape;
    t_point point; 
    t_point over_point;
    t_vec eyev;
    t_vec normalv;
    bool inside;
}               t_comp;

t_ray ray(t_point origin, t_vec direction);
t_point ray_position(t_ray r, double t);
t_sphere make_sphere(t_point origin, double radius);
t_sphere sphere();
t_hit intersect_sphere(const t_sphere sphere, const t_ray r);
t_plane make_plane(t_point pos, t_norm norm);
t_plane	plane(void);
t_hit	intersect_plane(t_plane p, t_ray r);
t_vec	normal_at_plane(t_plane p);
t_intersection hit(t_hit h);
t_ray ray_transform(t_ray ray, t_matrix4 m);
bool is_hit(const t_sphere sp, const t_ray r);
t_vec normal_at(t_shape shape, t_point world_point);
t_vec reflect(t_vec in, t_vec norm);
t_light point_light(t_point position, t_rgb color);
t_rgb	lighting(t_material m, t_light l, double light_norm, double reflect_eye);
t_material material();
t_comp prepare_computations(t_intersection i, t_ray r);
t_transform view_transform(t_point from, t_point to, t_vec up);
t_intersection intersection(double t, t_shape shape);
t_shape sphere_shape(t_sphere s);
t_shape plane_shape(t_plane s);
t_plane plane();
t_hit intersect(t_shape shape, t_ray r);
t_vec normal_at_plane(t_plane p);
t_vec normal_at_sphere(t_sphere s, t_point local_point);
t_hit no_intersection();

// THE WORLD
typedef struct s_world {
  t_shape *shapes;
  t_light light;
  int amount_of_shapes;
}               t_world;

t_world set_amount_of_shapes(size_t amount);
t_world add_shape(const t_world w, const t_shape s);
// t_world add_light(const t_world w, const t_light l);
t_world default_world();
t_hit intersect_world(t_world w, t_ray r);
t_rgb shade_hit(t_world w, t_comp comps);
t_rgb color_at(t_world w, t_ray r);
bool is_shadowed(t_world w, t_point p);

typedef struct s_camera {
  double hsize;
  double vsize;
  double pixel_size;
  double half_width;
  double half_height;
  t_transform transform;
} t_camera;

t_camera camera(const double hsize, const double vsize, const t_rad fov);
t_ray ray_for_pixel(t_camera c, int px, int py);
void render(t_camera c, t_world w);
#endif
