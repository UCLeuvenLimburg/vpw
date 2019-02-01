#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

vector<bool> barman_busy;
vector<vector<int>> graph;

bool found_path_left(int index, set<int> seen);
bool found_path_right(int index, const set<int>& seen) {
	if (!barman_busy.at(index)) return barman_busy.at(index) = true;

	for (int i = 0; i < graph.size(); i++) {
		if (graph.at(i).at(index) == -1 && found_path_left(i, seen)) return graph.at(i).at(index) = 1;
	}
	return false;
}

bool found_path_left(int index, set<int> seen) {
	if (!seen.insert(index).second) return false;

	for (int i = 0; i < graph.at(index).size(); i++) {
		if (graph.at(index).at(i) == 1 && found_path_right(i, seen)) return graph.at(index).at(i) = -1;
	}
	return false;
}

bool maximum_matching_bipartite_graph(string bestelling) {		// Maximum flow problem
	if (bestelling.size() > barman_busy.size()) return false;
	for (char c : bestelling) {
		if (!found_path_left(c - 'A', set<int>())) return false;
	}
	return true;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int m;
		cin >> m;

		vector<string> barmannen(m, "");
		for (int j = 0; j < m; j++) cin >> barmannen.at(j);

		int b;
		cin >> b;

		for (int j = 0; j < b; j++) {
			string line;
			cin >> line;

			barman_busy = vector<bool>(m, false);
			graph = vector<vector<int>>(26, vector<int>(m, 0));
			for (char c : line) {
				for (int k = 0; k < m; k++) {
					if (barmannen.at(k).find(c) < barmannen.at(k).size()) {
						graph.at(c - 'A').at(k) = 1;
					}
				}
			}

			if (maximum_matching_bipartite_graph(line)) {
				cout << line << " mogelijk" << endl;
			}
			else {
				cout << line << " onmogelijk" << endl;
			}
		}
	}
}
