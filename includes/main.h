/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:49:06 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/04 17:08:25 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <libft.h>
# include <linear_algebra.h>
# include <mlx_utils.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/stat.h>

# define BUFFER 1
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

# define EPSILON 0.00001
# define HEIGHT 600
# define WIDTH 600

/******* GENERAL  UTILS ********/

void			panic(bool con, const char *msg, const char *func);
bool			is_equal_str(const char *s1, const char *s2);
float			clamp(float n, float min, float max);
long			time_now(void);
void			ft_perror(int exit_status);

/******* GAME_DATA *******/

/*rgb*/

typedef struct s_rgb
{
	float	red;
	float	green;
	float	blue;
}	t_rgb;

typedef union u_color {
	struct {
		unsigned char	blue;
		unsigned char	green;
		unsigned char	red;
		unsigned char	alpha;
	};
	int	color;
}	t_color;

void			print_rgb(char *vec_name, t_rgb a);
t_rgb			rgb_sum(t_rgb a, t_rgb b);
t_rgb			rgb_sums(t_rgb a, t_rgb b, t_rgb c);
t_rgb			rgb_sub(t_rgb a, t_rgb b);
t_rgb			rgb_scalar(t_rgb a, double k);
bool			rgb_is_equal(t_rgb v1, t_rgb v2);
t_rgb			rgb_product(t_rgb c1, t_rgb c2);
t_rgb			color(float r, float g, float b);
t_rgb			black(void);

// RAY TRACING
typedef struct s_ray {
	t_point	origin;
	t_vec	direction;
}	t_ray;

typedef struct s_light {
	t_point	position;
	t_rgb	intensity;
}	t_light;

typedef struct s_material {
	t_rgb	color;
	double	ambient_ratio;
	t_rgb	ambient_color;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef enum e_color_type {
	Normal,
	Texture,
	Checkerboard,
}	t_color_type;

typedef enum e_shape_type {
	Error,
	SuperShape,
	Sphere,
	Plane,
	Cylinder,
	Cone,
}	t_shape_type;

typedef struct s_super_shape
{
	t_shape_type	type;
	int				id;
	t_transform		transform;
	t_material		material;
	t_color_type	color_type;
	t_image			img;
	t_rgb			checkerboard_color1;
	t_rgb			checkerboard_color2;
}	t_super_shape;

typedef struct s_sphere {
	t_shape_type	type;
	int				id;
	t_matrix4		t;
	t_material		material;
	t_color_type	color_type;
	t_image			img;
	t_rgb			checkerboard_color1;
	t_rgb			checkerboard_color2;
	t_point			center;
	double			radius;
}	t_sphere;

typedef struct s_cylinder {
	t_shape_type	type;
	int				id;
	t_matrix4		t;
	t_material		material;
	t_color_type	color_type;
	t_image			img;
	t_rgb			checkerboard_color1;
	t_rgb			checkerboard_color2;
	t_point			center;
	t_norm			normal;
	double			radius;
	double			height;
}	t_cylinder;

typedef struct s_cone {
	t_shape_type	type;
	int				id;
	t_matrix4		t;
	t_material		material;
	t_color_type	color_type;
	t_image			img;
	t_rgb			checkerboard_color1;
	t_rgb			checkerboard_color2;
	t_point			center;
	t_norm			normal;
	double			height;
}	t_cone;

typedef struct s_plane {
	t_shape_type	type;
	int				id;
	t_transform		transform;
	t_material		material;
	t_color_type	color_type;
	t_image			img;
	t_rgb			checkerboard_color1;
	t_rgb			checkerboard_color2;
	t_point			position;
	t_norm			normal;
}	t_plane;

typedef union u_shape {
	t_shape_type	type;
	t_super_shape	super;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_cone			cone;
}	t_shape;

typedef struct s_intersection {
	double	t;
	t_shape	shape;
}	t_intersection;

typedef struct s_hit {
	t_intersection	intersections[2];
	int				count;
}	t_hit;

typedef struct s_comp {
	double	t;
	t_shape	shape;
	t_point	point;
	t_point	over_point;
	t_vec	eyev;
	t_vec	normalv;
	bool	inside;
	t_ray 	r;
}	t_comp;

t_ray			ray(t_point origin, t_vec direction);
t_point			ray_position(t_ray r, double t);
t_sphere		make_sphere(t_point origin, double radius, t_rgb color);
t_sphere		sphere(void);
t_hit			intersect_sphere(const t_sphere sphere, const t_ray r);
t_plane			make_plane(t_point pos, t_norm norm);
t_plane			plane(void);
t_hit			intersect_plane(t_plane p, t_ray r);
t_vec			normal_at_plane(t_plane p);
t_intersection	hit(t_hit h);
t_ray			ray_transform(t_ray ray, t_matrix4 m);
bool			is_hit(const t_sphere sp, const t_ray r);
t_vec	normal_at(t_shape shape, t_point world_point);
t_vec			reflect(t_vec in, t_vec norm);
t_light			point_light(t_point position, t_rgb color);
t_rgb			lighting(t_material m, t_light l, double light_norm,
					double reflect_eye);
t_rgb			ambient(t_material m, t_light l);
t_material		material(void);
t_comp			prepare_computations(t_intersection i, t_ray r);
t_transform		view_transform(t_point from, t_point to, t_vec up);
t_intersection	intersection(double t, t_shape shape);
t_shape			sphere_shape(t_sphere s);
t_shape			plane_shape(t_plane s);
t_plane			plane(void);
t_hit			intersect(t_shape shape, t_ray r);
t_vec			normal_at_plane(t_plane p);
t_vec			normal_at_sphere(t_sphere s, t_point local_point);
t_hit			no_intersection(void);
double			discriminant(double a, double b, double c);

// THE WORLD
typedef struct s_world {
	volatile t_shape	*shapes;
	volatile t_light	*lights;
	volatile int		amount_of_shapes;
	volatile int		amount_of_lights;
}	t_world;

t_world			add_shape(const t_world w, const t_shape s);
t_world			add_light(const t_world w, const t_light l);
t_world			default_world(void);
t_hit			intersect_world(t_world w, t_ray r);
t_rgb			shade_hit(t_world w, t_comp comps, t_light l, bool amb);
t_rgb			color_at(t_world w, t_ray r);
bool			is_shadowed(t_world w, t_point p, t_light l);
t_rgb			diffuse(t_material m, t_light l, double light_dot_normal);
int				get_color_at(t_image img, int x, int y);
t_rgb			shade_hit_normal(t_world w, t_comp comps, t_light l);
t_rgb			shade_hit_texture(
					t_world w,
					t_comp comps,
					t_light l,
					t_intersection inter);
t_vec			reflect(t_vec in, t_vec norm);

typedef struct s_camera {
	double		hsize;
	double		vsize;
	double		pixel_size;
	double		half_width;
	double		half_height;
	t_transform	transform;
}	t_camera;

t_camera		camera(const double hsize, const double vsize, const t_rad fov);
t_ray			ray_for_pixel(t_camera c, int px, int py);

// RENDER

typedef struct s_thread_data {
	int			line;
	t_camera	camera;
	t_world		world;
	t_image		canvas;
}	t_thread_data;

void			render(const t_camera c, const t_world w, const t_image canvas);

// cylinder
t_cylinder		make_cylinder(t_point point, t_norm norm,
					t_fpair info, t_rgb color);
t_cylinder		cylinder(void);
t_hit			intersect_cylinder(const t_cylinder cy, const t_ray r);
t_vec			normal_at_cylinder(t_point local_point);
//cone
t_hit			intersect_cone(const t_cone co, const t_ray r);
t_vec   normal_at_cone(t_point p);
t_cone			make_cone(t_point point, t_norm norm,
					double height, t_rgb color);

t_cone			cone(void);
// uv
typedef struct s_uv
{
	double	u;
	double	v;
}	t_uv;

t_rgb			checkerboard(t_uv uv, t_rgb color1, t_rgb color2, t_pair ab);

t_rad			teta_sphere(t_sphere sp, t_point p);
t_rad			phi_sphere(t_sphere sp, t_point p);
t_uv			uv_of_sphere(t_sphere sp, t_point p);
t_uv			uv_of_plane(t_plane pl, t_point p);
t_uv			uv_of_cylinder(t_cylinder cy, t_point p);
t_fpair			ij_of_map(t_res res, t_uv uv);
t_rgb			shade_hit_bm_sphere(t_comp comps, t_light l, t_sphere s,
					t_world w);
t_rgb			shade_hit_bm_cylinder(t_comp comps, t_light l, t_cylinder s,
					t_world w);
t_rgb			shade_hit_bm_plane(t_comp comps, t_light l, t_plane s,
					t_world w);
int				get_color_at(t_image img, int x, int y);
double			linear_interpolation(double i, double j, t_image img);
t_rgb			shade_hit_cb(t_world w,
					t_comp comps,
					t_light l,
					t_intersection inter);
#endif
