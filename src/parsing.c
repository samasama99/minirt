#include "main.h"
#include <assert.h>

typedef struct s_optional_material {
  t_material material;
  bool error;
} t_optional_material;


typedef struct s_optional_camera {
  t_camera camera;
  bool error;
} t_optional_camera;

typedef struct s_optional_point {
  t_point point;
  bool error;
} t_optional_point;

typedef struct s_optional_int {
  int num;
  bool error;
} t_optional_int;

typedef struct s_optional_rgb {
  t_rgb color;
  bool error;
} t_optional_rgb;

typedef struct s_optional_double {
  double num;
  bool error;
} t_optional_double;

typedef struct s_optional_light {
  t_light light;
  bool error;
} t_optional_light;

int count_char(char *str, char c)
{
  int i;
  int count;

  i = 0;
  count = 0;
  while (str[i]) {
    if (str[i] == c)
      ++count;
    ++i;
  }
  return count;
}

size_t array_len(char **array)
{
  size_t i;

  i = 0;
  while (array[i])
    ++i;
  return i;
}

char get_type(char *target)
{
  if (target == NULL)
    return -1;
  if (ft_strlen(target) != 1)
    return -1;
  if (ft_isalpha(target[0]) != 1)
    return -1;
  if (target[0] != 'A'
      && target[0] != 'C'
      && target[0] != 'L')
    return -1;
  return target[0];
}

int get_digit(char *d)
{
  if (d == NULL || d[0] == '\0')
    return -1;
  if (ft_strlen(d) != 1)
    return -1;
  if (ft_isdigit(d[0]) != 1)
    return -1;
  return ft_atoi(d);
}

float get_ratio(char *target)
{
  char    **f;
  double  whole;
  double  fractional;

  printf ("Here ??\n");
  if (target == NULL)
    return -1;
  if (ft_strlen(target) != 3)
    return -1;
  f = ft_split(target, '.');
  whole = get_digit(f[0]);
  if (f[1] == NULL)
    return -1;
  if (!is_equal_double(whole, 0.0)
    && !is_equal_double(whole, 1.0))
    return -1;
  fractional = get_digit(f[1]) / 10.0;
  if (fractional > 1.0 || fractional < 0.0)
    return -1;
  if (fractional + whole > 1.0
      || fractional + whole < 0.0)
    return -1;
  return whole + fractional;
}

bool ft_isnumber(char *num)
{
  size_t i;

  i = 0;
  while (num[i])
  {
    if (ft_isdigit(num[i]) != 1)
        return false;
    ++i;
  }
  return true;
}

double get_color_ratio(char *target)
{
  int num;

  if (target == NULL)
    return -1;
  if (ft_isnumber(target) == false)
    return -1;
  num = ft_atoi(target);
  if (num < 0 || num > 255)
    return -1;
  return num / 255.0;
}

t_optional_int get_int(char *target)
{
  int i;

  i = 0;
  if (target == NULL)
    return (t_optional_int) {.error = true};
  if (target[0] == '-')
    i = 1;
  if (ft_isnumber(target + i) == false)
    return (t_optional_int) {.error = true};
  return (t_optional_int) {
    .num = ft_atoi(target),
    .error = false,
  }; 
}

size_t int_len(int num)
{
  int i;

  i = 0;
  while (num)
  {
    num = num / 10;
    ++i;
  }
  return i;
}

t_optional_double get_double(char *target)
{
  char    **f;
  t_optional_int  whole;
  t_optional_int  fractional;

  if (target == NULL)
    return (t_optional_double) {.error = true};
  f = ft_split(target, '.');
  whole = get_int(f[0]);
  if (whole.error)
    return (t_optional_double) {.error = true};
  if (f[1] == NULL) {
    return (t_optional_double) {
      .num = whole.num,
      .error = false,
    };
  }
  fractional = get_int(f[1]);
  if (fractional.error)
    return (t_optional_double) {.error = true};
  if (whole.num < 0)
    fractional.num = -1 * fractional.num;
  return (t_optional_double) {
    .num = whole.num + (fractional.num / pow(10, int_len(fractional.num))),
    .error = false,
  };
}

t_optional_rgb get_rgb(char *target)
{
  char **splited;
  double *colors;

  if (target == NULL)
    return (t_optional_rgb) {.error = true};
  if (count_char(target, ',') != 2)
    return (t_optional_rgb) {.error = true};
  splited = ft_split(target, ',');
  if (array_len(splited) != 3)
    return (t_optional_rgb) {.error = true};
  colors = (double [3]) {
    get_color_ratio(splited[0]),
    get_color_ratio(splited[1]),
    get_color_ratio(splited[2])
  };
  if (colors[0] == -1
      || colors[1] == -1
      || colors[2] == -1)
    return (t_optional_rgb) {.error = true};
  return (t_optional_rgb){
    .color = color(colors[0], colors[1], colors[2]),
    .error = false,
  };
}

t_optional_material parse_ambient(char *line)
{
  char **splited;
  double ambient_ratio;
  t_optional_rgb ambient_color;

  splited = ft_split(line, ' ');
  if (array_len(splited) != 3)
      return (t_optional_material) {.error = true};
  if (get_type(splited[0]) != 'A')
    return (t_optional_material) {.error = true};
  ambient_ratio = get_ratio(splited[1]);
  if (is_equal_double(ambient_ratio, -1.0))
    return (t_optional_material) {.error = true};
  ambient_color = get_rgb(splited[2]);
  if (ambient_color.error)
     return (t_optional_material) {.error = true,};
  return (t_optional_material) {
    .material = {
      .ambient_ratio = ambient_ratio,
      .ambient_light_color = ambient_color.color,
    },
    .error = false,
  };
}

t_optional_point get_position(char *target)
{
  char **splited;
  t_optional_double *p;

  if (target == NULL)
    return (t_optional_point) {.error = true};
  if (count_char(target, ',') != 2)
    return (t_optional_point) {.error = true};
  splited = ft_split(target, ',');
  if (array_len(splited) != 3)
    return (t_optional_point) {.error = true};
  p = (t_optional_double [3]) {
    get_double(splited[0]),
    get_double(splited[1]),
    get_double(splited[2])
  };
  if (p[0].error
      || p[1].error
      || p[2].error)
    return (t_optional_point) {.error = true};
  return (t_optional_point) {
    .point = point(p[0].num, p[1].num, p[2].num),
    .error = false,
  };
}

t_optional_double get_fov(char *target)
{
  t_optional_int deg;

  deg = get_int(target);
  if (deg.error)
    return (t_optional_double) {.error = true};
  if (deg.num < 0 || deg.num > 180)
    return (t_optional_double) {.error = true};
  return (t_optional_double) {
    .num = radians(deg.num),
    .error = false,
  };
}

t_optional_camera parse_camera(char *line, t_res res)
{
  char **splited;
  t_optional_point from;
  t_optional_point to;
  t_optional_double fov;
  t_camera cam;

  splited = ft_split(line, ' ');
  if (array_len(splited) != 4)
      return (t_optional_camera) {.error = true};
  if (get_type(splited[0]) != 'C')
    return (t_optional_camera) {.error = true};
  from = get_position(splited[1]);
  if (from.error)
    return (t_optional_camera) {.error = true};
  to = get_position(splited[2]);
  if (to.error)
    return (t_optional_camera) {.error = true};
  fov = get_fov(splited[3]);
  if (fov.error)
    return (t_optional_camera) {.error = true};
  cam = camera(res.height, res.width, fov.num);
  cam.transform = view_transform(from.point, to.point, vector(0, 1, 0));
  return (t_optional_camera) {
    .camera = cam,
    .error = false,
  };
}

t_optional_light parse_light(char *line)
{
  char **splited;
  t_optional_point pos;
  double brightness;
  t_optional_rgb color;

  if (line == NULL)
    return (t_optional_light) {.error = true};
  splited = ft_split(line, ' ');
  if (get_type(splited[0]) != 'L')
    return (t_optional_light) {.error = true};
  pos = get_position(splited[1]);
  if (pos.error)
    return (t_optional_light) {.error = true};
  brightness = get_ratio(splited[2]);
  if (brightness == -1)
    return (t_optional_light) {.error = true};
  color = get_rgb(splited[3]);
  if (color.error)
    return (t_optional_light) {.error = true};
  return (t_optional_light) {
    .light = point_light(pos.point, rgb_scalar(color.color, brightness)),
    .error = false,
  };
}

int main()
{
  assert(get_type(NULL) == -1);
  assert(get_type("A") == 'A');
  assert(get_type("AB") == -1);
 
  assert(get_digit(NULL) == -1);
  assert(get_digit("1") == 1);
  assert(get_digit("5.1") == -1);

  assert(is_equal_double(get_ratio(NULL), -1));
  assert(is_equal_double(get_ratio("1.0"), 1.0));
  assert(is_equal_double(get_ratio("5.1"), -1));
  assert(is_equal_double(get_ratio("0.5"), 0.5));

  assert(is_equal_double(get_color_ratio(NULL), -1));
  assert(is_equal_double(get_color_ratio("256"), -1));
  assert(is_equal_double(get_color_ratio("10a"), -1));
  assert(is_equal_double(get_color_ratio("200"), 200 / 255.0));
  assert(is_equal_double(get_color_ratio("60"), 60 / 255.0));
  assert(is_equal_double(get_color_ratio("0"), 0 / 255.0));

  assert(get_rgb(NULL).error);
  assert(rgb_is_equal(color(1, 1, 1), get_rgb("255,255,255").color));
  assert(get_rgb(",255,255,255").error);
  assert(get_rgb("255,255,255,").error);
  assert(rgb_is_equal(color(10/255., 15/255., 125/255.), get_rgb("10,15,125").color));

  {
    t_optional_material m = parse_ambient("A 0.2 255,255,255");
    if (m.error == false) {
      printf ("%f %f %f\n", m.material.ambient_light_color.red,
                            m.material.ambient_light_color.green,
                            m.material.ambient_light_color.blue);
      printf("ratio %f\n", m.material.ambient_ratio);
    } else {
      printf ("Error\n");
    }
  }
  {
    t_optional_material m = parse_ambient("A 0.8 50,0,255");
    if (m.error == false) {
      printf ("%f %f %f\n", m.material.ambient_light_color.red,
                            m.material.ambient_light_color.green,
                            m.material.ambient_light_color.blue);
      printf("ratio %f\n", m.material.ambient_ratio);
    } else {
      printf ("Error\n");
    }
  }
  {
    t_optional_material m = parse_ambient("A 1.0 50,0,255");
    if (m.error == false) {
      printf ("%f %f %f\n", m.material.ambient_light_color.red,
                            m.material.ambient_light_color.green,
                            m.material.ambient_light_color.blue);
      printf("ratio %f\n", m.material.ambient_ratio);
    } else {
      printf ("Error\n");
    }
  }
  {
    t_optional_material m = parse_ambient("A 0.0 50,0,255");
    if (m.error == false) {
      printf ("%f %f %f\n", m.material.ambient_light_color.red,
                            m.material.ambient_light_color.green,
                            m.material.ambient_light_color.blue);
      printf("ratio %f\n", m.material.ambient_ratio);
    } else {
      printf ("Error\n");
    }
  }
  {
    t_optional_material m = parse_ambient("X 0.2 255,255,255");
    if (m.error == false) {
      printf ("%f %f %f\n", m.material.ambient_light_color.red,
                            m.material.ambient_light_color.green,
                            m.material.ambient_light_color.blue);
      printf("ratio %f\n", m.material.ambient_ratio);
    } else {
      printf ("Error\n");
    }
  }
  {
    t_optional_material m = parse_ambient("A 0.2 ,255,255,255");
    if (m.error == false) {
      printf ("%f %f %f\n", m.material.ambient_light_color.red,
                            m.material.ambient_light_color.green,
                            m.material.ambient_light_color.blue);
      printf("ratio %f\n", m.material.ambient_ratio);
    } else {
      printf ("Error\n");
    }
  }
  {
    t_optional_material m = parse_ambient("A 1.5 255,255,255");
    if (m.error == false) {
      printf ("%f %f %f\n", m.material.ambient_light_color.red,
                            m.material.ambient_light_color.green,
                            m.material.ambient_light_color.blue);
      printf("ratio %f\n", m.material.ambient_ratio);
    } else {
      printf ("Error\n");
    }
  }
  {
    t_optional_material m = parse_ambient("A 0.5 300,255,255");
    if (m.error == false) {
      printf ("%f %f %f\n", m.material.ambient_light_color.red,
                            m.material.ambient_light_color.green,
                            m.material.ambient_light_color.blue);
      printf("ratio %f\n", m.material.ambient_ratio);
    } else {
      printf ("Error\n");
    }
  }
  {
    t_optional_material m = parse_ambient("A 0.5 255,255,255,255");
    if (m.error == false) {
      printf ("%f %f %f\n", m.material.ambient_light_color.red,
                            m.material.ambient_light_color.green,
                            m.material.ambient_light_color.blue);
      printf("ratio %f\n", m.material.ambient_ratio);
    } else {
      printf ("Error\n");
    }
  }

  assert(get_int("1").num == 1);
  assert(get_int("-1").num == -1);
  assert(get_int("50").num == 50);
  assert(get_int("-65645").num == -65645);
  assert(get_int("-65645").error == false);
  assert(get_int("-65645a").error == true);
  assert(get_int(NULL).error == true);

  if (get_double("1.1").error == false)
    printf("1.1 %f\n", get_double("1.1").num);
  else
    printf("Error\n");
  if (get_double("-1.1").error == false)
    printf("-1.1 %f\n", get_double("-1.1").num);
  else
    printf("Error\n");
  if (get_double("-50.0").error == false)
    printf("-50.0 %f\n", get_double("-50.0").num);
  else
    printf("Error\n");
  if (get_double("60").error == false)
    printf("60 %f\n", get_double("60").num);
  else
    printf("Error\n");
  if (get_double("0").error == false)
    printf("0 %f\n", get_double("0").num);
  else
    printf("Error\n");
  if (get_double("0a").error == false)
    printf("0a %f\n", get_double("0a").num);
  else
    printf("Error\n");
  if (get_double("a0").error == false)
    printf("a0 %f\n", get_double("a0").num);
  else
    printf("Error\n");

  print_tupil("test", get_position("-50.0,0,20").point);
  print_tupil("test", get_position("-40.0,50.0,0.0").point);
  assert(get_position("10,10,10,").error);
  assert(get_position(",10,10,10").error);
  assert(get_position("10,10,10,10").error);
  t_optional_camera cam = parse_camera("C -50.0,0,20 0,0,1 70", pair(600, 600));
  assert(cam.error == false);
  printf ("cam %f\n", cam.camera.half_height);
  printf ("cam %f\n", cam.camera.half_width);
  printf ("cam %f\n", cam.camera.hsize);
  printf ("cam %f\n", cam.camera.pixel_size);
  printf ("cam %f\n", cam.camera.transform.l1_c1);
  printf ("cam %f\n", cam.camera.vsize);
 
  t_optional_camera cam2 = parse_camera("C 0.0,1.5,-5 0,1,0 60", pair(600, 600));
  assert(cam2.error == false);
  printf ("cam %f\n", cam2.camera.half_height);
  printf ("cam %f\n", cam2.camera.half_width);
  printf ("cam %f\n", cam2.camera.hsize);
  printf ("cam %f\n", cam2.camera.pixel_size);
  printf ("cam %f\n", cam2.camera.transform.l1_c1);
  printf ("cam %f\n", cam2.camera.vsize);
  t_camera ctest = camera(600, 600, M_PI / 3);
  ctest.transform = view_transform(point(0, 1.5, -5),
                               point(0, 1, 0),
                               vector(0, 1, 0));
  printf ("cam %f\n", ctest.half_height);
  printf ("cam %f\n", ctest.half_width);
  printf ("cam %f\n", ctest.hsize);
  printf ("cam %f\n", ctest.pixel_size);
  printf ("cam %f\n", ctest.transform.l1_c1);
  printf ("cam %f\n", ctest.vsize);
  t_optional_light l = parse_light("L -40.0,50.0,0.0 0.6 10,0,255");
  assert(l.error == false);
  print_tupil("light", l.light.position);
  printf ("%f|", l.light.intensity.red);
  printf ("%f|", l.light.intensity.green);
  printf ("%f\n", l.light.intensity.blue);
  system("leaks a.out");
}
