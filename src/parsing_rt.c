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

t_camera is_valid_camera(t_optional_array array, t_res res)
{
  const t_optional_camera c = parse_camera(array, res);

  if (c.error) 
    ft_exit(get_string("failed to parse the camera"), 1);
  return c.value;
}

t_light is_valid_light(t_optional_array array)
{
  const t_optional_light l = parse_light(array);

  if (l.error) 
    ft_exit(get_string("failed to parse the light"), 1);
  return l.value;
}

t_material is_valid_ambient(t_optional_array array)
{
  const t_optional_material m = parse_ambient(array);

  if (m.error) 
    ft_exit(get_string("failed to parse the ambient"), 1);
  return (t_material){
    .ambient_color = m.value.ambient_color,
    .ambient_ratio = m.value.ambient_ratio,
  };
}

t_shape is_valid_shape(t_optional_array array, t_line_type type)
{
  const t_optional_shape m = parse_shape(array, type);

  if (m.error) 
    ft_exit(get_string("failed to parse a shape"), 1);
  return m.value;
}

void parse(t_data *data, int fd, t_res res)
{
  t_optional_string line;
  t_optional_array array;
  t_optional_int type;

  line.is_null = false;
  while(line.is_null == false)
  {
    line = get_line(fd);
    if (line.is_null || is_equal_str(line.value, "\n"))
      continue;
    line = get_string(ft_strtrim(line.value, "\n"));
    array = get_array(line.value, ' ');
    type = get_type(array.value[0]);
    if (line.is_null || array.error || type.error)
      ft_exit(get_string("parsing error"), 1);
    if (type.value == e_camera)
        data->c = is_valid_camera(array, res);
    if (type.value == e_light)
        data->w.light = is_valid_light(array);
    if (type.value == e_ambient)
        data->ambient = is_valid_ambient(array);
    if (type.value == e_sphere || type.value == e_plane)
        data->w = add_shape(data->w, is_valid_shape(array, type.value));
  }
}
