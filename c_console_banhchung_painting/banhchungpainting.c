#include <stdio.h>
int main() {
  const char *S = " *";
  int size = 1, i, j;
  printf("Size of banh chung (odd) = ");
  scanf("%i", &size);
  (size % 2) || size--;
  printf("\nThis is your %i-sized banh chung:\n", size);
  for (i = 0; i < size; i++) printf(S);
  printf("\n");
  for (i = 1; i < size / 2; i++) {
    printf(S);
    for (j = 1; j < size / 2; j++)
      if (j == i) printf(S); else printf("  ");
    printf(S);
    for (j = 1; j < size / 2; j++)
      if (size / 2 - j  == i) printf(S); else printf("  ");
    printf(S);
    printf("\n");
  }
  for (i = 0; i < size; i++) printf(S);
  printf("\n");
  for (i = 1; i < size / 2; i++) {
    printf(S);
    for (j = 1; j < size / 2; j++)
      if (size / 2 - j == i) printf(S); else printf("  ");
    printf(S);
    for (j = 1; j < size / 2; j++)
      if (j == i) printf(S); else printf("  ");
    printf(S);
    printf("\n");
  }
  for (i = 0; i < size; i++) printf(S);
  printf("\n");
  return 0;
}
