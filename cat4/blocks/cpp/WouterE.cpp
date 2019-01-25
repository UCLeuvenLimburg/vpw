#include <iostream>
#include <vector>
#include <set>

using namespace std;
struct pos { int x, y, dx, dy, dz; };
int operator < (const pos& l, const pos& r) { return memcmp(&l, &r, sizeof(pos)) < 0; }

vector<vector<int>> veld;
pos start;
const int EMPTY = 0, FIELD = 1, GOAL = 2;

bool in(pos p, int type){
	for (int i = p.x; i < p.x + p.dx; i++) {
		for (int j = p.y; j < p.y + p.dy; j++) {
			if (i < 0 || i >= veld.size() || j < 0 || j >= veld.at(0).size() || veld.at(i).at(j) < type) return false;
		}
	}
	return true;
}

int solve() {
	set<pos> seen;
	vector<pos> current, next;
	current.push_back(start);

	int result = 0;
	if (in(start, GOAL)) return result;

	while (!current.empty()) {
		result++;

		for (pos p : current) {
			for (pos p2 : { 
					pos{ p.x - p.dz, p.y, p.dz, p.dy, p.dx }, 
					pos{ p.x, p.y - p.dz, p.dx, p.dz, p.dy },
					pos{ p.x + p.dx, p.y, p.dz, p.dy, p.dx },
					pos{ p.x, p.y + p.dy, p.dx, p.dz, p.dy }
			}) {
				if (seen.find(p2) == seen.end() && in(p2, FIELD)) {
					if (in(p2, GOAL)) return result;
					seen.insert(p2);
					next.push_back(p2);
				}
			}
		}

		current = next;
		next.clear();
	}

	return -1;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int b, h;
		cin >> b >> h;

		veld = vector<vector<int>>(b, vector<int>(h, 0));
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < b; k++) {
				char c;
				cin >> c;
				veld.at(k).at(j) = c == '*' ? GOAL : c == '.' ? FIELD : EMPTY;
			}
		}

		cin >> start.x >> start.y >> start.dx >> start.dy >> start.dz;

		int result = solve();
		if (result == -1) {
			cout << i << " ONMOGELIJK" << endl;
		}
		else {
			cout << i << " " << result << endl;
		}
	}
}
