#include <iostream>
#include <vector>

using namespace std;

struct ii { int x, y; };
using vi = vector<int>;
using vvi = vector<vi>;
using vc = vector<char>;
using vvc = vector<vc>;

bool find_next(const vvi& grid, int& x, int& y) {
	int current = 1'000'000'000;
	int next_x = x;
	int next_y = y;

	for (ii p : { ii{x - 1, y}, ii{x + 1, y}, ii{x, y - 1}, ii{x, y + 1} }) {
		if (p.x >= 0 && p.x < grid.at(0).size()) {
			if (p.y >= 0 && p.y < grid.size()) {

				if (grid.at(p.y).at(p.x) < current && grid.at(p.y).at(p.x) > grid.at(y).at(x)) {
					current = grid.at(p.y).at(p.x);
					next_x = p.x;
					next_y = p.y;
				}

			}
		}
	}

	x = next_x;
	y = next_y;
	return current < 1'000'000'000;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int b, h;
		cin >> b >> h;

		int lowest = 1'000'000'000;
		int sx = 0, sy = 0;
		vvi grid(h, vi(b, 0));

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < b; x++) {
				cin >> grid[y][x];

				if (grid[y][x] < lowest) {
					lowest = grid[y][x];
					sx = x;
					sy = y;
				}
			}
		}

		vvc result(h, vc(b, '.'));
		char letter = 'A';

		do {
			result[sy][sx] = letter;
			letter++;
		} while (find_next(grid, sx, sy));

		for (auto r : result) {
			cout << i << " ";
			for (char c : r) {
				cout << c;
			}
			cout << endl;
		}
	}
}
