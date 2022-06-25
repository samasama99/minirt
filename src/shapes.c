#include "main.h"



// t_shape sphere_shape(t_sphere s)
// {
//   t_shape ss;

//   ss.sphere = s;
//   return ss;
// }

// t_shape plane_shape(t_plane s)
// {
//   t_shape ss;

//   ss.plane = s;
//   return ss;
// }

t_shape testing_shape()
{
  return (t_shape) {
    .super = (t_super_shape) {
      .t = identity(),
      .type = SuperShape,
      .material = material(),
      .id = -2,
    },
  };
}
