#include "main.h"

t_world set_amount_of_shapes(size_t amount)
{
  return ((t_world){
	.amount_of_shapes = 0,
	.shapes = malloc(sizeof(t_shape) * amount),
  });
}

t_world add_shape(const t_world w, const t_shape s) {
  t_world new_w;

  new_w = w;
  new_w.shapes[w.amount_of_shapes] = (t_shape)s;
  ++new_w.amount_of_shapes;
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

