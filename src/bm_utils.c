#include "main.h" 



t_rad teta_sphere(t_sphere sp, t_point p)
{
  return (acos(p.y / sp.radius));
}

t_rad phi_sphere(t_point p)
{
  return atan(p.z / p.x);
}

t_uv uv_of_sphere(t_sphere sp, t_point p)
{
  const double phi = phi_sphere(p);
  const double teta = teta_sphere(sp, p);
  const double v = teta / M_PI;
  double u;

  if (is_equal_double(phi, M_PI))
     u = 0;
  else
    u = (-phi + M_PI) / (M_PI * 2);
  return (t_uv) {u, v};
}

t_fpair ij_of_map(t_res res, t_uv uv)
{
  const double u = uv.u;
  const double v = uv.v;

  return (t_fpair) {{u * res.width - 0.5, v * res.height - 0.5}};
}

t_vec pu_sphere(t_point p)
{
  return vector(p.z * 2 * M_PI, 0, -p.x * 2 * M_PI);
}

t_vec pv_sphere(t_point p, t_sphere sp)
{
  const double phi = phi_sphere(p);
  const double teta = teta_sphere(sp, p);

  return vector(p.y * cos(phi) * M_PI,
                -sp.radius * sin(teta) * M_PI,
                p.y * sin(phi) * M_PI);
}

// p.x + (p.y * img.res.x)

double calc_du_sphere(t_image img, t_sphere sp, t_point p)
{
  t_fpair ij = ij_of_map(img.res, uv_of_sphere(sp, p));
  int i = ij.i;
  int j = ij.j;
  return (img.buffer[(i + 1) + (j * img.res.height)] -
          img.buffer[i + (j * img.res.height)]);
}

double calc_dv_sphere(t_image img, t_sphere sp, t_point p)
{
  const t_fpair ij = ij_of_map(img.res, uv_of_sphere(sp, p));
  const int i = ij.i;
  const int j = ij.j;

  return (img.buffer[i + ((j + 1) * img.res.height)] -
          img.buffer[i + (j * img.res.height)]);
}

t_vec bm_normal_at(t_sphere sp, t_point p, t_image img)
{
  const t_vec pu = pu_sphere(p);
  const t_vec pv = pv_sphere(p, sp);
  const double du = calc_du_sphere(img, sp, p);
  const double dv = calc_dv_sphere(img, sp, p);

  return (sub(normal_at_sphere(sp, p), 
              (sum(scalar(pu, du), scalar(pv, dv)))));
}


	// t_image_ptr	*img;
	// t_res		res;
	// int			*buffer;

