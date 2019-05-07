#include <stdio.h>

void manip1(const int* x) {
  // constant int.
  // thus, read-only.
  // (*x) += 1;


  // The addr, however, can change.
  x += 1;

  return;
}

void manip2(int* const x) {
  // non-constant int.
  (*x) += 1;

  // But we cannot manip the addr of the ptr.
  /*x += 1;*/

  return;
}

int main() {
  int x = 1;
  printf("(main) x = %d\n", x);
  manip2(&x);
  printf("(main)x = %d\n", x);
}
