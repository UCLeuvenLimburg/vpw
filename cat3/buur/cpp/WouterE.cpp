#include <iostream>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct ii { int x, y; };

int land[500][500];
int b, h;

void spread(int sx, int sy, int from, int to) {		// bfs (because dfs causes StackOverflow)
	queue<ii> todo;
	todo.push({ sx, sy });

	while (!todo.empty()) {
		ii p = todo.front();
		todo.pop();

		if (p.x >= 0 && p.x < b && p.y >= 0 && p.y < h) {
			if (land[p.x][p.y] == from) {
				land[p.x][p.y] = to;
			
				todo.push({p.x - 1, p.y});
				todo.push({p.x + 1, p.y});
				todo.push({p.x, p.y - 1});
				todo.push({p.x, p.y + 1});
			}
		}
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> b >> h;

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < b; x++) {
				char c;
				cin >> c;
				land[x][y] = c - 'A';
			}
		}

		int id = 26;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < b; x++) {
				if (land[x][y] < 26) {
					spread(x, y, land[x][y], id++);
				}
			}
		}

		map<int, set<int>> result;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < b; x++) {
				if (x > 0) result[land[x][y]].insert(land[x - 1][y]);
				if (y > 0) result[land[x][y]].insert(land[x][y - 1]);
				if (x < b - 1) result[land[x][y]].insert(land[x + 1][y]);
				if (y < h - 1) result[land[x][y]].insert(land[x][y + 1]);
			}
		}

		for (auto& p : result) p.second.erase(p.first);

		for (int y = 0; y < h; y++) {
			cout << i;
			for (int x = 0; x < b; x++) {
				cout << " " << result.at(land[x][y]).size();
			}
			cout << endl;
		}
	}
}
