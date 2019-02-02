#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

struct order { int from, to, time, cost; };

const int inf = 1'000'000'000;

vector<vector<int>> graph;
vector<order> orders;
map<pair<int, int>, int> cache;

void all_pair_shortest_path() {
	for (int i = 0; i < graph.size(); i++) {
		for (int from = 0; from < graph.size(); from++) {
			for (int to = 0; to < graph.size(); to++) {
				graph.at(from).at(to) = min(graph.at(from).at(to), graph.at(from).at(i) + graph.at(i).at(to));
			}
		}
	}
}

int solve(int start, int time, const set<int>& seen) {
	if (cache.find({ start, time }) != cache.end()) return cache.at({ start, time });

	int best = 0;

	for (int i = 0; i < orders.size(); i++) {
		const order& o = orders.at(i);

		if (seen.find(i) == seen.end() && time + graph.at(start).at(o.from) + graph.at(o.from).at(o.to) <= o.time) {
			set<int> tmp = seen;
			tmp.insert(i);
			best = max(best, o.cost + solve(o.to, o.time, tmp));
		}
	}

	return cache[{start, time}] = best;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int n, m;
		cin >> n >> m;

		graph = vector<vector<int>>(n, vector<int>(n, inf));
		for (int j = 0; j < n; j++) graph.at(j).at(j) = 0;
		for (int j = 0; j < m; j++) {
			int from, to, cost;
			cin >> from >> to >> cost;
			graph.at(from).at(to) = cost;
			graph.at(to).at(from) = cost;
		}

		all_pair_shortest_path();

		int k;
		cin >> k;

		orders = vector<order>();
		for (int j = 0; j < k; j++) {
			int from, to, time, cost;
			cin >> from >> to >> time >> cost;
			orders.push_back({ from, to, time, cost });
		}

		cache.clear();
		cout << i << " " << solve(0, 0, set<int>()) << endl;
	}
}
