#include "src/parsing.h"

t_optional_string what_shape(t_shape_type type)
{
  if (type == Sphere)
    return (get_string("Sphere"));
  if (type == Plane)
    return (get_string("Plane"));
  return (t_optional_string){.is_null = true};
}

int select_shape(int button,  int x, int y, t_data *data)
{
  if (button == 1 || button == 2)
  {
    t_ray r = ray_for_pixel(data->c, x, y);
    t_hit h = intersect_world(data->w, r);
    t_intersection i = hit(h);
    if (i.t >= 0)
    {
      printf ("%s id = %d\n",
              what_shape(i.shape.type).value,
              i.shape.super.id);
      data->selected.value = i.shape; 
      data->selected.error = false;
    }
    else
    {
      data->selected.error = true;
      printf ("no shape was hit\n");
    }
  }
  return 0;
}

t_optional_int find_shape(t_world w, t_shape_type type, int id)
{
    int i;

    i = 0;
    while (i < w.amount_of_shapes)
    {
      if (type == w.shapes[i].type
        && id == w.shapes[i].super.id)
      {
         return (t_optional_int) {
          .value = i,
          .error = false,
         };
        break;
      }
      ++i;
    }
    return (t_optional_int){.error = true};
}

t_transform rotation_type(t_key key)
{
    if (key == UP_ARROW)
      return rotation_x(radians(10));
    if (key == DOWN_ARROW)
      return rotation_x(radians(-10));
    if (key == RIGHT_ARROW)
      return rotation_z(radians(010));
    if (key == LEFT_ARROW)
      return rotation_z(radians(-10));
    return identity();
}

t_shape rotate_shape(t_shape s, t_key key)
{
  t_shape ns;

  printf ("%s id = %d is rotated\n", what_shape(s.type).value, s.super.id);
  ns = s;
  ns.super.transform = mat4_mult(rotation_type(key),
                                                    s.super.transform);
  return ns;
}

t_shape scale_shape(t_shape s, t_key key)
{
  t_shape ns;

  printf ("%s id = %d is scaled\n", what_shape(s.type).value, s.super.id);
  ns = s;
  if (s.type == Sphere)
  {
    if (key == MINUS_KEY)
        ns.sphere.radius = s.sphere.radius * 0.8;
    if (key == PLUS_KEY)
        ns.sphere.radius = s.sphere.radius * 1.2;
  }
  return ns;
}

t_shape duplicate_shape(t_shape s)
{
  t_shape ns;

  printf ("%s id = %d is duplicated x\n", what_shape(s.type).value, s.super.id);
  if (s.type == Plane)
    ns =(t_shape)make_plane(s.plane.position, s.plane.normal);
  if (s.type == Sphere)
    ns = (t_shape)make_sphere(s.sphere.center, s.sphere.radius, s.sphere.material.color);
  return ns;
}

t_vec move_vector(t_key key, t_shape s, t_camera c)
{
  double value;
  // if (s.type == Plane)
    value = c.half_height / 10;
  // // if (s.type == Sphere)
    // value =  s.sphere.radius / 10;
  if (key == W_KEY)
      return vector(0, value, 0);
  if (key == S_KEY)
      return vector(0, -value, 0);
  if (key == D_KEY)
      return vector(value, 0, 0);
  if (key == A_KEY)
      return vector(-value, 0, 0);
  return vector(0, 0, 0);
}


t_shape move_shape(t_key key, t_shape s, t_camera c)
{
  t_shape ns;

  printf ("%s id = %d is moved\n", what_shape(s.type).value, s.super.id);
  ns = s;
  if (s.type == Sphere)
     ns.sphere.center = sum(s.sphere.center, move_vector(key, s, c));
  if (s.type == Plane)
     ns.plane.position = sum(s.plane.position, move_vector(key, s, c));
  if (s.type == Plane)
    print_tupil("hello", ns.plane.position);
  return ns;
}

int esp(int key, t_data *data)
{
  if (key == ESC)
    exit(1);
  return 0;
}
int ren(int key, t_data *data)
{
  if (key == 49) {
    render(data->c, data->w);
    return 1;
  }
  return 0;
}

int shape_manipulation(int key, t_data *data)
{
  int index;
  t_shape s;

  if (esp(key, data) || ren(key, data))
    return 0;
  if (data->selected.error)
    return printf ("nothing is selected\n");
  index = find_shape(data->w, data->selected.value.type, data->selected.value.super.id).value;
  s  = data->w.shapes[index]; 
  if (key == 35)
      data->w = add_shape(data->w, duplicate_shape(s));
  if (key == UP_ARROW || key == DOWN_ARROW || key == LEFT_ARROW || key == RIGHT_ARROW)
      data->w.shapes[index] = rotate_shape(s, key);
  if (key == MINUS_KEY || key == PLUS_KEY)
      data->w.shapes[index] = scale_shape(data->w.shapes[index], key);
  if (key == W_KEY || key == S_KEY || key == D_KEY || key == A_KEY)
      data->w.shapes[index] =  move_shape(key, s, data->c);
  return 0;
}

int main()
{
  t_res res = pair(500, 500);
  int fd = open("src/test.rt", O_RDONLY);
  if (fd < 0)
	  exit(2);
  t_data data;
  data.selected.error = true;
  data.w = set_amount_of_shapes(20);
  parse(&data, fd, res);
  close(fd);
  correct_ambient(data.w, data.ambient);
  init(res, pair(0, 0));
  printf ("The amount of shapes %d\n", data.w.amount_of_shapes);
  render(data.c, data.w);
  listen_to(mouseup, select_shape, &data);
  listen_to(keydown, shape_manipulation, &data);
  start();
}

