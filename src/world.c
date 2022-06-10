#include "main.h"

t_world world()
{
  return ((t_world){
    .amount_of_spheres = 0,
    .amount_of_lights = 0,
  });
}

t_world add_sphere(const t_world w, const t_sphere s)
{
  t_world new_w;

  // panic(w.amount_of_spheres == 1024,
  //       "reached the maximum amount of spheres",
  //       __func__,__FILE__,__LINE__);
  new_w = world();
  new_w = w;
  new_w.spheres[w.amount_of_spheres] = s;
  ++new_w.amount_of_spheres;
  return new_w;
}

t_world add_light(const t_world w, const t_light l)
{
  t_world new_w;

  panic(w.amount_of_spheres == 1024,
        "reached the maximum amount of lights",
        __func__,__FILE__,__LINE__);
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

  w = world();
  s1 = sphere();
  s1.material.color = color(0.8, 1.0, 0.6);
  s1.material.diffuse = 0.7;
  s1.material.specular = 0.2;
  s2 = sphere();
  s2.t = scaling(0.5, 0.5, 0.5);
  w = add_sphere(w, s1);
  w = add_sphere(w, s2);
  w = add_light(w, light);
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

void sort(t_intersection inters[], int size)
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
  while (i < w.amount_of_spheres)
  {
    tmp = intersect_sphere(w.spheres[i], r); 
    if (tmp.count != 0)
    {
      h.intersection[h.count] = tmp.intersection[0];
      h.intersection[h.count + 1] = tmp.intersection[1];
      h.count += tmp.count;
    }
    ++i;
  }
  if (h.count > 2)
    sort(h.intersection, h.count);
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
