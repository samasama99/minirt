#include "parsing.h"
#include <assert.h>

t_optional_int parse_digit(const char *d)
{
  if (d == NULL || d[0] == '\0')
    return (t_optional_int){.error = true};
  if (ft_strlen(d) != 1)
    return (t_optional_int){.error = true};
  if (ft_isdigit(d[0]) != 1)
    return (t_optional_int){.error = true};
  return (t_optional_int) {
  .value = ft_atoi(d),
  .error = false,
  };
}

t_optional_array split_string(const char *line, const char delimiter)
{
  char **array;

  if (line == NULL)
	return (t_optional_array){.error = true};
  array = ft_split(line, delimiter);
  if (array == NULL)
	return (t_optional_array){.error = true};
  return (t_optional_array){
	.value = array,
	.size = array_len(array),
	.error = false,
  };
}

t_optional_double parse_ratio(const char *target)
{
  const t_optional_array array = split_string(target, '.');
  const t_optional_double error = {.error = true};
  t_optional_int  whole;
  t_optional_int  fractional;

  if (array.error || array_len(array.value) > 2)
    return error;
  whole = parse_digit(array.value[0]);
  if (whole.error)
    return error;
  if (array.size == 1)
    return (t_optional_double) {
    .value = whole.value,
    .error = false,
    };
  fractional = parse_digit(array.value[1]);
  if (fractional.error)
    return error;
  if (fractional.value / 10. + whole.value > 1.0
	  || fractional.value / 10. + whole.value < 0.0)
    return error;
  return (t_optional_double) {
	.value = whole.value + fractional.value / 10.,
	.error = false,
  };
}

t_optional_double parse_color_ratio(const char *target)
{
  int num;

  if (target == NULL)
    return (t_optional_double){.error = true};
  if (ft_isnumber(target) == false)
    return (t_optional_double){.error = true};
  num = ft_atoi(target);
  if (num < 0 || num > 255)
	return (t_optional_double){.error = true};
  return (t_optional_double) {
	  .value = num / 255.0,
	  .error = false,
  };
}

t_optional_int parse_int(const char *target)
{
  int sign;

  sign = 1;
  if (target == NULL)
    return (t_optional_int) {.error = true};
  if (ft_isnumber(target + (target[0] == '-')) == false)
    return (t_optional_int) {.error = true};
  if (target[0] == '-')
    sign = -1;
  return (t_optional_int) {
    .value = ft_atoi(target),
    .sign = sign,
    .error = false,
  }; 
}

t_optional_double parse_fractional(const char *target)
{
  const t_optional_int fractional= parse_int(target);
  const t_optional_double error = {.error = true};

  if (fractional.error)
	return error;
  return (t_optional_double) {
	.value = ((double)fractional.value / pow(10, int_len(fractional.value))),
	.error = false,
  };
}

t_optional_double parse_double(const char *target)
{
  const t_optional_array array =  split_string(target, '.');
  const t_optional_double error = {.error = true};
  t_optional_int  whole;
  t_optional_double  fractional;

  if (array.error || array.size > 2)
    return error;
  whole = parse_int(array.value[0]);
  if (whole.error)
    return error;
  if (array.size == 1)
  {
    return (t_optional_double) {
      .value = whole.value,
      .error = false,
    };
  }
  fractional = parse_fractional(array.value[1]);
  if (fractional.error)
    return error;
  fractional.value = whole.sign * fractional.value;
  return (t_optional_double) {
    .value = whole.value + fractional.value,
    .error = false,
  };
}

t_optional_rgb parse_rgb(const char *target)
{
  char **splited;
  t_optional_double *colors;

  if (target == NULL)
	return (t_optional_rgb) {.error = true};
  if (count_char(target, ',') != 2)
	return (t_optional_rgb) {.error = true};
  splited = ft_split(target, ',');
  if (array_len(splited) != 3)
	return (t_optional_rgb) {.error = true};
  colors = (t_optional_double [3]) {
	parse_color_ratio(splited[0]),
	parse_color_ratio(splited[1]),
	parse_color_ratio(splited[2])
  };
  if (colors[0].error
	  || colors[1].error
	  || colors[2].error)
	return (t_optional_rgb) {.error = true};
  return (t_optional_rgb){
	.value = color(colors[0].value, colors[1].value, colors[2].value),
	.error = false,
  };
}

t_optional_point parse_position(const char *target)
{
  t_optional_array array = split_string(target, ',');
  t_optional_double *p;

  if (array.error
    || count_char(target, ',') != 2
    || array_len(array.value) != 3)
    return (t_optional_point) {.error = true};
  p = (t_optional_double [3]) {
    parse_double(array.value[0]),
    parse_double(array.value[1]),
    parse_double(array.value[2]),
  };
  if (p[0].error || p[1].error || p[2].error)
    return (t_optional_point) {.error = true};
  return (t_optional_point) {
	.value = point(p[0].value, p[1].value, p[2].value),
	.error = false,
  };
}

t_optional_double parse_fov(const char *target)
{
  t_optional_int deg;

  deg = parse_int(target);
  if (deg.error)
    return (t_optional_double) {.error = true};
  if (deg.value < 0 || deg.value > 180)
    return (t_optional_double) {.error = true};
  return (t_optional_double) {
    .value = radians(deg.value),
    .error = false,
  };
}

t_optional_string parse_string(char *target)
{
  if (target == NULL)
    return (t_optional_string){.is_null = true};
  return (t_optional_string) {
    .value = target,
    .size = ft_strlen(target),
    .is_null = false,
  };
}

t_optional_int parse_type(char *target)
{
  const t_optional_string string = parse_string(target);
  
  if (string.is_null)
    return (t_optional_int) {.error = true}; 
  if (is_equal_str(string.value, "L"))
    return (t_optional_int){.value = e_light};
  if (is_equal_str(string.value, "C"))
    return (t_optional_int){.value = e_camera};
  if (is_equal_str(string.value, "A"))
    return (t_optional_int){.value = e_ambient};
  if (is_equal_str(string.value, "sp"))
    return (t_optional_int){.value = e_sphere};
  if (is_equal_str(string.value, "pl"))
    return (t_optional_int){.value = e_plane};
  return (t_optional_int){.error = true};
}

void correct_ambient(t_world w, t_material ambient)
{
  for (int i = 0;i < w.amount_of_shapes;++i) {
    w.shapes[i].super.material.ambient_color = ambient.ambient_color;
    w.shapes[i].super.material.ambient_ratio = ambient.ambient_ratio;
  }
}
