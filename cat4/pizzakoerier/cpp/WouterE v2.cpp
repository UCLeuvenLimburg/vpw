#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct order { int from, to, time, cost; };

const int inf = 1'000'000'000;

void all_pair_shortest_path(vector<vector<int>>& graph) {
	for (int i = 0; i < graph.size(); i++) {
		for (int from = 0; from < graph.size(); from++) {
			for (int to = 0; to < graph.size(); to++) {
				graph.at(from).at(to) = min(graph.at(from).at(to), graph.at(from).at(i) + graph.at(i).at(to));
			}
		}
	}
}

int solve(const vector<vector<int>>& graph, const vector<order>& orders) {
	int max_time = max_element(orders.begin(), orders.end(), [](order l, order r) {return l.time < r.time; })->time;

	vector<vector<int>> cost(graph.size(), vector<int>(max_time + 1, 0));

	int t = max_time, next_t = 0;
	while (t >= 0) {
		for (order o : orders) {
			if (next_t < o.time && o.time < t) next_t = o.time;	// => iterate through all o.time and skip unused values of time => speedup

			for (int i = 0; i < graph.size(); i++) {
				if (t + graph.at(i).at(o.from) + graph.at(o.from).at(o.to) <= o.time && t < o.time) {
					cost.at(i).at(t) = max(cost.at(i).at(t), o.cost + cost.at(o.to).at(o.time));
				}
			}
		}

		t = t == 0 ? -1 : next_t;
		next_t = 0;
	}

	return cost.at(0).at(0);
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int n, m;
		cin >> n >> m;

		vector<vector<int>> graph(n, vector<int>(n, inf));
		for (int j = 0; j < n; j++) graph.at(j).at(j) = 0;
		for (int j = 0; j < m; j++) {
			int from, to, cost;
			cin >> from >> to >> cost;
			graph.at(from).at(to) = cost;
			graph.at(to).at(from) = cost;
		}

		all_pair_shortest_path(graph);

		int k;
		cin >> k;

		vector<order> orders(k, { 0, 0, 0, 0 });
		for (order& o : orders) cin >> o.from >> o.to >> o.time >> o.cost;

		cout << i << " " << solve(graph, orders) << endl;
	}
}
