#include "linear_algebra.h"
#include <math.h>


t_matrix4 translation(double x, double y, double z) {
  return (t_matrix4) {{
    1, 0, 0, x,
    0, 1, 0, y,
    0, 0, 1, z,
    0, 0, 0, 1,
  }};
}

t_matrix4 scaling(double x, double y, double z) {
  return (t_matrix4) {{
    x, 0, 0, 0,
    0, y, 0, 0,
    0, 0, z, 0,
    0, 0, 0, 1,
  }};
}

t_rad radians(t_deg deg) {
  return (deg / 180) * M_PI;
}

t_matrix4 rotation_x(t_rad deg) {
  return (t_matrix4) {{
    1, 0, 0, 0,
    0, cos(deg), -sin(deg), 0,
    0, sin(deg), cos(deg), 0,
    0, 0, 0, 1,
  }};
}

t_matrix4 rotation_y(t_rad deg) {
  return (t_matrix4) {{
    cos(deg), 0, sin(deg), 0,
    0, 1, 0, 0,
    -sin(deg), 0, cos(deg), 0,
    0, 0, 0, 1,
  }};
}

t_matrix4 rotation_z(t_rad deg) {
  return (t_matrix4) {{
    cos(deg), -sin(deg), 0, 0,
    sin(deg), cos(deg), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  }};
}

// t_matrix4 shearing(t_point x, t_point y, t_point z) {
// return (t_matrix4) {{
//     1, y.x, z.x, 0,
//     x.y, 1, z.y, 0,
//     x.z, y.z, 1, 0,
//     0, 0, 0, 1,
//   }};
// }

t_matrix4 transform(t_matrix4 a, t_matrix4 b, t_matrix4 c) {
  const t_transform f = mat4_mult(b, a);
  return mat4_mult(c, f);
}

t_matrix4 identity() {
  return (t_matrix4) {{
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  }};
}

t_transform view_transform(t_point from, t_point to, t_vec up)
{
  const t_vec forward = normalize(sub(to, from));
  const t_vec nup = normalize(up);
  const t_vec left = cross(forward, nup);
  const t_vec true_up = cross(left, forward);
  const t_transform orientation = {{
    left.x, left.y, left.z, 0,
    true_up.x, true_up.y, true_up.z, 0,
    -forward.x, -forward.y, -forward.z, 0,
    0, 0, 0, 1,
  }};

  return mat4_mult(orientation, translation(-from.x, -from.y, -from.z));
}

inline t_point apply(t_transform mat, t_point p) {
  return ((t_point){{
      p.x * mat.l1_c1 + p.y * mat.l1_c2 + p.z * mat.l1_c3 + p.w * mat.l1_c4,
      p.x * mat.l2_c1 + p.y * mat.l2_c2 + p.z * mat.l2_c3 + p.w * mat.l2_c4,
      p.x * mat.l3_c1 + p.y * mat.l3_c2 + p.z * mat.l3_c3 + p.w * mat.l3_c4,
      p.x * mat.l4_c1 + p.y * mat.l4_c2 + p.z * mat.l4_c3 + p.w * mat.l4_c4,
  }});
}

