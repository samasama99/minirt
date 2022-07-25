#include "main.h"
#include "parsing.h"

void ft_exit(t_optional_string err, int err_status)
{
  if (err.is_null == false)
    write(1, err.value, err.size);
  exit(err_status);
}

t_optional_string get_line(int fd)
{
  char *line;

  line = get_next_line(fd);
  if (line == NULL)
    return (t_optional_string) {.is_null = true};
  return (t_optional_string) {
    .value = line,
    .size = ft_strlen(line),
    .is_null = false,
  };
}

t_camera unwarp_camera(t_optional_array array, t_res res)
{
  const t_optional_camera c = parse_camera(array, res);

  if (c.error) 
    ft_exit(parse_string("failed to parse the camera"), 1);
  return c.value;
}

t_light unwrap_light(t_optional_array array)
{
  const t_optional_light l = parse_light(array);

  if (l.error) 
    ft_exit(parse_string("failed to parse the light"), 1);
  return l.value;
}

t_material unwrap_ambient(t_optional_array array)
{
  const t_optional_material m = parse_ambient(array);

  if (m.error) 
    ft_exit(parse_string("failed to parse the ambient"), 1);
  return (t_material){
    .ambient_color = m.value.ambient_color,
    .ambient_ratio = m.value.ambient_ratio,
  };
}

t_shape unwrap_shape(t_optional_array array, t_line_type type)
{
  const t_optional_shape m = parse_shape(array, type);

  if (m.error) 
    ft_exit(parse_string("failed to parse a shape"), 1);
  return m.value;
}

void parse(t_data *data, int fd, t_res res)
{
  puts ("hello");
  t_optional_string line;
  t_optional_array array;
  t_optional_int type;

  line.is_null = false;
  while(line.is_null == false)
  {
    line = get_line(fd);
    if (line.is_null || is_equal_str(line.value, "\n"))
      continue;
    line = parse_string(ft_strtrim(line.value, "\n"));
    array = split_string(line.value, ' ');
    type = parse_type(array.value[0]);
    if (line.is_null || array.error || type.error)
      ft_exit(parse_string("parsing error"), 1);
    if (type.value == e_camera)
        data->c = unwarp_camera(array, res);
    if (type.value == e_light)
        data->w.light = unwrap_light(array);
    if (type.value == e_ambient)
        data->ambient = unwrap_ambient(array);
   
    if (type.value == e_sphere || type.value == e_plane || type.value == e_cylinder)
        data->w = add_shape(data->w, unwrap_shape(array, type.value));
  }
}
