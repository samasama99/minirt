#include "parsing.h"

t_optional_image parse_image_path(const char *path) {
  const t_optional_image error = {.error = true};
  char *dot;

  if (path == NULL)
    return error;
  dot = strrchr(path, '.');
  if (is_equal_str(dot, ".xpm") == false)
    return error;
  return (t_optional_image){
      .value = load_image(path),
      .error = false,
  };
}
