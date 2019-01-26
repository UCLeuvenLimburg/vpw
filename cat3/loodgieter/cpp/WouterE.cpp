#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct pos { int x, y; };
struct dir { int dx, dy; };
bool operator < (const pos& l, const pos& r) { return memcmp(&l, &r, sizeof(pos)) < 0; }

int t;
vector<vector<bool>> field;
pair<int, int> result;

void solve(set<pos> seen, pos current, dir direction) {
	int n_x = current.x + direction.dx;
	int n_y = current.y + direction.dy;
	pos n_p = { n_x, n_y };

	if (seen.size() > t || seen.find(n_p) != seen.end()) {
		return;
	} 
	else if (n_x < 0 || n_x >= field.size() || n_y < 0 || n_y >= field.at(0).size()) {
		result.first++;
		result.second = max(result.second, (int)seen.size());
	}
	else {
		seen.insert(n_p);

		if (field.at(n_x).at(n_y)) {
			dir n_d = { direction.dy, -direction.dx };
			solve(seen, n_p, n_d);

			n_d = { -direction.dy, direction.dx };
			solve(seen, n_p, n_d);
		}
		else {
			solve(seen, n_p, direction);
		}
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int b, h;
		cin >> b >> h >> t;

		field = vector<vector<bool>>(b, vector<bool>(h, false));
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < b; k++) {
				char c;
				cin >> c;
				field.at(k).at(j) = c == 'B';
			}
		}

		result = { 0, 0 };
		solve(set<pos>(), { 0, -1 }, { 0, 1 });
		cout << i << " " << result.first << " " << result.second << endl;
	}
}
