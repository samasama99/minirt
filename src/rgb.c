#include "main.h"

void	print_rgb(char *vec_name, t_rgb a)
{
	printf("color %s\n|red x = %f %f|\n|green y = %f %f|\n|blue = %f %f|\n",
				vec_name,
		a.red, a.red * 255,
		a.green, a.green * 255,
		a.blue, a.blue * 255
		);
}

t_rgb	rgb_sum(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		.red = a.red + b.red,
		.green = a.green + b.green,
		.blue = a.blue + b.blue,
	});
}

t_rgb	rgb_sums(t_rgb a, t_rgb b, t_rgb c)
{
	return ((t_rgb){
		.red = a.red + b.red + c.red,
		.green = a.green + b.green + c.green,
		.blue = a.blue + b.blue + c.blue,
	});
}

t_rgb	rgb_sub(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		.red = a.red - b.red,
		.green = a.green - b.green,
		.blue = a.blue - b.blue,
	});
}

t_rgb	rgb_scalar(t_rgb a, double k)
{
	return ((t_rgb){
		.red = a.red * k,
		.green = a.green * k,
		.blue = a.blue * k,
	});
}

t_rgb	rgb_product(t_rgb c1, t_rgb c2)
{
	return ((t_rgb){
		.blue = c1.blue * c2.blue,
		.green = c1.green * c2.green,
		.red = c1.red * c2.red,
	});
}

bool	rgb_is_equal(t_rgb v1, t_rgb v2)
{
	return (
		is_equal_double(v1.blue, v2.blue)
		&& is_equal_double(v1.green, v2.green)
		&& is_equal_double(v1.red, v2.red)
	);
}

t_rgb	color(float r, float g, float b)
{
	return ((t_rgb){
		.red = r,
		.green = g,
		.blue = b,
	});
}

t_rgb	black(void)
{
	return ((t_rgb){0, 0, 0});
}
