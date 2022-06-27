#include "main.h"
#include "parsing.h"

t_optional_array valid_line(const char *target, size_t nb_elem, char *type)
{
  char **array;

  if (target == NULL || type == NULL)
    return (t_optional_array){.error = true}; 
  array = ft_split(target, ' ');
  if (array == NULL)
    return (t_optional_array){.error = true}; 
  if (array_len(array) != nb_elem)
    return (t_optional_array){.error = true}; 
  if (is_equal_str(array[0], type) == false)
    return (t_optional_array){.error = true}; 
  return (t_optional_array){
    .value = array + 1,
    .error = false,
  };
}

t_optional_material parse_ambient(const char *line)
{
  const t_optional_array elems = valid_line(line, 3, "A");
  t_optional_double ambient_ratio;
  t_optional_rgb ambient_color;

  if (elems.error)
    return (t_optional_material) {.error = true};
  ambient_ratio = get_ratio(elems.value[0]);
  ambient_color = get_rgb(elems.value[1]);
  if (ambient_ratio.error || ambient_color.error)
    return (t_optional_material) {.error = true};
  return (t_optional_material) {
    .value = {
      .ambient_ratio = ambient_ratio.value,
      .ambient_color = ambient_color.value,
    },
    .error = false,
  };
}

t_optional_transform get_camera_view(char *from, char *to)
{
  const t_optional_transform error = {.error = true};
  t_optional_point p_from;
  t_optional_point p_to;

  p_from = get_position(from);
  p_to = get_position(to);
  if (p_from.error || p_to.error)
    return error;
  return (t_optional_transform) {
    .value = view_transform(p_from.value, p_to.value, vector(0, 1, 0)),
    .error = false,
  };
}

t_optional_camera parse_camera(const char *line, t_res res)
{
  const t_optional_array elems = valid_line(line, 4, "C");
  const t_optional_camera error = {.error = true};
  t_optional_transform camera_view;
  t_camera cam;
  t_optional_double fov;

  if (elems.error)
      return error;
  camera_view = get_camera_view(elems.value[0], elems.value[1]);
  fov = get_fov(elems.value[2]);
  if (camera_view.error || fov.error)
    return error;
  cam = camera(res.height, res.width, fov.value);
  return (t_optional_camera) {
    .value = cam,
    .error = false,
  };
}

t_optional_light parse_light(const char *line)
{
  const t_optional_array elems = valid_line(line, 4, "L");
  const t_optional_light error = {.error = true};
  t_optional_point pos;
  t_optional_double brightness;
  t_optional_rgb color;

  if (elems.error)
      return error;
  pos = get_position(elems.value[0]);
  brightness = get_ratio(elems.value[1]);
  color = get_rgb(elems.value[2]);
  if (pos.error || brightness.error || color.error)
    return (t_optional_light) {.error = true};
  return (t_optional_light) {
    .value = point_light(pos.value, rgb_scalar(color.value, brightness.value)),
    .error = false,
  };
}

t_optional_plane parse_plane(const char *line)
{
  const t_optional_array elems = valid_line(line, 4, "pl");
  const t_optional_plane error = {.error = true};
  t_optional_point p;
  t_optional_point  normal;
  t_optional_rgb  c;

  if (elems.error)
      return error;
  p = get_position(elems.value[0]);
  normal = get_position(elems.value[1]);
  c = get_rgb(elems.value[2]); 
  if (p.error || normal.error || c.error)
    return error;
  return (t_optional_plane){
    .value = make_plane(p.value,
          vector(normal.value.x, normal.value.y, normal.value.z)),
    .error = false,
  };
}

t_optional_sphere parse_sphere(const char *line)
{
  const t_optional_array elems = valid_line(line, 4, "sp");
  const t_optional_sphere error = {.error = true};
  t_optional_point center;
  t_optional_double  diameter;

  if (elems.error)
      return error;
  center = get_position(elems.value[0]);
  diameter = get_double(elems.value[1]);
  if (center.error || diameter.error)
    return error;
  return (t_optional_sphere){
    .value = make_sphere(center.value, diameter.value / 2.0),
    .error = false,
  };
}

