#include "vector.h"
#include <math.h>


t_matrix4 translation(double x, double y, double z) {
  return (t_matrix4) {
    1, 0, 0, x,
    0, 1, 0, y,
    0, 0, 1, z,
    0, 0, 0, 1,
  };
};

t_matrix4 scaling(double x, double y, double z) {
  return (t_matrix4) {
    x, 0, 0, 0,
    0, y, 0, 0,
    0, 0, z, 0,
    0, 0, 0, 1,
  };
};

t_rad radians(t_deg deg) {
  return (deg / 180) * M_PI;
}

t_matrix4 rotation_x(t_rad deg) {
  return (t_matrix4) {
    1, 0, 0, 0,
    0, cos(deg), -sin(deg), 0,
    0, sin(deg), cos(deg), 0,
    0, 0, 0, 1,
  };
}

t_matrix4 rotation_y(t_rad deg) {
  return (t_matrix4) {
    cos(deg), 0, sin(deg), 0,
    0, 1, 0, 0,
    -sin(deg), 0, cos(deg), 0,
    0, 0, 0, 1,
  };
}

t_matrix4 rotation_z(t_rad deg) {
  return (t_matrix4) {
    cos(deg), -sin(deg), 0, 0,
    sin(deg), cos(deg), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };
}

t_matrix4 shearing(t_pos x, t_pos y, t_pos z) {
return (t_matrix4) {
    1, y.x, z.x, 0,
    x.y, 1, z.y, 0,
    x.z, y.z, 1, 0,
    0, 0, 0, 1,
  };
}

t_matrix4 transform(t_matrix4 a, t_matrix4 b, t_matrix4 c) {
  const t_transform f = mat4_mult(b, a);
  return mat4_mult(c, f);
}

t_matrix4 identity() {
  return (t_matrix4) {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };
}







