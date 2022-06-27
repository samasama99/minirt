#include "parsing.h"
#include <assert.h>

t_optional_int get_digit(const char *d)
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

t_optional_array get_array(const char *line, const char delimiter)
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

t_optional_double get_ratio(const char *target)
{
  const t_optional_array array =  get_array(target, '.');
  t_optional_int  whole;
  t_optional_int  fractional;

  if (array.error || array_len(array.value) != 2)
    return (t_optional_double){.error = true};
  whole = get_digit(array.value[0]);
  fractional = get_digit(array.value[1]);
  if (whole.error || fractional.error)
    return (t_optional_double){.error = true};
  if (fractional.value / 10. + whole.value > 1.0
      || fractional.value / 10. + whole.value < 0.0)
    return (t_optional_double){.error = true};
  return (t_optional_double) {
    .value = whole.value + fractional.value / 10.,
    .error = false,
  };
}

t_optional_double get_color_ratio(const char *target)
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

t_optional_int get_int(const char *target)
{
  if (target == NULL)
    return (t_optional_int) {.error = true};
  if (ft_isnumber(target + (target[0] == '-')) == false)
    return (t_optional_int) {.error = true};
  return (t_optional_int) {
    .value = ft_atoi(target),
    .error = false,
  }; 
}

t_optional_double get_fractional(const char *target)
{
  const t_optional_int fractional= get_int(target);
  const t_optional_double error = {.error = true};

  if (fractional.error)
    return error;
  return (t_optional_double) {
    .value = ((double)fractional.value / pow(10, int_len(fractional.value))),
    .error = false,
  };
}

t_optional_double get_double(const char *target)
{
  const t_optional_array array =  get_array(target, '.');
  const t_optional_double error = {.error = true};
  t_optional_int  whole;
  t_optional_double  fractional;

  if (array.error || array.size > 2)
    return error;
  whole = get_int(array.value[0]);
  if (whole.error)
    return error;
  if (array.size == 1)
  {
    return (t_optional_double) {
      .value = whole.value,
      .error = false,
    };
  }
  fractional = get_fractional(array.value[1]);
  if (fractional.error)
    return error;
  if (whole.value < 0)
    fractional.value = -1 * fractional.value;
  return (t_optional_double) {
    .value = whole.value + fractional.value,
    .error = false,
  };
}

t_optional_rgb get_rgb(const char *target)
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
    get_color_ratio(splited[0]),
    get_color_ratio(splited[1]),
    get_color_ratio(splited[2])
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

t_optional_point get_position(const char *target)
{
  t_optional_array array = get_array(target, ',');
  t_optional_double *p;

  if (array.error
    || count_char(target, ',') != 2
    || array_len(array.value) != 3)
    return (t_optional_point) {.error = true};
  p = (t_optional_double [3]) {
    get_double(array.value[0]),
    get_double(array.value[1]),
    get_double(array.value[2]),
  };
  if (p[0].error || p[1].error || p[2].error)
    return (t_optional_point) {.error = true};
  return (t_optional_point) {
    .value = point(p[0].value, p[1].value, p[2].value),
    .error = false,
  };
}

t_optional_double get_fov(const char *target)
{
  t_optional_int deg;

  deg = get_int(target);
  if (deg.error)
    return (t_optional_double) {.error = true};
  if (deg.value < 0 || deg.value > 180)
    return (t_optional_double) {.error = true};
  return (t_optional_double) {
    .value = radians(deg.value),
    .error = false,
  };
}

typedef struct {
  t_world w;
  t_camera c;
  t_material ambient;
} t_data;

t_data parse(int fd, t_res res)
{
  t_data data;
  char *line;
  bool cam, light, ambient;
  t_optional_material a;
  t_optional_light l;
  t_optional_camera c;
  t_optional_sphere s;
  t_optional_plane p;
  size_t nb_shapes;
  data.w = set_amount_of_shapes(100);

  nb_shapes = 0;
  cam = light = ambient = false;
  while((line = get_next_line(fd)))
  {
    if (is_equal_str(line, "\n") == true)
        continue;
    line = ft_strtrim(line, "\n");
    if (cam == false) {
      c = parse_camera(line, res);
      if (c.error == false) {
          puts("parsing the camera");
          data.c = c.value;
          cam = true;
          continue;
      }  
    }
    if (light == false) {
      l = parse_light(line);
      if (l.error == false) {
          puts("parsing the light");
          data.w.light = l.value;
          light = true;
          continue;
      }  
    }
    if (ambient == false) {
      a = parse_ambient(line);
      if (a.error == false) {
          puts("parsing the ambient");
          data.ambient = a.value;
          ambient = true;
          continue;
      }  
    }
    s = parse_sphere(line);
    if (s.error == false) {
        puts("parsing the sphere");
        data.w = add_shape(data.w, (t_shape)s.value);
        continue;
    }  
    p = parse_plane(line);
    if (p.error == false) {
        puts("parsing the plane");
        data.w = add_shape(data.w, (t_shape)p.value);
        continue;
    }  
    puts("parsing error\n");
    exit(1);
  }
  return data;
}

int main()
{
  int fd = open("test.rt", O_RDONLY);
  if (fd < 0)
    exit(2);
  t_data data = parse(fd, pair(600, 600));
  init_mlx(pair(600, 600), pair(0, 0));
  render(data.c, data.w);
  start_mlx();
  close(fd);
}

// int main()
// {
//   // assert(get_type(NULL).error);
//   // assert(get_type("A").value == 'A');
//   // assert(get_type("AB").error);
//  
//   assert(get_digit(NULL).error);
//   assert(get_digit("1").value == 1);
//   assert(get_digit("5.1").error);

//   assert(get_ratio(NULL).error);
//   assert(is_equal_double(get_ratio("1.0").value, 1.0));
//   assert(get_ratio("5.1").error);
//   assert(is_equal_double(get_ratio("0.5").value, 0.5));

//   assert(get_color_ratio(NULL).error);
//   assert(get_color_ratio("256").error);
//   assert(get_color_ratio("10a").error);
//   assert(is_equal_double(get_color_ratio("200").value, 200 / 255.0));
//   assert(is_equal_double(get_color_ratio("60").value, 60 / 255.0));
//   assert(is_equal_double(get_color_ratio("0").value, 0 / 255.0));

//   assert(get_rgb(NULL).error);
//   assert(rgb_is_equal(color(1, 1, 1), get_rgb("255,255,255").value));
//   assert(get_rgb(",255,255,255").error);
//   assert(get_rgb("255,255,255,").error);
//   assert(rgb_is_equal(color(10/255., 15/255., 125/255.), get_rgb("10,15,125").value));

//   {
//     t_optional_material m = parse_ambient("A 0.2 255,255,255");
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient("A 0.8 50,0,255");
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient("A 1.0 50,0,255");
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient("A 0.0 50,0,255");
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient("X 0.2 255,255,255");
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient("A 0.2 ,255,255,255");
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient("A 1.5 255,255,255");
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient("A 0.5 300,255,255");
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }
//   {
//     t_optional_material m = parse_ambient("A 0.5 255,255,255,255");
//     if (m.error == false) {
//       printf ("%f %f %f\n", m.value.ambient_color.red,
//                             m.value.ambient_color.green,
//                             m.value.ambient_color.blue);
//       printf("ratio %f\n", m.value.ambient_ratio);
//     } else {
//       printf ("Error\n");
//     }
//   }

//   assert(get_int("1").value == 1);
//   assert(get_int("-1").value == -1);
//   assert(get_int("50").value == 50);
//   assert(get_int("-65645").value == -65645);
//   assert(get_int("-65645").error == false);
//   assert(get_int("-65645a").error == true);
//   assert(get_int(NULL).error == true);

//   if (get_double("1.1").error == false)
//     printf("1.1 %f\n", get_double("1.1").value);
//   else
//     printf("Error\n");
//   if (get_double("-1.1").error == false)
//     printf("-1.1 %f\n", get_double("-1.1").value);
//   else
//     printf("Error\n");
//   if (get_double("-50.0").error == false)
//     printf("-50.0 %f\n", get_double("-50.0").value);
//   else
//     printf("Error\n");
//   if (get_double("60").error == false)
//     printf("60 %f\n", get_double("60").value);
//   else
//     printf("Error\n");
//   if (get_double("0").error == false)
//     printf("0 %f\n", get_double("0").value);
//   else
//     printf("Error\n");
//   if (get_double("0a").error == false)
//     printf("0a %f\n", get_double("0a").value);
//   else
//     printf("Error\n");
//   if (get_double("a0").error == false)
//     printf("a0 %f\n", get_double("a0").value);
//   else
//     printf("Error\n");

//   print_tupil("test", get_position("-50.0,0,20").value);
//   print_tupil("test", get_position("-40.0,50.0,0.0").value);
//   assert(get_position("10,10,10,").error);
//   assert(get_position(",10,10,10").error);
//   assert(get_position("10,10,10,10").error);
//   t_optional_camera cam = parse_camera("C -50.0,0,20 0,0,1 70", pair(600, 600));
//   assert(cam.error == false);
//   printf ("cam %f\n", cam.value.half_height);
//   printf ("cam %f\n", cam.value.half_width);
//   printf ("cam %f\n", cam.value.hsize);
//   printf ("cam %f\n", cam.value.pixel_size);
//   printf ("cam %f\n", cam.value.transform.l1_c1);
//   printf ("cam %f\n", cam.value.vsize);
//  
//   t_optional_camera cam2 = parse_camera("C 0.0,1.5,-5 0,1,0 60", pair(600, 600));
//   assert(cam2.error == false);
//   printf ("cam %f\n", cam2.value.half_height);
//   printf ("cam %f\n", cam2.value.half_width);
//   printf ("cam %f\n", cam2.value.hsize);
//   printf ("cam %f\n", cam2.value.pixel_size);
//   printf ("cam %f\n", cam2.value.transform.l1_c1);
//   printf ("cam %f\n", cam2.value.vsize);
//   t_camera ctest = camera(600, 600, M_PI / 3);
//   ctest.transform = view_transform(point(0, 1.5, -5),
//                                point(0, 1, 0),
//                                vector(0, 1, 0));
//   printf ("cam %f\n", ctest.half_height);
//   printf ("cam %f\n", ctest.half_width);
//   printf ("cam %f\n", ctest.hsize);
//   printf ("cam %f\n", ctest.pixel_size);
//   printf ("cam %f\n", ctest.transform.l1_c1);
//   printf ("cam %f\n", ctest.vsize);
//   t_optional_light l = parse_light("L -40.0,50.0,0.0 0.6 10,0,255");
//   assert(l.error == false);
//   print_tupil("light", l.value.position);
//   printf ("%f|", l.value.intensity.red);
//   printf ("%f|", l.value.intensity.green);
//   printf ("%f\n", l.value.intensity.blue);
//   system("leaks a.out");
// }
