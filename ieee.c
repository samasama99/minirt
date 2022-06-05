#include <stdio.h>
#include <math.h>

int main() {
  printf("%f / %f = %f\n", 5.0, 0.0, +5.0/ +0.0);
  if (5.0 / 0.0 == INFINITY) {
      printf("%f\n", INFINITY);
  }
  printf("%f\n", -INFINITY);
  printf("%f\n", +INFINITY);
  printf("%f\n", NAN);
}
