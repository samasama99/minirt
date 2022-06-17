#include "main.h"

t_world world()
{
  return ((t_world){
    .amount_of_shapes = 0,
    .amount_of_lights = 0,
  });
}

t_world add_shape(const t_world w, const t_shape s)
{
  t_world new_w;

  // panic(w.amount_of_spheres == 1024,
  //       "reached the maximum amount of spheres",
  //       __func__,__FILE__,__LINE__);
  new_w = w;
  new_w.shapes[w.amount_of_shapes] = (t_shape)s;
  ++new_w.amount_of_shapes;
  return new_w;
}

t_world add_light(const t_world w, const t_light l)
{
  t_world new_w;

  // panic(w.amount_of_spheres == 1024,
  //       "reached the maximum amount of lights",
  //       __func__,__FILE__,__LINE__);
  new_w = w;
  new_w.lights[w.amount_of_lights] = l;
  ++new_w.amount_of_lights;
  return new_w;
}

t_world default_world()
{
  t_world w;
  t_sphere s1;
  t_sphere s2;
  const t_light light = point_light(
      point(-10, 10, -10),
      color(1, 1, 1)
  );

  // w = world();
  w.amount_of_lights = 0;
  w.amount_of_shapes = 0;
  s1 = sphere();
  s1.material.color = color(0.8, 1.0, 0.6);
  s1.material.diffuse = 0.7;
  s1.material.specular = 0.2;
  s2 = sphere();
  s2.t = scaling(0.5, 0.5, 0.5);
  w = add_light(w, light);
  w = add_shape(w, (t_shape)s1);
  w = add_shape(w, (t_shape)s2);
  return w;
}

// double min_inters(const t_intersection inters[], int size)
// {
//   double min;
//   int i;

//   i = 0;
//   min = inters[0].t;
//   while (i < size)
//   {
//     if (min > inters[i].t)
//       min = inters[i].t;
//     i++;
//   }
//   return min;
// }

static void sort(t_intersection inters[], int size)
{
  int i;
  int j;
  int index;
  t_intersection min_inter;
  t_intersection tmp;

  i = 0;
  j = 0;
  while (j < size)
  {
    min_inter = inters[j];
    index = j;
    while (i < size)
    {
      if (min_inter.t > inters[i].t)
      {
        min_inter = inters[i];
        index = i;
      }
      i++;
    }
    tmp = inters[j];
    inters[j] = min_inter;
    inters[index] = tmp;
    ++j;
    i = j;
  }
}

t_hit intersect_world(t_world w, t_ray r)
{
  t_hit h;
  t_hit tmp;
  int i;

  i = 0;
  h.count = 0;
  while (i < w.amount_of_shapes)
  {
    tmp = intersect(w.shapes[i], r); 
    if (tmp.count != 0)
    {
      h.intersections[h.count] = tmp.intersections[0];
      if (tmp.count == 2) 
        h.intersections[h.count + 1] = tmp.intersections[1];
      h.count += tmp.count;
    }
    ++i;
  }
  if (h.count > 2)
    sort(h.intersections, h.count);
  if (h.count == 0)
    return (t_hit) {{intersection(-1, (t_shape) {.type = Error})},
                    .count =  0};
  return h;
}

t_rgb color_at(t_world w, t_ray r)
{
  const t_hit h = intersect_world(w, r);
  const t_intersection i = hit(h);
  
  if (i.t < 0)
    return color(0, 0 ,0);
  t_comp comp = prepare_computations(i, r);
  return (shade_hit(w, comp));
}

bool is_shadowed(t_world w, t_point p)
{
  const t_vec v = sub(w.lights[0].position, p);
  const double d = magnitude(v);
  const t_vec direction = normalize(v);
  const t_ray r = ray(p, direction);
  const t_hit i = intersect_world(w, r);
  const t_intersection h = hit(i);

  if (h.t >= 0 && h.t < d) {
    return true;
  }
  return false;
}
