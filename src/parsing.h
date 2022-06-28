#include "main.h"

typedef struct {
  t_world w;
  t_camera c;
  t_material ambient;
} t_data;

typedef enum e_line_type {
  e_ambient, e_camera, e_light, e_sphere, e_plane
} t_line_type;

typedef struct s_optional_array {
  char **value;
  size_t size;
  bool error;
} t_optional_array;

typedef struct s_optional_string {
  char *value;
  size_t size;
  bool is_null;
} t_optional_string;

typedef struct s_optional_material {
  t_material value;
  bool error;
} t_optional_material;


typedef struct s_optional_transform {
  t_transform value;
  bool error;
} t_optional_transform;

typedef struct s_optional_camera {
  t_camera value;
  bool error;
} t_optional_camera;

typedef struct s_optional_point {
  t_point value;
  bool error;
} t_optional_point;

typedef struct s_optional_int {
  int value;
  bool error;
} t_optional_int;

typedef struct s_optional_rgb {
  t_rgb value;
  bool error;
} t_optional_rgb;

typedef struct s_optional_double {
  double value;
  bool error;
} t_optional_double;

typedef struct s_optional_light {
  t_light value;
  bool error;
} t_optional_light;

typedef struct s_optional_plane {
  t_plane value;
  bool error;
} t_optional_plane;


typedef struct s_optional_sphere {
  t_sphere value;
  bool error;
} t_optional_sphere;

typedef struct s_optional_shape {
  t_shape value;
  bool error;
} t_optional_shape;

int count_char(const char *str, const char c);
size_t array_len(char **array);
bool ft_isnumber(const char *num);
size_t int_len(int num);
void ft_exit(t_optional_string err, int err_status);
void correct_ambient(t_world w, t_material ambient);

t_optional_string get_string(char *target);
t_optional_int get_digit(const char *d);
t_optional_double get_ratio(const char *target);
t_optional_double get_color_ratio(const char *target);
t_optional_int get_int(const char *target);
t_optional_double get_double(const char *target);
t_optional_rgb get_rgb(const char *target);
t_optional_point get_position(const char *target);
t_optional_double get_fov(const char *target);
t_optional_array get_array(const char *line, const char delimiter);
t_optional_int get_type(char *target);

t_optional_material parse_ambient(const t_optional_array elems);
t_optional_camera parse_camera(const t_optional_array elems, t_res res);
t_optional_light parse_light(const t_optional_array elems);
t_optional_plane parse_plane(const t_optional_array elems);
t_optional_sphere parse_sphere(const t_optional_array elems);
t_optional_shape parse_shape(const t_optional_array elems, t_line_type type);

t_optional_string get_line(int fd);
t_camera is_valid_camera(t_optional_array array, t_res res);
t_light is_valid_light(t_optional_array array);
t_material is_valid_ambient(t_optional_array array);
t_shape is_valid_shape(t_optional_array array, t_line_type type);

void parse(t_data *data, int fd, t_res res);
