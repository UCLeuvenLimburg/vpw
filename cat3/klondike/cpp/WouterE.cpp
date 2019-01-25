#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct pos { int x, y; };
bool operator < (const pos& l, const pos& r) { return memcmp(&l, &r, sizeof(pos)) < 0; }

vector<vector<int>> veld;
pos start;
map<pos, int> cache;

struct priority { bool operator () (const pos& l, const pos& r) { return cache.at(l) > cache.at(r); } };

bool valid(pos p) {
	return p.x >= 0 && p.y >= 0 && p.x < veld.size() && p.y < veld.at(0).size() && veld.at(p.x).at(p.y) > 0;
}

bool exit(pos p) {
	if (p.x < 0 || p.y < 0 || p.x >= veld.size() || p.y >= veld.at(0).size() || veld.at(p.x).at(p.y) > 0) return false;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (valid(pos{ p.x + i, p.y + j })) return true;
		}
	}
	return false;
}

int solve() {
	priority_queue<pos, vector<pos>, priority> todo;
	todo.push(start);
	cache[start] = veld.at(start.x).at(start.y);

	while (!todo.empty()) {
		pos s = todo.top();
		todo.pop();

		int d = veld.at(s.x).at(s.y);
		for (pos p : {
				pos{ s.x + d, s.y },
				pos{ s.x - d, s.y },
				pos{ s.x, s.y + d },
				pos{ s.x, s.y - d },
				pos{ s.x + d, s.y + d },
				pos{ s.x - d, s.y + d },
				pos{ s.x + d, s.y - d },
				pos{ s.x - d, s.y - d }
		}) {
			if (exit(p)) return cache.at(s);
			else if (valid(p) && cache.find(p) == cache.end()) {
				cache[p] = cache.at(s) + veld.at(p.x).at(p.y);
				todo.push(p);
			}
		}
	}
	
	return -1;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int w, h;
		cin >> w >> h;

		veld = vector<vector<int>>(w + 2, vector<int>(h + 2, 0));
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < w; k++) {
				char c;
				cin >> c;
				veld.at(k + 1).at(j + 1) = c == '.' ? 0 : c - '0';
			}
		}

		cin >> start.x >> start.y;
		start.x++;
		start.y++;

		cache.clear();
		int result = solve();
		if (result == -1) {
			cout << i << " ONMOGELIJK" << endl;
		}
		else {
			cout << i << " " << result << endl;
		}
	}
}
