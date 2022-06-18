#include "main.h"

t_rgb	rgb_sum(t_rgb a, t_rgb b)
{
	return (t_rgb) {
		.red = a.red + b.red,
		.green = a.green + b.green,
		.blue = a.blue + b.blue,
	};
}

t_rgb	rgb_sub(t_rgb a, t_rgb b)
{
	return (t_rgb) {
		.red = a.red - b.red,
		.green = a.green - b.green,
		.blue = a.blue - b.blue,
	};
}

t_rgb	rgb_scalar(t_rgb a, double k)
{
	return (t_rgb){
		.red = a.red * k,
		.green = a.green * k,
		.blue = a.blue * k,
	};
}

t_rgb rgb_hadamard_product(t_rgb c1, t_rgb c2)
{
  return (t_rgb) {
		.blue = c1.blue * c2.blue,
		.green = c1.green * c2.green,
		.red = c1.red * c2.red,
  };
}

bool rgb_is_equal(t_rgb v1, t_rgb v2)
{
  if (is_equal_double(v1.blue, v2.blue == false))
    return false;
  if (is_equal_double(v1.green, v2.green) == false) 
    return false;
  if (is_equal_double(v1.red, v2.red) == false) 
    return false;
  return true;
}

t_rgb color(float r, float g, float b)
{
  return ((t_rgb){
    .red = r,
    .green = g,
    .blue = b,
  });
}

t_rgb black()
{
  return ((t_rgb){
    0, 0, 0
  });
}
