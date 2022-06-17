/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:56:03 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/21 12:44:19 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

double mat2_determinant(t_matrix2 m) {
  return (m.l1_c1 * m.l2_c2 - m.l1_c2 * m.l2_c1);
}

void mat3_print(t_matrix3 mat) {
  printf("|%.2f %.2f %.2f|\n", mat.l1_c1, mat.l1_c2, mat.l1_c3);
  printf("|%.2f %.2f %.2f|\n", mat.l2_c1, mat.l2_c2, mat.l2_c3);
  printf("|%.2f %.2f %.2f|\n", mat.l3_c1, mat.l3_c2, mat.l3_c3);
}

t_matrix3 mat3_mult(t_matrix3 mat1, t_matrix3 mat2) {

  int i;
  int j;
  t_matrix3 mult;

  i = 0;
  j = 0;
  while (i < 3) {
    while (j < 3) {
      mult.m[i][j] = mat1.m[i][0] * mat2.m[0][j] + mat1.m[i][1] * mat2.m[1][j] +
                     mat1.m[i][2] * mat2.m[2][j];
      j++;
    }
    j = 0;
    i++;
  }
  return (mult);
}

t_matrix4 mat4_mult(t_matrix4 mat1, t_matrix4 mat2) {
  int i;
  int j;
  t_matrix4 mult;

  i = 0;
  j = 0;
  while (i < 4) {
    while (j < 4) {
      mult.m[i][j] = mat1.m[i][0] * mat2.m[0][j] + mat1.m[i][1] * mat2.m[1][j] +
                     mat1.m[i][2] * mat2.m[2][j] + mat1.m[i][3] * mat2.m[3][j];
      j++;
    }
    j = 0;
    i++;
  }
  return (mult);
}

t_point apply_transformation(t_transform mat, t_point p) {
  return ((t_point){{
      p.x * mat.l1_c1 + p.y * mat.l1_c2 + p.z * mat.l1_c3 + p.w * mat.l1_c4,
      p.x * mat.l2_c1 + p.y * mat.l2_c2 + p.z * mat.l2_c3 + p.w * mat.l2_c4,
      p.x * mat.l3_c1 + p.y * mat.l3_c2 + p.z * mat.l3_c3 + p.w * mat.l3_c4,
      p.x * mat.l4_c1 + p.y * mat.l4_c2 + p.z * mat.l4_c3 + p.w * mat.l4_c4,
  }});
}

bool matrix_is_equal(t_matrix4 m, t_matrix4 n) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (j < 4) {
    while (i < 4) {
      if (is_equal_double(m.m[j][i], n.m[j][i]) == false)
        return false;
      ++i;
    }
    i = 0;
    ++j;
  }
  return true;
}

t_matrix4 transpose(t_matrix4 m) {
  int i;
  int j;
  t_matrix4 t;

  i = 0;
  j = 0;
  while (i < 4) {
    while (j < 4) {
      t.m[i][j] = m.m[j][i];
      j++;
    }
    j = 0;
    i++;
  }
  return (t);
}

t_matrix2 mat3_submatrix(t_matrix3 m, int row, int col) {
  int i;
  int j;
  int i2;
  int j2;
  t_matrix2 n;

  i = 0;
  j = 0;
  i2 = 0;
  j2 = 0;
  // panic(row < 0 || row > 2 || col < 0 || col > 2, "out of bound params"
  //       , __func__, __FILE__, __LINE__);
  while (j < 3 && j2 < 3) {
    if (j == row)
      ++j;
    while (i < 3 && j < 3 && i2 < 3 && j2 < 3) {
      if (i == col)
        ++i;
      n.m[j2][i2] = m.m[j][i];
      ++i;
      ++i2;
    }
    i = 0;
    i2 = 0;
    ++j;
    ++j2;
  }
  return n;
}

t_matrix3 mat4_submatrix(t_matrix4 m, int row, int col) {
  int i;
  int j;
  int i2;
  int j2;
  t_matrix3 n;

  i = 0;
  j = 0;
  i2 = 0;
  j2 = 0;
  // panic(row < 0 || row > 3 || col < 0 || col > 3, "out of bound params"
  //       , __func__, __FILE__, __LINE__);
  while (j < 4) {
    if (j == row)
      ++j;
    while (i < 4) {
      if (i == col)
        ++i;
      n.m[j2][i2] = m.m[j][i];
      ++i;
      ++i2;
    }
    i = 0;
    i2 = 0;
    ++j;
    ++j2;
  }
  return n;
}

double mat3_minor(t_matrix3 m, int row, int col) {
  t_matrix2 n;

  n = mat3_submatrix(m, row, col);
  return mat2_determinant(n);
}

double mat3_cofactor(t_matrix3 m, int row, int col) {
  t_matrix3 s = (t_matrix3){{
      1, -1, 1,
      -1, 1, -1,
      1, -1, 1,
  }};
  return s.m[row][col] * mat3_minor(m, row, col);
}

double mat3_determinant(t_matrix3 m) {
  return (m.l1_c1 * mat3_cofactor(m, 0, 0) + m.l1_c2 * mat3_cofactor(m, 0, 1) +
          m.l1_c3 * mat3_cofactor(m, 0, 2));
}

double mat4_minor(t_matrix4 m, int row, int col) {
  t_matrix3 x;

  x = mat4_submatrix(m, row, col);
  return mat3_determinant(x);
}

double mat4_cofactor(t_matrix4 m, int row, int col) {
  t_matrix4 x = {{
      1, -1, 1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1, 1, -1, 1,
  }};

  return x.m[row][col] * mat4_minor(m, row, col);
}

double mat4_determinant(t_matrix4 m) {
  return (m.l1_c1 * mat4_cofactor(m, 0, 0) + m.l1_c2 * mat4_cofactor(m, 0, 1) +
          m.l1_c3 * mat4_cofactor(m, 0, 2) + m.l1_c4 * mat4_cofactor(m, 0, 3));
}

bool mat4_is_invertible(t_matrix4 m) { return mat4_determinant(m); }

t_matrix4 inverse(t_matrix4 m) {
  const double id = 1 / mat4_determinant(m);
  return (t_matrix4){{
      mat4_cofactor(m, 0, 0) * id, mat4_cofactor(m, 1, 0) * id,
      mat4_cofactor(m, 2, 0) * id, mat4_cofactor(m, 3, 0) * id,
      mat4_cofactor(m, 0, 1) * id, mat4_cofactor(m, 1, 1) * id,
      mat4_cofactor(m, 2, 1) * id, mat4_cofactor(m, 3, 1) * id,
      mat4_cofactor(m, 0, 2) * id, mat4_cofactor(m, 1, 2) * id,
      mat4_cofactor(m, 2, 2) * id, mat4_cofactor(m, 3, 2) * id,
      mat4_cofactor(m, 0, 3) * id, mat4_cofactor(m, 1, 3) * id,
      mat4_cofactor(m, 2, 3) * id, mat4_cofactor(m, 3, 3) * id,
  }};
}
