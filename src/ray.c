#include "main.h"

t_pos ray_position(t_ray r, double t)
{
  return vec_sum(r.origin, vec_scalar(r.direction, t));
}

t_sphere make_sphere(t_pos origin, double radius)
{
  static int id;
  t_sphere sphere;

  sphere = (t_sphere) {
    id,
    origin,
    radius,
    identity(),
  };
  ++id;
  return sphere;
}

t_sphere sphere()
{
  return make_sphere((t_pos){0, 0}, 1);
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
        return ((t_hit) {{{.t = root, sp}, {.t = root, sp}}, 1});
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

// function normal_at(sphere, world_point)
// object_point ← inverse(sphere.transform) * world_point 
// object_normal ← object_point - point(0, 0, 0)
// world_normal ← transpose(inverse(sphere.transform)) * object_normal 
// world_normal.w ← 0
// return normalize(world_normal)
// end function
