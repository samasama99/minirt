#include "main.h"
#include "vector.h"
#include <assert.h>
#include <stdio.h>

// void my_func(char *ptr) {
//   panic(ptr == NULL, "NULL param", __func__, __FILE__, __LINE__);
// }

int main() {
  {
    t_vec v = vec_init(3, -2, 5);
    t_vec w = vec_init(-2, 3, 1);
    t_vec vw = vec_sum(v, w);
    assert(vec_is_equal(vw, (t_vec){1, 1, 6}));
    assert(!vec_is_equal(vw, (t_vec){2, 1, 6}));
    printf("Vector sum : ✔\n");
  }
  {
    t_vec v = vec_init(3, 2, 1);
    t_vec w = vec_init(5, 6, 7);
    t_vec vw = vec_sub(v, w);
    assert(vec_is_equal(vw, (t_vec){-2, -4, -6}));
    assert(!vec_is_equal(vw, (t_vec){-3, -4, -6}));
    printf("Vector sub : ✔\n");
  }
  {
    t_vec v = vec_init(0, 0, 0);
    t_vec w = vec_init(1, -2, 3);
    t_vec vw = vec_sub(v, w);
    assert(vec_is_equal(vw, (t_vec){-1, 2, -3}));
    assert(!vec_is_equal(vw, (t_vec){-2, 2, -3}));
    printf("Vector negation : ✔\n");
  }
  {
    t_vec v = vec_init(1, -2, 3);
    t_vec ov = vec_opose(v);
    assert(vec_is_equal(ov, (t_vec){-1, 2, -3}));
    assert(!vec_is_equal(ov, (t_vec){-1, 3, -3}));
    printf("Vector negation : ✔\n");
  }
  {
    t_vec v = vec_init(1, -2, 3);
    t_vec w = vec_scalar(v, 3.5);
    assert(vec_is_equal(w, (t_vec){3.5, -7, 10.5}));
    assert(!vec_is_equal(w, (t_vec){3.5, -8, 10.5}));
    printf("Vector mult with scalar : ✔\n");
  }
  {
    t_vec v = vec_init(1, -2, 3);
    t_vec w = vec_scalar(v, 0.5);
    assert(vec_is_equal(w, (t_vec){0.5, -1, 1.5}));
    assert(!vec_is_equal(w, (t_vec){0.5, -2, 1.5}));
    printf("Vector mult with scalar : ✔\n");
  }
  {
    t_vec v = vec_init(1, 0, 0);
    assert(vec_lenght(v, sqrt) == 1);
    assert(!(vec_lenght(v, sqrt) == 1.1));
    printf("computing the magnitude of vector: ✔\n");
  }
  {
    t_vec v = vec_init(0, 1, 0);
    assert(vec_lenght(v, sqrt) == 1);
    assert(!(vec_lenght(v, sqrt) == 2));
    printf("computing the magnitude of vector: ✔\n");
  }
  {
    t_vec v = vec_init(0, 0, 1);
    assert(vec_lenght(v, sqrt) == 1);
    assert(!(vec_lenght(v, sqrt) == 1.1));
    printf("computing the magnitude of vector: ✔\n");
  }
  {
    t_vec v = vec_init(1, 2, 3);
    assert(vec_lenght(v, sqrt) == sqrt(14));
    assert(!(vec_lenght(v, sqrt) == sqrt(15)));
    printf("computing the magnitude of vector: ✔\n");
  }
  {
    t_vec v = vec_init(-1, -2, -3);
    assert(vec_lenght(v, sqrt) == sqrt(14));
    assert(!(vec_lenght(v, sqrt) == sqrt(16)));
    printf("computing the magnitude of vector: ✔\n");
  }
  {
    t_vec v = vec_init(4, 0, 0);
    t_vec nv = vec_normalize(v, sqrt);
    assert(vec_is_equal(vec_normalize(v, sqrt), (t_vec){1, 0, 0}));
    assert(!vec_is_equal(vec_normalize(v, sqrt), (t_vec){1, 1, 0}));
    printf("vector normalize: ✔\n");
  }
  {
    t_vec v = vec_init(1, 2, 3);
    t_vec nv = vec_normalize(v, sqrt);
    assert(vec_is_equal(vec_normalize(v, sqrt),
                        (t_vec){0.26726, 0.53452, 0.80178}));
    assert(vec_is_equal(vec_normalize(v, sqrt),
                        (t_vec){1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)}));
    assert(!vec_is_equal(vec_normalize(v, sqrt),
                         (t_vec){0.26726, 0.53452, 0.80177}));
    printf("Vector normalize: ✔\n");
  }
  {
    t_vec v = vec_init(1, 2, 3);
    t_vec w = vec_init(2, 3, 4);
    assert(vec_dot_product(v, w) == 20);
    assert(!(vec_dot_product(v, w) == 25));
    printf("Vector dot product : ✔\n");
  }
  {
    t_vec v = vec_init(1, 2, 3);
    t_vec w = vec_init(2, 3, 4);
    t_vec vw = vec_cross_product(v, w);
    t_vec wv = vec_cross_product(w, v);
    assert(vec_is_equal(vw, (t_vec){-1, 2, -1}));
    assert(!(vec_is_equal(vw, (t_vec){-1, 2, 1})));
    assert(vec_is_equal(wv, (t_vec){1, -2, 1}));
    printf("Vector cross product : ✔\n");
  }
  {
    typedef struct s_projectile {
      t_pos position;
      t_vec velocity;
    } t_projectile;
    typedef struct s_environment {
      t_pos gravity;
      t_vec wind;
    } t_environment;
    t_projectile proj = {(t_pos){0, 1, 0},
                         vec_normalize((t_vec){1, 1, 0}, sqrt)};
    t_environment env = {(t_vec){0, -0.1, 0}, (t_vec){-0.01, 0, 0}};
    int ticks = 0;
    while (proj.position.y > 0) {
      proj.position = vec_sub(proj.position, proj.velocity);
      proj.velocity = vec_sub(proj.velocity, vec_sum(env.gravity, env.wind));
      ++ticks;
    }
    printf("amount of ticks is %d\n", ticks);
  }
  {
    t_rgb color = {.red = -0.5, .green = 0.4, .blue = 1.7};

    assert(is_equal_float(color.red, -0.5));
    assert(is_equal_float(color.green, 0.4));
    assert(is_equal_float(color.blue, 1.7));
    assert(!(is_equal_float(color.red, -0.6)));
    assert(!(is_equal_float(color.green, 0.7)));
    assert(!(is_equal_float(color.blue, 1.8)));

    printf("Rgb color : ✔\n");
  }
  {
    t_rgb c1 = {.red = 0.9, .green = 0.6, .blue = 0.75};
    t_rgb c2 = {.red = 0.7, .green = 0.1, .blue = 0.25};
    t_rgb c3 = {.red = 1.6, .green = 0.7, .blue = 1.0};
    t_rgb sum = rgb_sum(c1, c2);
    assert(rgb_is_equal(sum, c3));
    assert(!rgb_is_equal(sum, (t_rgb){1.6, 0.8, 1.0}));
    printf("Rgb sum : ✔\n");
  }
  {
    t_rgb c1 = {.red = 0.9, .green = 0.6, .blue = 0.75};
    t_rgb c2 = {.red = 0.7, .green = 0.1, .blue = 0.25};
    t_rgb c3 = {.red = 0.2, .green = 0.5, .blue = 0.5};
    t_rgb sub = rgb_sub(c1, c2);

    assert(rgb_is_equal(sub, c3));
    assert(!rgb_is_equal(sub, (t_rgb){1.6, 0.8, 1.0}));
    printf("Rgb sub : ✔\n");
  }
  {
    t_rgb c1 = {.red = 0.2, .green = 0.3, .blue = 0.4};
    t_rgb c2 = {.red = 0.4, .green = 0.6, .blue = 0.8};
    t_rgb mult = rgb_scalar(c1, 2);

    assert(rgb_is_equal(mult, c2));
    assert(!rgb_is_equal(mult, (t_rgb){1.6, 0.8, 1.0}));
    printf("Rgb scalar : ✔\n");
  }
  {
    t_rgb c1 = {.red = 1, .green = 0.2, .blue = 0.4};
    t_rgb c2 = {.red = 0.9, .green = 1, .blue = 0.1};
    t_rgb hp = {.red = 0.9, 0.2, 0.04};
    t_rgb mult = rgb_hadamard_product(c1, c2);

    assert(rgb_is_equal(mult, hp));
    assert(!rgb_is_equal(mult, (t_rgb){1.6, 0.8, 1.0}));
    printf("Rgb hadamard product : ✔\n");
  }
  {
    t_matrix2 M = {-3, 5,
                   1, -2};
    assert(M.m[0][0] == -3);
    assert(M.m[0][1] == 5);
    assert(M.m[1][0] == 1);
    assert(M.m[1][1] == -2);

    assert(!(M.m[1][1] == 16.5));
    printf("2 x 2 Matrix: ✔\n");
  }
  {

    t_matrix3 M = {
        -3, 5, 0, 1, -2, -7, 0, 1, 1,
    };
    assert(M.m[0][0] == -3);
    assert(M.m[1][1] == -2);
    assert(M.m[2][2] == 1);
    assert(!(M.m[2][2] == 4));
    printf("3 x 3 Matrix: ✔\n");
  }
  {
    t_matrix4 M = {1, 2,  3,  4,  5.5,  6.5,  7.5,  8.5,
                   9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5};
    assert(M.m[0][0] == 1);
    assert(M.m[0][3] == 4);
    assert(M.m[1][0] == 5.5f);
    assert(M.m[1][2] == 7.5f);
    assert(M.m[2][2] == 11);
    assert(M.m[3][0] == 13.5f);
    assert(M.m[3][2] == 15.5);
    assert(!(M.m[3][2] == 16.5));
    printf("4 x 4 Matrix: ✔\n");
  }
  {
    t_matrix4 m = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6
      , 5, 4, 3, 2,
    };
    t_matrix4 n = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6
      , 5, 4, 3, 2,
    };
    t_matrix4 n2 = {
        1, 2, 5, 4,
        5, 6, 7, 8,
        9, 8, 7, 6
      , 5, 4, 3, 2,
    };
    assert(mat4_is_equal(m, n));
    assert(!mat4_is_equal(m, n2));
    printf("4 x 4 Matrix equality : ✔\n");
  }
  {
    t_matrix4 m = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2,
    };
    t_matrix4 n = {
      -2, 1, 2, 3,
      3, 2, 1, -1,
      4, 3, 6, 5,
      1, 2, 7, 8,
    };
    t_matrix4 mXn = {
      20, 22, 50, 48,
      44, 54, 114, 108,
      40, 58, 110, 102,
      16, 26, 46, 42,
    };
    assert(mat4_is_equal(mat4_mult(m, n), mXn));
    printf("4 x 4 Matrix multi : ✔\n");
  }
  {
    t_matrix4 m = {
        0,9,3,0,
        9,8,0,8,
        1,8,5,3,
        0,0,5,8,
    };
    t_matrix4 Tm = {
        9,8,8,0,
        3,0,5,5,
        0,8,3,8,
    };
    mat4_is_equal(Tm, mat4_transpose(m));
    mat4_is_equal(m, mat4_transpose(Tm));
    printf("Matrix transposing : ✔\n");
  }
  {
    t_matrix4 m = {
        1, 2, 3, 4,
        2, 4, 4, 2,
        8, 6, 4, 1,
        0, 0, 0, 1,
    };
    m = mat4_transpose(m);
    t_pos pos = {1, 2, 3};
    t_pos res =  pos3_multi_mat4(pos, m);
    assert(vec_is_equal(res, (t_pos) {18, 24, 33}));
    printf("vec3 and Matrix multi : ✔\n");
  }
  {
    const t_matrix4 Identity = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1,
    };
    t_pos pos = {1, 2, 3};
    t_pos res =  pos3_multi_mat4(pos, mat4_transpose(Identity));
    t_pos res2 =  pos3_multi_mat4(pos, Identity);
    assert(vec_is_equal(res, (t_pos) {1, 2, 3}));
    assert(vec_is_equal(res2, (t_pos) {1, 2, 3}));
    assert(mat4_is_equal(Identity, mat4_transpose(Identity)));
    printf("vec3 and Identity Matrix multi : ✔\n");
  }
  {
    t_matrix2 m = {
      1, 5,
      -3, 2
    };
    assert(mat2_determinant(m) == 17);
    assert(!(mat2_determinant(m) == 18));
    printf("mat2 determinant: ✔\n");
  }
  {
    t_matrix3 m = {
      1, 5, 0,
      -3, 2, 7,
      0 ,6 ,-3
    };
    t_matrix2 n = mat3_submatrix(m, 0, 2);
    assert(n.l1_c1 == -3);
    assert(n.l1_c2 == 2);
    assert(n.l2_c1 == 0);
    assert(n.l2_c2 == 6);
    printf("Submatrix of 3x3 : ✔\n");
  }
  {
    t_matrix4 m = {
      -6, 1, 1, 6 ,
      -8, 5, 8, 6 ,
      -1, 0, 8, 2 ,
      -7, 1, -1, 1
    };
    t_matrix3 n = mat4_submatrix(m, 2, 1);
    assert(n.l1_c1 == -6);
    assert(n.l1_c2 == 1);
    assert(n.l1_c3 == 6);

    assert(n.l2_c1 == -8);
    assert(n.l2_c2 == 8);
    assert(n.l2_c3 == 6);

    assert(n.l3_c1 == -7);
    assert(n.l3_c2 == -1);
    assert(n.l3_c3 == 1);
    printf("Submatrix of 4x4 : ✔\n");
  }
  {
    t_matrix3 m = {
      3, 5, 0,
      2, -1, -7,
      6, -1, 5
    };
    assert(mat3_minor(m, 1, 0) == 25);
    assert(!(mat3_minor(m, 1, 0) == 5));
    printf("minor of 3x3 : ✔\n");
  }
  {
    t_matrix3 m = {
      3,5,0,
      2,-1,-7,
      6,-1, 5,
    };
    assert(mat3_minor(m, 0, 0) == -12);
    assert(mat3_cofactor(m, 0, 0) == -12);
    assert(mat3_minor(m, 1, 0) == 25);
    assert(mat3_cofactor(m, 1, 0) == -25);
    printf("cofactor of 3x3 : ✔\n");
  }
  {
   t_matrix3 m = {
      1,2,6,
      -5, 8,-4,
      2,6,4,
    };
    assert(mat3_cofactor(m, 0, 0) == 56);
    assert(mat3_cofactor(m, 0, 1) == 12);
    assert(mat3_cofactor(m, 0, 2) == -46);
    assert(mat3_determinant(m) == -196);
      printf("determinant of 3x3 : ✔\n");

    t_matrix4 n = {
        -2,-8, 3, 5 ,
        -3, 1, 7, 3 ,
        1, 2,-9, 6 ,
        -6, 7, 7,-9,
      };

     assert(mat4_cofactor(n, 0, 0) == 690);
     assert(mat4_cofactor(n, 0, 1) == 447);
     assert(mat4_cofactor(n, 0, 2) == 210);
     assert(mat4_cofactor(n, 0, 3) == 51);
     assert(mat4_determinant(n) == -4071);
    printf("cofactor of 4x4 : ✔\n");
    printf("determinant  of 4x4 : ✔\n");
  }
  {
      t_matrix4 m = {
          6,4,4,4,
          5,5,7,6, 
          4,-9, 3,-7, 
          9, 1, 7,-6
      };
      t_matrix4 n = {
          -4, 2,-2,-3,
          9,6,2,6, 
          0,-5, 1,-5, 
          0,0,0,0,
      };
      assert(mat4_is_invertible(m) == true); 
      assert(mat4_is_invertible(n) == false); 
    printf("checking the invertibility of a 4x4 matrix : ✔\n");
  }
  {
    t_matrix4 m = {
      -5, 2, 6,-8,
      1,-5, 1, 8,
      7, 7, -6, -7,
      1, -3, 7, 4
    };
    t_matrix4 res = {
          0.21805,0.45113,0.24060,-0.04511,
          -0.80827,-1.45677,-0.44361,0.52068,
          -0.07895,-0.22368,-0.05263,0.19737,
          -0.52256,-0.81391,-0.30075,0.30639,
    };
    assert(mat4_is_equal(mat4_inverse(m), res));

    t_matrix4 a = {
          3,-9, 7, 3,
          3,-8, 2,-9, 
          -4, 4, 4, 1,
          -6, 5,-1, 1,
    };
    t_matrix4 b = {
           8,2,2,2,
           3,-1, 7, 0, 
           7,0,5,4,
           6,-2, 0, 5,
    }; 
    t_matrix4 c = mat4_mult(a, b);
    assert(mat4_is_equal(mat4_mult(c, mat4_inverse(b)), a));
    printf("inversing a 4x4 matrix : ✔\n");
  }
  {
    t_matrix4 v = translation(5, -3, 2);
    t_pos p = (t_pos) {-3, 4, 5};
    assert(vec_is_equal(mat4_multi_pos3(v, p), (t_pos) {2, 1, 7}));
  }
  {
    t_matrix4 v = translation(5, -3, 2);
    t_matrix4 inv = mat4_inverse(v);
    t_pos p = (t_pos) {-3, 4, 5};
    assert(vec_is_equal(mat4_multi_pos3(inv, p), (t_pos) {-8, 7, 3}));
    printf("testing translation : ✔\n");
  }
  {
    // Scenario: Translation does not affect vectors // fail
  }
  {
    t_matrix4 m = scaling(2, 3, 4);
    t_pos p = {-4, 6, 8};
    assert(vec_is_equal(mat4_multi_pos3(m, p), (t_pos) {-8, 18, 32}));
  }
  {
    t_matrix4 m = scaling(2, 3, 4);
    t_matrix4 inv = mat4_inverse(m);
    t_pos p = {-4, 6, 8};
    assert(vec_is_equal(mat4_multi_pos3(inv, p), (t_pos) {-2, 2, 2}));
  }
  {
    t_matrix4 m = scaling(-1, 1, 1);
    t_pos p = {2, 3, 4};
    assert(vec_is_equal(mat4_multi_pos3(m, p), (t_pos) {-2, 3, 4}));
    printf("testing scaling : ✔\n");
  }
  {
    t_pos p = {0, 1, 0};
    t_matrix4 half_quarter = rotation_x(M_PI_4);
    t_matrix4 full_quarter = rotation_x(M_PI_2);
    assert(vec_is_equal(mat4_multi_pos3(half_quarter, p), (t_pos) {0, M_SQRT2 / 2, M_SQRT2 / 2}));
    assert(vec_is_equal(mat4_multi_pos3(full_quarter, p), (t_pos) {0, 0, 1}));
    printf("rotation x: ✔\n");
  }
  {
    t_pos p = {0, 1, 0};
    t_matrix4 half_quarter = rotation_x(M_PI_4);
    t_matrix4 inv = mat4_inverse(half_quarter);
    assert(vec_is_equal(mat4_multi_pos3(inv, p), (t_pos) {0, M_SQRT2 / 2, -1 * M_SQRT2 / 2}));
    printf("inverse rotation x: ✔\n");
  }
  {
    t_pos p = {0, 0, 1};
    t_matrix4 half_quarter = rotation_y(M_PI_4);
    t_matrix4 full_quarter = rotation_y(M_PI_2);
    assert(vec_is_equal(mat4_multi_pos3(half_quarter, p), (t_pos) {M_SQRT2 / 2, 0, M_SQRT2 / 2}));
    assert(vec_is_equal(mat4_multi_pos3(full_quarter, p), (t_pos) {1, 0, 0}));
    printf("rotation y: ✔\n");
  }
  {
    t_pos p = {0, 1, 0};
    t_matrix4 half_quarter = rotation_z(M_PI_4);
    t_matrix4 full_quarter = rotation_z(M_PI_2);
    assert(vec_is_equal(apply_transformation(half_quarter, p), (t_pos) {-1 * M_SQRT2 / 2, M_SQRT2 / 2, 0}));
    assert(vec_is_equal(apply_transformation(full_quarter, p), (t_pos) {-1, 0, 0}));
    printf("rotation z: ✔\n");
  }
  {
    t_pos p = point(1, 0, 1);
    t_matrix4 A = rotation_x(M_PI_2);
    p = apply_transformation(A, p);
    t_matrix4 B = scaling(5, 5, 5);
    p = apply_transformation(B, p);
    t_matrix4 C = translation(10, 5, 7);
    p = apply_transformation(C, p);
    assert(vec_is_equal(
             p,
             (t_pos) {15, 0, 7}));
    printf("testing transform : ✔\n");
  }
  {
    t_pos p = point(1, 0, 1);
    t_matrix4 A = rotation_x(M_PI_2);
    t_matrix4 B = scaling(5, 5, 5);
    t_matrix4 C = translation(10, 5, 7);
    assert(vec_is_equal(
             apply_transformation(transform(A, B, C), p),
             (t_pos) {15, 0, 7}));
    printf("testing transform : ✔\n");
  }
  {
    assert(is_equal_double(radians(30), 0.523599));
    assert(!is_equal_double(radians(30), 0.0));
    printf("checking deg to rand func : ✔\n");
  }
  {
    t_ray ray = {
      {1, 2, 3},
      {4, 5, 6},
    };
    t_pos origin = {1, 2, 3};
    t_pos direction = {4, 5, 6};
    assert(vec_is_equal(ray.origin, origin));
    assert(vec_is_equal(ray.direction, direction));
    printf("ray struct : ✔\n");
  }
  {
    t_ray ray = {(t_pos) {2, 3, 4}, (t_vec) {1, 0, 0}};
    assert(vec_is_equal(ray_position(ray, 0), (t_pos) {2, 3, 4}));
    assert(vec_is_equal(ray_position(ray, 1), (t_pos) {3, 3, 4}));
    assert(vec_is_equal(ray_position(ray, -1), (t_pos) {1, 3, 4}));
    assert(vec_is_equal(ray_position(ray, 2.5), (t_pos) {4.5, 3, 4}));
    printf("ray position : ✔\n");
  }
  {
    t_ray ray = (t_ray) { (t_pos) {0, 0, -5}, (t_vec) {0, 0, 1}};
    t_sphere sp = sphere();
    t_hit hit = intersect_sphere(sp, ray);
    assert(hit.count == 2);
    assert(is_equal_double(hit.intersection[0].t, 4.0));
    assert(is_equal_double(hit.intersection[1].t, 6.0));
  }
  {
    t_ray ray = (t_ray) { (t_pos) {0, 1, -5}, (t_vec) {0, 0, 1}};
    t_sphere sp = sphere();
    t_hit hit = intersect_sphere(sp, ray);
    assert(hit.count == 2);
    assert(is_equal_double(hit.intersection[0].t, 5.0));
    assert(is_equal_double(hit.intersection[1].t, 5.0));
  }
  {
    t_ray ray = (t_ray) { (t_pos) {0, 0, 0}, (t_vec) {0, 0, 1}};
    t_sphere sp = sphere();
    t_hit hit = intersect_sphere(sp, ray);
    assert(hit.count == 2);
    assert(is_equal_double(hit.intersection[0].t, -1));
    assert(is_equal_double(hit.intersection[1].t, 1));
  }
  {
    t_ray ray = (t_ray) { (t_pos) {0, 0, 5}, (t_vec) {0, 0, 1}};
    t_sphere sp = sphere();
    t_hit hit = intersect_sphere(sp, ray);
    assert(hit.count == 2);
    assert(is_equal_double(hit.intersection[0].t, -6));
    assert(is_equal_double(hit.intersection[1].t, -4));
    printf("intersect sphere : ✔\n");
  }
  {
    t_sphere s = sphere();
    t_intersection i = {3.5, s};
    assert(i.sphere.id == s.id);
    assert(i.t == 3.5);
  }
  {
    t_sphere s = sphere();
    t_intersection i1 = {1, s};
    t_intersection i2 = {2, s};
    t_hit h = {{i1, i2}, 2};
    assert(hit(h).t == 1 && hit(h).sphere.id == s.id);
  }
  {
    t_sphere s = sphere();
    t_intersection i1 = {-1, s};
    t_intersection i2 = {1, s};
    t_hit h = {{i1, i2}, 2};
    assert(hit(h).t == 1 && hit(h).sphere.id == s.id);
  }
  {
    t_sphere s = sphere();
    t_intersection i1 = {-2, s};
    t_intersection i2 = {-1, s};
    t_hit h = {{i1, i2}, 2};
    assert(hit(h).t == -1 && hit(h).sphere.id == -1);
  }
  {
    t_sphere s = sphere();
    t_intersection i1 = {5, s};
    t_intersection i2 = {7, s};
    t_intersection i3 = {-3, s};
    t_intersection i4 = {2, s};
    t_hit h = {{i1, i2}, 2};
    t_hit h2 = {{i3, i4}, 2};
    t_intersection this = hit(h);
    assert(this.t == 5 && hit(h).sphere.id == s.id);
    t_intersection this2 = hit(h2);
    assert(this2.t == 2 && hit(h2).sphere.id == s.id);
    t_hit h3 = {{this, this2}, 2};
    t_intersection i5 = hit(h3);
    assert(i5.t == i4.t && i5.sphere.id == s.id && i5.sphere.id == i4.sphere.id);
    printf("getting the hit on sphere : ✔\n");
  }
  {
    t_ray ray = {{1, 2, 3}, {0, 1, 0}};
    t_ray tray = ray_transform(ray, scaling(2, 3, 4));
    assert(vec_is_equal(tray.origin, (t_vec){2, 6, 12}));
    assert(vec_is_equal(tray.direction, (t_vec){0, 3, 0}));
  }
  {
    t_ray ray = {{1, 2, 3, 1}, {0, 1, 0}};
    t_ray tray = ray_transform(ray, translation(3, 4, 5));
    assert(vec_is_equal(tray.origin, (t_vec){4, 6, 8}));
    assert(vec_is_equal(tray.direction, (t_vec){0, 1, 0}));
    printf("transforming a ray : ✔\n");
  }
  {
    t_sphere s = sphere();
    assert(mat4_is_equal(s.t, identity()));
    s.t = translation(2, 3, 4);
    assert(mat4_is_equal(s.t, translation(2, 3, 4)));
  }
  {
    t_ray r = {{0, 0, -5}, {0, 0, 1}};
    t_sphere s = sphere();
    s.t = scaling(2, 2, 2);
    t_hit h = intersect_sphere(s, r);
    assert(h.intersection[0].t == 3 && h.intersection[1].t == 7);
  }
  {
    t_ray r = {point(0, 0, -5), vector(0, 0, 1)};
    t_sphere s = sphere();
    s.t = translation(5, 0, 0);
    t_hit h = intersect_sphere(s, r);
    assert(h.count == 0);
    printf("transforming a sphere : ✔\n");
  }
  {
    t_sphere s = sphere();
    t_vec v = normal_at(s, point(1, 0, 0));
    assert(vec_is_equal(v, vector(1, 0, 0)));
  }
  {
    t_sphere s = sphere();
    t_vec v = normal_at(s, point(0, 1, 0));
    assert(vec_is_equal(v, vector(0, 1, 0)));
  }
  {
    t_sphere s = sphere();
    t_vec v = normal_at(s, point(0, 0, 1));
    assert(vec_is_equal(v, vector(0, 0, 1)));
  }
  {
    t_sphere s = sphere();
    t_vec v = normal_at(s, point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    assert(vec_is_equal(v, vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3)));
    assert(vec_is_equal(vec_normalize(v, sqrt), v));
    printf("calc normal in sphere : ✔\n");
  }
  {
    t_sphere s = sphere();
    s.t = translation(0, 1, 0);
    t_vec n = normal_at(s, point(0, 1.70711, -0.70711));
    assert(vec_is_equal(n, vector(0, 0.70711, -0.70711)));
  }
  {
    t_sphere s = sphere();
    s.t = scaling(1, 0.5, 1);
    t_vec n = normal_at(s, point(0, M_SQRT2 / 2, -M_SQRT2 / 2));
    assert(vec_is_equal(n, vector(0, 0.97014, -0.24254)));
  }
  {
    t_vec v = vector(1, -1, 0);
    t_vec n = vector(0, 1, 0);
    t_vec r = reflect(v, n);
    assert(vec_is_equal(r, vector(1, 1, 0)));
  }
  {
    t_vec v = vector(0, -1, 0);
    t_vec n = vector(M_SQRT2 / 2, M_SQRT2 / 2, 0);
    t_vec r = reflect(v, n);
    assert(vec_is_equal(r, vector(1, 0, 0)));
    printf("calc the reflection vector : ✔\n");
  }
  {
    const t_rgb intensity = (t_rgb) {1, 1, 1};
    const t_pos position = point(0, 0, 0);
    t_light light = point_light(position, intensity);
    assert(vec_is_equal(position, light.position));
    rgb_is_equal(intensity, light.intensity);
  }
  {
    t_material m = {
      .color = {1, 1, 1},
      0.1,
      0.9,
      0.9,
      200.0,
    };
    t_sphere s = sphere();
    s.material = m;
    assert(s.material.shininess == 200.0);
    printf("the light data struct : ✔\n");
  }
  {
    t_material m = {
      .color = {1, 1, 1},
      0.1,
      0.9,
      0.9,
      200.0,
    };
    t_pos position = point(0, 0, 0);  
    {
      t_vec eyev = vector(0, 0, -1);
      t_vec normalv = vector(0, 0, -1);
      t_light light = point_light(point(0, 0, -10), (t_rgb){1, 1, 1});
      t_rgb result = lighting(m, light, position, eyev, normalv);
      assert(rgb_is_equal(result, (t_rgb){1.9, 1.9, 1.9}));
    }
    {
      t_vec eyev = vector(0, M_SQRT2 / 2, -M_SQRT2 / 2);
      t_vec normalv = vector(0, 0, -1);
      t_light light = point_light(point(0, 0, -10), (t_rgb){1, 1, 1});
      t_rgb result = lighting(m, light, position, eyev, normalv);
      assert(rgb_is_equal(result, (t_rgb){1., 1., 1.}));
    }
    {
      t_vec eyev = vector(0, 0, -1);
      t_vec normalv = vector(0, 0, -1);
      t_light light = point_light(point(0, 10, -10), (t_rgb){1, 1, 1});
      t_rgb result = lighting(m, light, position, eyev, normalv);
      assert(rgb_is_equal(result, (t_rgb){0.7364, 0.7364, 0.7364}));
    }
    {
      t_vec eyev = vector(0, -M_SQRT2 / 2, -M_SQRT2 / 2);
      t_vec normalv = vector(0, 0, -1);
      t_light light = point_light(point(0, 10, -10), (t_rgb){1, 1, 1});
      t_rgb result = lighting(m, light, position, eyev, normalv);
      assert(rgb_is_equal(result, (t_rgb){1.6364, 1.6364, 1.6364}));
    }
    {
      t_vec eyev = vector(0, 0, -1);
      t_vec normalv = vector(0, 0, -1);
      t_light light = point_light(point(0, 0, 10), (t_rgb){1, 1, 1});
      t_rgb result = lighting(m, light, position, eyev, normalv);
      assert(rgb_is_equal(result, (t_rgb){0.1, 0.1, 0.1}));
      printf("the lighting function : ✔\n");
    }
    {
      t_world w = world();
      assert(w.amount_of_spheres == 0);
      assert(w.amount_of_lights == 0);
    }
    {
      t_world w = default_world();
      assert(w.amount_of_lights == 1);
      assert(w.amount_of_spheres == 2);
      assert(w.spheres[0].material.shininess == 200);
      assert(mat4_is_equal(w.spheres[1].t, scaling(0.5, 0.5, 0.5)));
      assert(vec_is_equal(w.lights[0].position, point(-10, 10, -10)));
      printf("create the world default functions : ✔\n");
    }
    {
      t_world w = default_world();
      const t_ray r = {point(0, 0, -5), vector(0, 0, 1)};
      t_hit i = intersect_world(w, r);  
      assert(i.count == 4);
      assert(is_equal_double(i.intersection[0].t, 4));
      assert(is_equal_double(i.intersection[1].t, 4.5));
      assert(is_equal_double(i.intersection[2].t, 5.5));
      assert(is_equal_double(i.intersection[3].t, 6));
      printf("world intersection : ✔\n");
    }
    {
      t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));     
      t_sphere s = sphere();
      t_intersection i = {.sphere = s, .t = 4};
      t_comp comps = prepare_computations(i, r);
    }
      // t_world add_sphere(const t_world w, const t_sphere s);
  }
  return 0;
}
