#include "src/parsing.h"
#include <assert.h>

int main() {
  init(pair(2048, 1024), "test");
  t_optional_image test = parse_image_path("./textures/earth_col.xpm");
  assert(test.error == false);
  printf("%d %d\n", test.value.res.width, test.value.res.height);
  put_image(pair(0, 0), test.value);
  start();
}
