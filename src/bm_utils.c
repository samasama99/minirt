#include "main.h" 

t_rad teta_sphere(t_sphere sp, t_point p)
{
  return (acos(p.y / sp.radius));
}

t_rad phi_sphere(t_point p)
{
  return atan2(p.z, p.x);
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

  return (t_fpair) {{u * res.width + 0.5, v * res.height + 0.5}};
}

double linear_interpolation(double i, double j, t_image img)
{
    int k = i;
    int l = j;
    return  ((1 - (i - k)) * (1 - (j - l)) * get_color_at(img, k, l)
                      + (1 - (i - k)) * (j - l) * get_color_at(img, k, l + 1)
                      + (i - k) * (1 - (j - l)) * get_color_at(img, k + 1, l)
                      + (i - k) * (j - l) * get_color_at(img, k + 1, l + 1));
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
  double i = ij.i;
  double j = ij.j;

  return ((linear_interpolation(i + 1, j, img) - linear_interpolation(i, j, img) / 2.0));
}

double calc_dv_sphere(t_image img, t_sphere sp, t_point p)
{
  const t_fpair ij = ij_of_map(img.res, uv_of_sphere(sp, p));
  double i = ij.i;
  double j = ij.j;

  return (linear_interpolation(i, j + 1, img) - linear_interpolation(i, j, img) / 2.0);
}

t_vec bm_normal_at(t_sphere sp, t_point p, t_image img)
{
  const t_vec pu = pu_sphere(p);
  const t_vec pv = pv_sphere(p, sp);
  const double du = calc_du_sphere(img, sp, p);
  const double dv = calc_dv_sphere(img, sp, p);

  return ((sub((cross(pv, pu)), 
              (sum(scalar(pu, du), scalar(pv, dv))))));
}

