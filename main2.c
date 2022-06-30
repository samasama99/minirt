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
  printf ("%d %d %d\n", button, x, y);
  if (button == 1 || button == 2)
  {
    t_ray r = ray_for_pixel(data->c, x, y);
    t_hit h = intersect_world(data->w, r);
    t_intersection i = hit(h);
    if (i.t >= 0)
    {
      printf ("%s id = %d t = %f\n",
              what_shape(i.shape.type).value,
              i.shape.super.id,
              i.t);
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

int move_shape(int key, t_data *data)
{
  if (key == 49) {
    render(data->c, data->w);
    return 0;
  }
  if (key == ESC)
    exit (0);
  if (data->selected.error)
  {
    printf ("nothing is selected\n");
    return 0;
  }
  t_optional_int index = find_shape(data->w, data->selected.value.type, data->selected.value.super.id);
  if (index.error == true)
  {
    printf ("nothing is selected\n");
    return 0;
  }
  t_world w = data->w;
  t_camera c = data->c;
  if (w.shapes[index.value].type != Sphere)
    return 0;
  if (key == MINUS_KEY)
  {
      printf ("%s id = %d is scaled down\n",
              what_shape(data->selected.value.type).value,
              data->selected.value.super.id);
      w.shapes[index.value].sphere.radius = w.shapes[index.value].sphere.radius * 0.8;
  }
  if (key == PLUS_KEY)
  {
      printf ("%s id = %d is scaled up\n",
              what_shape(data->selected.value.type).value,
              data->selected.value.super.id);
      w.shapes[index.value].sphere.radius = w.shapes[index.value].sphere.radius * 1.2;
 
  }
  if (key == W_KEY)
  {
      printf ("%s id = %d is pushed back\n",
              what_shape(data->selected.value.type).value,
              data->selected.value.super.id);
         data->w.shapes[index.value].sphere.center = sum(data->w.shapes[index.value].sphere.center,
                                              vector(0, 0, data->w.shapes[index.value].sphere.radius / 10));
    return 0;
  }
  if (key == UP_ARROW)
  {
      printf ("%s id = %d is pushed up\n",
              what_shape(data->selected.value.type).value,
              data->selected.value.super.id);
         data->w.shapes[index.value].sphere.center = sum(data->w.shapes[index.value].sphere.center,
                                              vector(0, data->w.shapes[index.value].sphere.radius / 10, 0));
    return 0;
  }
  if (key == DOWN_ARROW)
  {
      printf ("%s id = %d is pushed down\n",
              what_shape(data->selected.value.type).value,
              data->selected.value.super.id);
         data->w.shapes[index.value].sphere.center = sub(data->w.shapes[index.value].sphere.center,
                                              vector(0, data->w.shapes[index.value].sphere.radius / 10, 0));
    return 0;
  }
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
  data.w = set_amount_of_shapes(6);
  parse(&data, fd, res);
  close(fd);
  correct_ambient(data.w, data.ambient);
  init(res, pair(0, 0));
  printf ("%d\n", data.w.amount_of_shapes);
  render(data.c, data.w);
  listen_to(mouseup, select_shape, &data);
  listen_to(keydown, move_shape, &data);
  start();
}

