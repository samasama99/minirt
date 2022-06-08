#include "main.h"
#include <stdio.h>

t_ray ray(t_pos origin, t_vec direction)
{
  return ((t_ray){
    .origin = origin,
    .direction = direction,
  });
}

t_pos ray_position(t_ray r, double t)
{
  return vec_sum(r.origin, vec_scalar(r.direction, t));
}

t_sphere make_sphere(t_pos origin, double radius)
{
  static int id;
  const t_sphere sphere = {
    ++id,
    origin,
    radius,
    identity(),
    material(),
  };

  return sphere;
}

t_sphere sphere()
{
  return make_sphere((t_pos){0, 0, 0, 1}, 1);
}

// e is the origin of the ray and d is the direction
// p(t) = e + td
// (p - c).(p - c) - R^2 = 0
// (d.d)t^2 + 2d.(e - c)t + (e - c).(e - c) - R^2 = 0
// discriminant  = B^2 - 4AC if there is a solution then discriminant >= 0
bool is_hit(const t_sphere sp, const t_ray r) {
    const t_ray ray = ray_transform(r, mat4_inverse(sp.t));
    t_vec e_c = vec_sub(ray.origin, sp.center); // e - c
    double a = vec_dot_product(ray.direction, ray.direction);
    double b = 2.0 * vec_dot_product(e_c, ray.direction);
    double c = vec_dot_product(e_c, e_c) - sp.radius * sp.radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant  < 0)
        return false;
    return true;
}

t_hit intersect_sphere(const t_sphere sp, const t_ray r) {
    const t_ray ray = ray_transform(r, mat4_inverse(sp.t)); 
    t_vec e_c = vec_sub(ray.origin, sp.center); // e - c
    double a = vec_dot_product(ray.direction, ray.direction);
    double b = 2.0 * vec_dot_product(e_c, ray.direction);
    double c = vec_dot_product(e_c, e_c) - sp.radius * sp.radius;
    double discriminant = b * b - 4 * a * c;
    if (discriminant  < 0)
        return (t_hit) {(t_intersection) {.t = -1, sp}, .count = 0};
    if (discriminant == 0)
    {
        const double root = (-1 * b) / (2 * a);
        return ((t_hit) {{{.t = root, sp}, {.t = root, sp}}, 2});
    }
    const double sqrt_dis =  sqrt(discriminant);
    const double root1 = ((-1 * b) - sqrt_dis) / (2 * a);
    const double root2 = ((-1 * b) + sqrt_dis) / (2 * a);
    return ((t_hit) {{{.t = root1, sp}, {.t = root2, sp}}, 2});
}

t_intersection hit(t_hit h)
{
  if (h.intersection[0].t >= 0 && h.intersection[1].t >=0
      && h.count > 0)
  {
    if (h.intersection[0].t <= h.intersection[1].t)
      return h.intersection[0];
    return h.intersection[1];
  }
  if (h.intersection[0].t >= 0 && h.count > 0)
    return h.intersection[0];
  if (h.intersection[1].t >= 0 && h.count > 0)
    return h.intersection[1];
  return (t_intersection) {-1, (t_sphere) {.id = -1}};
}

t_ray ray_transform(t_ray ray, t_matrix4 m)
{
  return (t_ray) {
        .origin = apply_transformation(m, ray.origin),
        .direction = apply_transformation(m, ray.direction),
  };
};

t_vec normal_at(t_sphere s, t_pos world_point)
{
  const t_pos object_point = apply_transformation(mat4_inverse(s.t), world_point);
  const t_vec object_normal =  vec_normalize(vec_sub(object_point, s.center), sqrt);
  t_vec world_normal = apply_transformation(mat4_transpose(mat4_inverse(s.t)), object_normal);
  world_normal.w = 0;
  return vec_normalize(world_normal, sqrt);
}

t_vec reflect(t_vec in, t_vec norm)
{
  return vec_sub(
    in,
    vec_scalar(norm, 2 * vec_dot_product(in, norm))
  );
}

t_light point_light(t_pos position, t_rgb intensity)
{
  return (t_light) {
    position,
    intensity,
  };
}

t_material material()
{
  return ((t_material){
    .color = color(1, 1, 1),
    .ambient = 0.1,
    .diffuse = 0.9,
    .specular = 0.9,
    .shininess = 200.0,
  });
}


t_rgb lighting(t_material m, t_light l, t_pos p, t_vec eyev, t_vec normalv)
{
  t_rgb diffuse;
  t_rgb specular;
  t_vec reflectv;
  double reflect_dot_eye;
  double factor;

  const t_rgb effective_color = rgb_hadamard_product(m.color, l.intensity);
  const t_vec lightv = vec_normalize(vec_sub(l.position, p), sqrt);
  const t_rgb ambient = rgb_scalar(effective_color, m.ambient);
  const double light_dot_normal = vec_dot_product(lightv, normalv);
  if (light_dot_normal < 0) {
   diffuse = (t_rgb){0 ,0 ,0}; 
   specular = (t_rgb){0 ,0 ,0}; 
  } else {
    diffuse = rgb_scalar(effective_color, m.diffuse * light_dot_normal);
    reflectv = reflect(vec_opose(lightv), normalv);
    reflect_dot_eye = vec_dot_product(reflectv, eyev);
    if (reflect_dot_eye <= 0) {
      specular = (t_rgb) {0, 0, 0};
    } else {
      factor = pow(reflect_dot_eye, m.shininess);
      specular =  rgb_scalar(l.intensity, m.specular * factor);
    }
  }
  return rgb_sum(ambient, rgb_sum(diffuse, specular));
}

t_comp prepare_computations(t_intersection i, t_ray r)
{
    t_comp comp;

    comp.t = i.t;
    comp.object.sphere = i.sphere;
    comp.point = ray_position(r, comp.t);
    comp.eyev = vec_opose(r.direction);
    comp.normalv = normal_at(comp.object.sphere, comp.point);
    if (vec_dot_product(comp.normalv, comp.eyev) < 0)
    {
      comp.inside = true;
      comp.normalv = vec_opose(comp.normalv);
    } 
    else
      comp.inside = false;
    return comp;
};

t_rgb shade_hit(t_world w, t_comp comps)
{
  return lighting(
    comps.object.sphere.material,
    w.lights[0],
    comps.point,
    comps.eyev,
    comps.normalv
  );
}
// function normal_at(sphere, world_point)
// object_point ← inverse(sphere.transform) * world_point 
// object_normal ← object_point - point(0, 0, 0)
// world_normal ← transpose(inverse(sphere.transform)) * object_normal 
// world_normal.w ← 0
// return normalize(world_normal)
// end function
  // printf ("m color %f %f %f\n", m.color.red, m.color.green, m.color.blue);
  // printf("light intensity %f %f %f\nlight position %f %f %f\n", l.intensity.red, l.intensity.red, l.intensity.red,l.position.x, l.position.y, l.position.z);
  // printf("p %f %f %f\n", p.x, p.y, p.z);
  // printf("eye %f %f %f\n", eyev.x, eyev.y, eyev.z);
  // printf("normal %f %f %f\n", normalv.x, normalv.y, normalv.z);
  // printf ("light_dot_normal %f\n", light_dot_normal);
