#include <iostream>
using namespace std;

int i = -1;

void local() {
	int i = -2;
	for (int i = 0; i < 10; i++)
		if (!(i & 1)) cout << "Inside for: " << i << endl;
		// even int: not (i & 1); odd int: (i & 1)
	cout << "Outside for: " << i << endl;
}

int main() {
	local();
	cout << "Global: " << i << endl;
	return 0;
}
