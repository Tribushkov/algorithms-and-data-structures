#include <iostream>
#include <algorithm>

using namespace std;

int *calculate_min_roads(int *x, int n) {
	int *f = new int[n];

	for (int i = 0; i < n; ++i) {
		cin >> x[i];
	}

	sort(x, x + n);

	if (n >= 1) f[0] = 0;
	if (n >= 2) f[1] = x[1] - x[0];
	if (n >= 3) f[2] = x[1] - x[0] + x[2] - x[1];
	if (n >= 4) f[3] = x[1] - x[0] + x[3] - x[2];
	if (n >= 5) {
		for (int i = 4; i < n; ++i) {
			f[i] = min(f[i - 2] + (x[i] - x[i - 1]), f[i - 3] + (x[i] - x[i - 1]) + (x[i - 1] - x[i - 2]));
		}
	}

	return f;
}

int main() {
	int n;

	cin >> n;

	int *coordinates = new int[n];
	int *min_roads = calculate_min_roads(coordinates, n);

	cout << min_roads[n - 1];

	return 0;
}
