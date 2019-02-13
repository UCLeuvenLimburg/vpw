#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct path { int cost, dist, x, y; };
bool operator > (const path& l, const path& r) { return l.cost != r.cost ? l.cost > r.cost : l.dist > r.dist; }

int r, k;
vector<vector<int>> kaart;

path solve() {													// dijkstra
	vector<vector<bool>> seen(r, vector<bool>(k, false));

	priority_queue<path, vector<path>, greater<path>> queue;
	for(int i = 0; i < r; i++) queue.push(path{ 0, 0, -1, i });

	while (queue.top().x != k - 1) {
		path p = queue.top();
		queue.pop();

		if (p.x < 0 || !seen.at(p.y).at(p.x)) {
			if(p.x >= 0) seen.at(p.y).at(p.x) = true;

			queue.push(								{ p.cost + kaart.at(p.y).at(p.x + 1), p.dist + 1, p.x + 1, p.y });
			if (p.x > 0) queue.push(				{ p.cost + kaart.at(p.y).at(p.x - 1), p.dist + 1, p.x - 1, p.y });
			if (p.x >= 0 && p.y > 0) queue.push(	{ p.cost + kaart.at(p.y - 1).at(p.x), p.dist + 1, p.x, p.y - 1 });
			if (p.x >= 0 && p.y < r - 1) queue.push({ p.cost + kaart.at(p.y + 1).at(p.x), p.dist + 1, p.x, p.y + 1 });
		}
	}

	return queue.top();
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> r >> k;

		kaart = vector<vector<int>>(r, vector<int>(k, 0));
		for (int j = 0; j < r; j++) {
			for (int l = 0; l < k; l++) {
				cin >> kaart.at(j).at(l);
			}
		}

		path sol = solve();
		cout << i << " " << sol.dist << " " << sol.cost << endl;
	}
}
