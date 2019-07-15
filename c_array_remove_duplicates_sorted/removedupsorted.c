// Remove duplicate entries in an ASCENDING (sorted) array
#include <stdio.h>

int main() {
	unsigned a[100], i, n, l = 0;
	printf("n = ");
	scanf("%u", &n);
	for (i = 0; i < n; i++) {
		printf("a[%u] = ", i);
		scanf("%u", &a[i]);
	}
	for (i = 1; i < n; i++) {
		if (a[i] > a[i - 1]) {
			a[l + 1] = a[i];
			l += 1;
		}
	}
	n = l + 1;
	for (i = 0; i < n; i++)
		printf("%u\t", a[i]);
	return 0;
}
