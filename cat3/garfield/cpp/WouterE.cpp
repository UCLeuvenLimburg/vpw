#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int inf = 1'000'000'000;

using ll = long long;
struct ii { int x, y; };

ll max_mask;
vector<ii> nodes;
vector<int> minimum_span;
int max_count;

int dist(int a, int b) {
	return abs(nodes.at(a).x - nodes.at(b).x) + abs(nodes.at(a).y - nodes.at(b).y);
}

void generate_minimum_span() {
	for (ll i = 0; i <= max_mask; i++) {
		map<int, int> todo;

		for (int j = 0; j < nodes.size() - 1; j++) {
			if (i & (1LL << j)) todo[j + 1] = inf;
		}
		int food_count = todo.size();
		todo[0] = 0;

		int cost = food_count;
		while (todo.size() > 0) {
			auto it = min_element(todo.begin(), todo.end(), [](auto p1, auto p2) { return p1.second < p2.second; });
			int node = it->first;
			cost += it->second;
			todo.erase(it);
			for (auto& p : todo) p.second = std::min(p.second, dist(node, p.first));
		}

		minimum_span.at(food_count) = std::min(minimum_span.at(food_count), cost);
	}
}

void solve(int current_node, ll mask, int time_left, int food_count) {	// Brute force with heuristic (~ minimum spanning tree)
	if (dist(current_node, 0) > time_left) return;
	if (max_count < food_count) max_count = food_count;
	if (max_count == nodes.size() - 1) return;
	if (minimum_span.at(max_count - food_count) > time_left) return;

	for (int next = 0; next < nodes.size() - 1; next++) {
		if (mask & (1LL << next))
		{
			solve(next + 1, mask ^ (1LL << next), time_left - dist(current_node, next + 1) - 1, food_count + 1);
		}
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int b, h, t;
		cin >> b >> h >> t;

		nodes.clear();
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < b; k++) {
				char c;
				cin >> c;
				if (c == 'G') {
					nodes.insert(nodes.begin(), { k, j });
				}
				else if(c == 'E') {
					nodes.push_back({ k, j });
				}
			}
		}

		max_mask = (1LL << nodes.size()) - 1LL;
		minimum_span = vector<int>(nodes.size(), inf);
		max_count = 0;

		generate_minimum_span();
		solve(0, max_mask, t, 0);

		cout << i << " " << max_count << endl;
	}
}
