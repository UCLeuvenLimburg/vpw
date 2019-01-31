#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<pair<int, int>> nodes;
int max_count;

int dist(int a, int b) {
	return abs(nodes.at(a).first - nodes.at(b).first) + abs(nodes.at(a).second - nodes.at(b).second);
}

int minimum_span(int current_node, const vector<bool>& subset, int count) {
	map<int, int> open;
	int closest_to_home = current_node;

	for (int j = 0; j < nodes.size() - 1; j++) {
		if (subset.at(j)) {
			open[j + 1] = dist(current_node, j + 1);
		}
	}

	int cost = count;
	for (; count > 0; count--) {
		auto it = min_element(open.begin(), open.end(), [](auto p1, auto p2) { return p1.second < p2.second; });
		int node = it->first;
		cost += it->second;
		open.erase(it);

		if (dist(0, node) < dist(0, closest_to_home)) closest_to_home = node;

		for (auto& p : open) p.second = min(p.second, dist(node, p.first));
	}

	return cost + dist(0, closest_to_home);
}

void solve(int current_node, vector<bool> subset, int time_left, int food_count) {	// Brute force with heuristic (~ minimum spanning tree)
	if (max_count == nodes.size() - 1) return;
	if (minimum_span(current_node, subset, max(0, max_count - food_count)) > time_left) return;

	max_count = max(max_count, food_count);

	for (int next = 0; next < nodes.size() - 1; next++) {
		if (subset.at(next))
		{
			subset.at(next).flip();
			solve(next + 1, subset, time_left - dist(current_node, next + 1) - 1, food_count + 1);
			subset.at(next).flip();
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

		max_count = 0;
		solve(0, vector<bool>(nodes.size() - 1, true), t, 0);

		cout << i << " " << max_count << endl;
	}
}
