#include "main.h"

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

typedef struct s_optional_char {
  char c;
  bool error;
} t_optional_char;

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

typedef struct s_optional_plane {
  t_plane plane;
  bool error;
} t_optional_plane;


typedef struct s_optional_sphere {
  t_sphere sphere;
  bool error;
} t_optional_sphere;

int count_char(const char *str, const char c);
size_t array_len(char **array);
bool ft_isnumber(const char *num);
size_t int_len(int num);

t_optional_char get_type(const char *target);
t_optional_int get_digit(const char *d);
t_optional_double get_ratio(const char *target);
t_optional_double get_color_ratio(const char *target);
t_optional_int get_int(const char *target);
t_optional_double get_double(const char *target);
t_optional_rgb get_rgb(const char *target);
t_optional_material parse_ambient(const char *line);
t_optional_point get_position(const char *target);
t_optional_double get_fov(const char *target);
t_optional_camera parse_camera(const char *line, t_res res);
t_optional_light parse_light(const char *line);
