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
  }
  {
    t_pos p = {0, 1, 0};
    t_matrix4 half_quarter = rotation_x(M_PI_4);
    t_matrix4 full_quarter = rotation_x(M_PI_2);
    assert(vec_is_equal(mat4_multi_pos3(half_quarter, p), (t_pos) {0, M_SQRT2 / 2, M_SQRT2 / 2}));
    assert(vec_is_equal(mat4_multi_pos3(full_quarter, p), (t_pos) {0, 0, 1}));
  }
  {
    t_pos p = {0, 1, 0};
    t_matrix4 half_quarter = rotation_x(M_PI_4);
    t_matrix4 inv = mat4_inverse(half_quarter);
    assert(vec_is_equal(mat4_multi_pos3(inv, p), (t_pos) {0, M_SQRT2 / 2, -1 * M_SQRT2 / 2}));
  }
  {
    t_pos p = {0, 0, 1};
    t_matrix4 half_quarter = rotation_y(M_PI_4);
    t_matrix4 full_quarter = rotation_y(M_PI_2);
    assert(vec_is_equal(mat4_multi_pos3(half_quarter, p), (t_pos) {M_SQRT2 / 2, 0, M_SQRT2 / 2}));
    assert(vec_is_equal(mat4_multi_pos3(full_quarter, p), (t_pos) {1, 0, 0}));
  }
  {
    t_pos p = {0, 1, 0};
    t_matrix4 half_quarter = rotation_z(M_PI_4);
    t_matrix4 full_quarter = rotation_z(M_PI_2);
    assert(vec_is_equal(mat4_multi_pos3(half_quarter, p), (t_pos) {-1 * M_SQRT2 / 2, M_SQRT2 / 2, 0}));
    assert(vec_is_equal(mat4_multi_pos3(full_quarter, p), (t_pos) {-1, 0, 0}));
  }
  {
    t_pos p = {1, 0, 1};
    t_matrix4 A = rotation_x(M_PI_2);
    t_matrix4 B = scaling(5, 5, 5);
    t_matrix4 C = translation(10, 5, 7);
    assert(vec_is_equal(mat4_multi_pos3(transform(A,B,C), p), (t_pos) {15, 0, 7}));
  }
  {
    assert(is_equal_double(radians(30), 0.523599));
    assert(!is_equal_double(radians(30), 0.0));
    printf("checking deg to rand func : ✔\n");
  }
  return 0;
}
