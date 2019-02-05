#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int c_u, c_m, n_u, n_m;
		cin >> c_u >> c_m >> n_u >> n_m;

		int up_u = (n_u - c_u + 24) % 24;
		int down_u = (c_u - n_u + 24) % 24;

		int up_m = (n_m - c_m + 60) % 60;
		int down_m = (c_m - n_m + 60) % 60;

		bool flip_up = c_m > n_m;
		bool flip_down = c_m < n_m;

		int best = min(
			min(up_u + up_m - flip_up, down_u + up_m + flip_up),
			min(up_u + down_m + flip_down, down_u + down_m - flip_down)
		);

		cout << i << " " << best << endl;
	}
}
