#include <stdio.h>
#ifndef bool
enum bool { false = 0, true = 1 };
#endif

int toBool(int arg) {
  return arg != false;
}

int main(int argc, char **argv) {
  printf("%i\n", toBool(2));
  return 0;
}
