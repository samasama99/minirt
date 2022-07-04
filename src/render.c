#include "main.h"
#include <pthread.h>

static t_thread_data create_thread_data(int y,
                                 t_camera c,
                                 t_world w,
                                 t_image canvas)
{
  return ((t_thread_data){
    .y = y,
    .camera = c,
    .world = w,
    .canvas = canvas
  });
}

static void *render_thread(void *d)
{
  t_thread_data *data = d;
  const int y = data->y;
  const t_camera c = data->camera;
  const t_world w = data->world;
  const t_image canvas = data->canvas;
  size_t x;

  x = 0;
  while (x < c.hsize - 1)
  {
    t_ray r = ray_for_pixel(c, x, y);
    t_rgb c = color_at(w, r);
    put_pixel_to_image(canvas, pair(x, y), c);
    ++x;
  }
  return NULL;
}

void render(t_camera c, t_world w)
{
  const t_image canvas = create_image(pair(c.hsize, c.vsize));
  const long start = time_now();
  t_thread_data *data;
  pthread_t *id;
  size_t y;

  put_black_bar(pair(600, 25), pair(600, 0));
  id  =  malloc(sizeof(t_thread_data) * (int)c.vsize - 1); 
  data = malloc(sizeof(t_thread_data) * (int)c.vsize - 1);
  y = 0;
  while (y < c.vsize - 1)
  {
    data[y] = create_thread_data(y, c, w, canvas);
    pthread_create(&id[y], NULL, render_thread, &data[y]);
    ++y;
  }
  y = 0;
  while (y < c.vsize - 1)
    pthread_join(id[y++], NULL);
  put_image(pair(0, 25), canvas);
  put_string(600, 0,
             ft_strjoin("it took (ms) ",
                        ft_itoa((int)time_now() - start)));
}

// void render(t_camera c, t_world w)
// {
//   t_image canvas = create_image(pair(c.hsize, c.vsize));
//   const long start = time_now();

//   for (int y = 0;y < c.vsize - 1;++y) {
// 	for (int x = 0;x < c.hsize - 1;++x) {
// 	  t_ray r = ray_for_pixel(c, x, y);
// 	  t_rgb c = color_at(w, r);
// 	  put_pixel_to_image(canvas, pair(x, y), c);
// 	}
//   }
//   const long end = time_now() - start;
//   printf ("It took (%ldms %lds)\n", end, end / 1000);
//   put_image(pair(0, 0), canvas);
// }

