#include "src/parsing.h"

t_optional_string what_shape(t_shape_type type)
{
  if (type == Sphere)
    return (parse_string("Sphere"));
  if (type == Plane)
    return (parse_string("Plane"));
  return (t_optional_string){.is_null = true};
}

void put_black_bar(t_res res, t_pair pos)
{
  const t_image black_bar = create_image(res);

  put_image(pos, black_bar);
}

void put_selected_shape(t_optional_shape shape)
{
  put_black_bar(pair(600, 25), pair(0, 0));
  if (shape.error == false)
  {
    // if (shape.value.type == Plan) {

    // }
    char *str1 = ft_strjoin(what_shape(shape.value.type).value, " ");
    char *str2 = ft_strjoin(str1, ft_itoa(shape.value.super.id));
    char *str3 = ft_strjoin(str2, " is selected");
    put_string(100, 0, str3);
  }
  else
    put_string(100, 0, "no shape was hit");
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
      put_selected_shape((t_optional_shape){.value = i.shape});
      data->selected.value = i.shape; 
      data->selected.error = false;
    }
    else
    {
      put_selected_shape((t_optional_shape){.error = true});
      data->selected.error = true;
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

  // printf ("%s id = %d is rotated\n", what_shape(s.type).value, s.super.id);
  ns = s;
  ns.super.transform = mat4_mult(rotation_type(key),
                                                    s.super.transform);
  return ns;
}

t_shape scale_shape(t_shape s, t_key key)
{
  t_shape ns;

  // printf ("%s id = %d is scaled\n", what_shape(s.type).value, s.super.id);
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

  // printf ("%s id = %d is duplicated x\n", what_shape(s.type).value, s.super.id);
  if (s.type == Plane)
    ns =(t_shape)make_plane(s.plane.position, s.plane.normal);
  if (s.type == Sphere)
    ns = (t_shape)make_sphere(s.sphere.center, s.sphere.radius, s.sphere.material.color);
  return ns;
}

t_vec move_vector(t_key key, t_shape s, t_camera c)
{
  const double value = c.half_height / 10;

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

  // printf ("%s id = %d is moved\n", what_shape(s.type).value, s.super.id);
  ns = s;
  if (s.type == Sphere)
     ns.sphere.center = sum(s.sphere.center, move_vector(key, s, c));
  if (s.type == Plane)
     ns.plane.position = sum(s.plane.position, move_vector(key, s, c));
  // if (s.type == Plane)
  //   print_tupil("hello", ns.plane.position);
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

  put_selected_shape(data->selected);
  if (esp(key, data) || ren(key, data) || data->selected.error)
    return 0;
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

void ft_perror(int exit_status)
{
  perror("Error");
  exit(exit_status);
}

int main()
{
  const t_res canvas_size = pair(1200, 675);
  const t_res res = pair(canvas_size.x, canvas_size.y + 25);
  const int fd = open("src/test.rt", O_RDONLY);
  t_data  data;
  if (fd < 0)
    ft_perror(1);
  data.w.amount_of_shapes = 0;
  data.selected.error = true;
  parse(&data, fd, canvas_size);
  close(fd);
  correct_ambient(data.w, data.ambient);
  printf ("The amount of shapes %d\n", data.w.amount_of_shapes);
  print_tupil("cy", data.w.shapes[0].cylinder.normal);
  // printf ("normal | vec x  = %fdot %frad %fdeg\n", dot(normalize(data.w.shapes[0].cylinder.normal), vector(1,0,0)),radians(acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(1,0,0))))
  //                                   , acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(1,0,0))));
  // printf ("normal | vec y  = %fdot %frad %fdeg\n", dot(normalize(data.w.shapes[0].cylinder.normal), vector(0,1,0)),radians(acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(0,1,0))))
  //                                   , acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(0,1,0))));
  // printf ("normal | vec z  = %fdot %frad %fdeg\n", dot(normalize(data.w.shapes[0].cylinder.normal), vector(0,0,1)),radians(acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(0,0,1))))
  //                                   , acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(0,0,1))));                   
//  data.w.shapes[0].cylinder.t = transform 
//                                   (
//                                     rotation_x(acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(0,0,1)))),
//                                     rotation_y(acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(1,0,0)))),
//                                      rotation_z(acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(0,0,1))))
//                                   );
//  data.w.shapes[0].cylinder.t = mat4_mult(mat4_mult(rotation_x(acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(0,1,0))))
//                                         , rotation_z(acos(dot(vector(0,1,0), normalize(data.w.shapes[0].cylinder.normal)))))
//                                         , rotation_y( acos(dot(normalize(data.w.shapes[0].cylinder.normal), vector(1,0,0)))));
  // data.w.shapes[0].cylinder.t = rotation_z(50);
  init(res, "miniRt");
  render(data.c, data.w);
  // listen_to(mouseup, select_shape, &data);
  // listen_to(keydown, shape_manipulation, &data);
  start();
}

//  int main()
//  {
//    const t_res canvas_size = pair(1200, 675);
//    const t_res res = pair(canvas_size.x, canvas_size.y + 25);
//    init(res, "miniRt");
//    t_world w;
//     t_sphere s = sphere();
//     s.material.ambient_color = color(0.5, 0, 0);
//    w = add_shape(w, (t_shape)cylinder());
//    t_light light = point_light(point(0, 0, -30), color(1, 1, 1));
//    t_camera c = camera(res.x, res.y, M_PI / 3);
//    c.transform = view_transform(point(0, 0, -30),
//                                 point(0, 0, 0),
//                                 vector(0, 1, 0));
//    w.light = light;
//    printf ("The amount of shapes %d\n", w.amount_of_shapes);

//    render(c, w);
//    puts("here");
//    start();
//  }

// #include <assert.h>
// int main() {
// 	{
// 		t_ray r = ray(point(1, 0, 0), vector(0, 1, 0));
// 		t_cylinder cy = cylinder();
// 		t_hit h = intersect_cylinder(cy, r);
// 		assert(h.count == 0);
//     printf ("test1\n");
// 	}
// 	{
// 		t_ray r = ray(point(0, 0, 0), vector(0, 1, 0));
// 		t_cylinder cy = cylinder();
// 		t_hit h = intersect_cylinder(cy, r);
// 		assert(h.count == 0);
//      printf ("test2\n");
// 	}
// 	{
// 		t_ray r = ray(point(0, 0, -5), vector(1, 1, 1));
// 		t_cylinder cy = cylinder();
// 		t_hit h = intersect_cylinder(cy, r);
// 		assert(h.count == 0);
//      printf ("test3\n");
// 	}

//  {
// 		t_cylinder cy = cylinder();
//     assert(vec_is_equal(normal_at_cylinder(cy, point(1, 0, 0)), vector(1, 0, 0)));
//     assert(vec_is_equal(normal_at_cylinder(cy, point(0, 5, -1)), vector(0, 0, -1)));
//     assert(vec_is_equal(normal_at_cylinder(cy, point(0, -2, 1)), vector(0, 0, 1)));
//     assert(vec_is_equal(normal_at_cylinder(cy, point(-1, 1, 0)), vector(-1, 0, 0)));
//      printf ("normal tests\n");
//   }

//   {
//     t_ray r = ray(point(1, 0, -5), vector(0, 0, 1));
// 		t_cylinder cy = cylinder();
// 		t_hit h = intersect_cylinder(cy, r);
//     printf ("the count is (%d), roots are (%f, %f)\n"
//         , h.count, h.intersections[0].t, h.intersections[1].t);
//     assert(is_equal_double(h.intersections[0].t, 5));
//     assert(is_equal_double(h.intersections[1].t, 5));
// 		assert(h.count == 2);
//     printf ("test4\n");
//   }
//   {
//     t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
// 		t_cylinder cy = cylinder();
// 		t_hit h = intersect_cylinder(cy, r);
//     printf ("the count is (%d), roots are (%f, %f)\n"
//         , h.count, h.intersections[0].t, h.intersections[1].t);
//     assert(is_equal_double(h.intersections[0].t, 4));
//     assert(is_equal_double(h.intersections[1].t, 6));
// 		assert(h.count == 2);
//      printf ("test5\n");
//   }
//     {
//     t_ray r = ray(point(0.5, 0, -5), vector(0.1, 1, 1));
// 		t_cylinder cy = cylinder();
// 		t_hit h = intersect_cylinder(cy, r);
//     printf ("the count is (%d), roots are (%f, %f)\n"
//         , h.count, h.intersections[0].t, h.intersections[1].t);
//     assert(is_equal_double(h.intersections[0].t, 6.80798));
//     assert(is_equal_double(h.intersections[1].t, 7.08872));
// 		assert(h.count == 2);
//      printf ("test6\n");
//   }
// }
