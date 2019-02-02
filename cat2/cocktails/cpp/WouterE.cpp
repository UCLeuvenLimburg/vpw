#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool assign_cocktail_to_barman(int cocktail, vector<bool>& seen, vector<int>& barman_busy, const vector<vector<int>>& graph) {
	for (int barman : graph.at(cocktail)) {
		if (!seen.at(barman)) {
			seen.at(barman) = true;

			if (barman_busy.at(barman) < 0 || assign_cocktail_to_barman(barman_busy.at(barman), seen, barman_busy, graph)) {
				barman_busy.at(barman) = cocktail;
				return true;
			}
		}
	}
	return false;
}

bool maximum_matching_bipartite_graph(const string& bestelling, vector<int> barman_busy, const vector<vector<int>>& graph) {
	if (bestelling.size() > barman_busy.size()) return false;
	for (char c : bestelling) {
		vector<bool> seen(barman_busy.size(), false);
		if (!assign_cocktail_to_barman(c - 'A', seen, barman_busy, graph)) return false;
	}
	return true;
}

int main() {				// Maximum flow problem
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int m;
		cin >> m;

		vector<int> barman_busy = vector<int>(m, -1);
		vector<vector<int>> graph = vector<vector<int>>(26, vector<int>());
		for (int k = 0; k < m; k++) {
			string str;
			cin >> str;

			for (char c : str) {
				graph.at(c - 'A').push_back(k);
			}
		}

		int b;
		cin >> b;

		for (int j = 0; j < b; j++) {
			string line;
			cin >> line;

			if (maximum_matching_bipartite_graph(line, barman_busy, graph)) {
				cout << line << " mogelijk" << endl;
			}
			else {
				cout << line << " onmogelijk" << endl;
			}
		}
	}
}
