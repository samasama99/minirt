#include "main.h"

void render(t_camera c, t_world w)
{
  t_image canvas = create_image(pair(c.hsize, c.vsize));
  const long start = time_now();

  for (int y = 0;y < c.vsize - 1;++y) {
    for (int x = 0;x < c.hsize - 1;++x) {
      t_ray r = ray_for_pixel(c, x, y);
      t_rgb c = color_at(w, r);
      put_pixel_to_image(canvas, pair(x, y), c);
    }
  }
  const long end = time_now() - start;
  printf ("It took (%ldms %lds)\n", end, end / 1000);
  put_image(pair(0, 0), canvas);
}
