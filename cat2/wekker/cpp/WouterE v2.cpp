#include <iostream>
#include <algorithm>

using namespace std;

int sol[1440][1440];

void prepare() {
	for (int i = 0; i < 1440; i++) {
		for (int j = 0; j < 1440; j++) sol[i][j] = 1'000'000'000;

		for (int m = -59; m <= 59; m++) {
			for (int h = -23; h <= 23; h++) {
				int n = (i + h * 60 + m + 1440) % 1440;
				sol[i][n] = min(sol[i][n], abs(m) + abs(h));
			}
		}
	}
}

int main() {
	prepare();

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int c_u, c_m, n_u, n_m;
		cin >> c_u >> c_m >> n_u >> n_m;

		cout << i << " " << sol[c_u * 60 + c_m][n_u * 60 + n_m] << endl;
	}
}
