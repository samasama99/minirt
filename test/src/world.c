#include "main.h"

t_world add_shape(const t_world w, const t_shape s) {
  t_world new_w;
  int i;

  new_w = w;
  new_w.shapes = ft_malloc(sizeof(t_shape) * (w.amount_of_shapes + 1));
  new_w.amount_of_shapes = w.amount_of_shapes + 1;
  i = 0;
  while (i < w.amount_of_shapes) {
    new_w.shapes[i] = w.shapes[i];
    ++i;
  }
  new_w.shapes[w.amount_of_shapes] = s;
  return new_w;
}

t_hit intersect_world(t_world w, t_ray r) {
  t_intersection  min;
  t_intersection  tmp;
  int i;

  i = 1;
  min = hit(intersect(w.shapes[0], r));
  while (i < w.amount_of_shapes) {
	tmp = hit(intersect(w.shapes[i], r));
	if ((tmp.t > 0 && tmp.t < min.t) || min.t < 0)
	{
	  min = tmp;
	}
	++i;
  }
  if (min.t < 0)
	return no_intersection();
  return (t_hit){{min}, 1};
}

