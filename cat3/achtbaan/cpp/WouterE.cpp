#include <iostream>
#include <string>

using namespace std;

struct ci {
	char c;
	int i;
};

ci result[600][600];
int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int len;
		string pad;
		cin >> len >> pad;

		for (int i = 0; i < 600; i++) for (int j = 0; j < 600; j++) result[i][j] = { '.', 0 };

		int x = 300, y = 300, z = 300;
		int dx = 1, dy = 0;

		int min_x = 600, min_z = 600;
		int max_x = 0, max_z = 0;

		for (char c : pad) {
			char cc = '=';
			if (c == 'S') {
				cc = '=';
				dx = 1, dy = 0;
			}
			else if (c == 'V') {
				cc = '_';
			}
			else if (c == 'U') {
				cc = dx == 0 ? '#' :
					dx > 0 ? '/' : '\\';
			}
			else if (c == 'D') {
				z--;
				cc = dx == 0 ? '#' :
					dx > 0 ? '\\' : '/';
			}
			else if (c == 'L') {
				int tmp = dy;
				dy = -dx;
				dx = tmp;
				cc = '_';
			}
			else if (c == 'R') {
				int tmp = dy;
				dy = dx;
				dx = -tmp;
				cc = '_';
			}

			if (result[z][x].i < y) result[z][x] = { cc, y };

			if (x < min_x) min_x = x;
			if (x > max_x) max_x = x;
			if (z < min_z) min_z = z;
			if (z > max_z) max_z = z;

			x += dx, y += dy;

			if (c == 'U') z++;
		}

		for (int z = max_z; z >= min_z; z--) {
			cout << i << " ";
			for (int x = min_x; x <= max_x; x++) {
				cout << result[z][x].c;
			}
			cout << endl;
		}
	}
}
