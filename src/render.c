#include "main.h"

// t_image render(t_camera c, t_world w)
// {
//   t_image canvas = create_image(pair(c.hsize, c.vsize));

//   for (int y = 0;y < c.vsize - 1;++y) {
//     for (int x = 0;x < c.hsize - 1;++x) {
//       t_ray r = ray_for_pixel(c, x, y);
//       t_rgb c = color_at(w, r);
//       put_pixel_to_image(canvas, pair(x, y), c);
//     }
//   }
//   return canvas;
// }

t_image render(t_camera c, t_world w)
{
  t_image canvas = create_image(pair(c.hsize, c.vsize));

  printf ("start of the 'render' function\n"); const long start = time_now();
  for (int y = 0;y < c.vsize - 1;++y) {
      const long start1 = time_now();
    for (int x = 0;x < c.hsize - 1;++x) {
      // const long start0 = time_now();
      t_ray r = ray_for_pixel(c, x, y);
      // printf ("ray_for_pixel : %ldms\n", time_now() - start0);
      // const long start1 = time_now();
      t_rgb c = color_at(w, r);
      // printf ("color_at : %ldms\n", time_now() - start1);
      // const long start2 = time_now();
      put_pixel_to_image(canvas, pair(x, y), c);
      // printf ("put_pixel_to_image : %ldms\n", time_now() - start2);
    }
      printf ("one loop : %ldms\n", time_now() - start1);
  }
  const long end = time_now() - start;
  printf ("end of the 'render' function (%ldms %lds)\n", end, end / 1000);
  put_image(pair(0, 0), canvas);
  return canvas;
}
