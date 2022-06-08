#include "main.h"

t_rgb	rgb_sum(t_rgb a, t_rgb b);
t_rgb	rgb_scalar(t_rgb a, double k);

// void print_rgb(t_rgb color) {
//   printf ("red == %u")
// }

t_rgb	rgb_sum(t_rgb a, t_rgb b)
{
	t_rgb	x;

	x = (t_rgb) {
		.blue = a.blue + b.blue,
		.green = a.green + b.green,
		.red = a.red + b.red,
	};
	return (x);
}

t_rgb	rgb_sub(t_rgb a, t_rgb b)
{
	t_rgb	x;

	x = (t_rgb) {
		.blue = a.blue - b.blue,
		.green = a.green - b.green,
		.red = a.red - b.red,
	};
	return (x);
}

t_rgb	rgb_scalar(t_rgb a, double k)
{
	t_rgb	x;

	x = (t_rgb){
		.blue = a.blue * k,
		.green = a.green * k,
		.red = a.red * k,
	};
	return (x);
}

t_rgb rgb_hadamard_product(t_rgb c1, t_rgb c2)
{
  t_rgb hp;
  
  hp = (t_rgb) {
		.blue = c1.blue * c2.blue,
		.green = c1.green * c2.green,
		.red = c1.red * c2.red,
  };
  return hp;
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

// int main () {
//   t_rgb color1 = {{255, 0, 255, 0}};
//   unsigned int color2 = 0x00FF00FF;
//   printf ("%u\n", color1.uvalue); 
//   printf ("%d\n", color1.svalue); 
//   printf ("%u\n", color1.blue); 
//   printf ("%u\n", color1.green); 
//   printf ("%u\n", color1.red); 
//   // printf ("%u\n", color2); 
// }
