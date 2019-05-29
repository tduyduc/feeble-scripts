#include <iostream>
using namespace std;

float *solve(int n, float **a, float *c) {
	float *r = new float[n];
	if (n == 2) {
		if (a[0][1] != 0) {
			float t = -a[1][1] / a[0][1];
			a[0][0] *= t;
			a[0][1] *= t;
			c[0] *= t;
			a[0][0] += a[1][0];
			a[0][1] += a[1][1];
			c[0] += c[1];
		}
		if (a[0][0] != 0) r[0] = c[0] / a[0][0];
		else if (c[0] != 0) {
			cout << "No solution!\n";
			return NULL;
		} else {
			cout << "Infinite number of solutions!\n";
			return NULL;
		}
		c[1] -= a[1][0] * r[0];
		if (a[1][1] != 0) r[1] = c[1] / a[1][1];
		else if (c[1] != 0) {
			cout << "No solution!\n";
			return NULL;
		} else {
			cout << "Infinite number of solutions!\n";
			return NULL;
		}
		return r;
	} else return NULL;
}

int main() {
	float **a, *c, *r;
	int n = 2, i = 0;
	a = new float*[n];
	c = new float[n];
	r = new float[n];
	for (; i < n; i++)
		a[i] = new float[n];
	a[0][0] = 1.; a[0][1] = 1.; c[0] = 36.;
	a[1][0] = 4.; a[1][1] = 2.; c[1] = 100.;
	if (r = solve(n, a, c))
		cout << "x1 = " << r[0] << ", x2 = " << r[1] << endl;
	return 0;
}                             
