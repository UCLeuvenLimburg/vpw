#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int inf = 1'000'000'000;

vector<int> tocht;
vector<vector<int>> graph;

void all_pair_shortest_path() {
	for (int i = 0; i < graph.size(); i++) {
		for (int a = 0; a < graph.size(); a++) {
			for (int b = 0; b < graph.size(); b++) {
				graph.at(a).at(b) = min(graph.at(a).at(b), graph.at(a).at(i) + graph.at(i).at(b));
			}
		}
	}
}

int solve(int position, int time, const set<int>& todo_voetbal, int index_tocht) {
	if (index_tocht == tocht.size()) {
		if (todo_voetbal.size() == 0) return -1;
		else return -inf;
	}

	int max = -inf;

	for (int x : todo_voetbal) {
		set<int> tmp = todo_voetbal;
		tmp.erase(x);
		max = std::max(max, solve(x, time + graph.at(position).at(x), tmp, index_tocht));
	}

	for (int i = index_tocht; i < tocht.size(); i++) {
		if (time + graph.at(position).at(tocht.at(i)) <= i + 1) {
			max = std::max(max, solve(tocht.at(i), i + 1, todo_voetbal, i + 1) + 1);
		}
	}

	return max;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int ss, start, eind, c;
		cin >> ss >> start >> eind >> c;
		start--, eind--;

		tocht = vector<int>(c + 1, 0);
		for (int j = 0; j < c; j++) {
			int x;
			cin >> x;
			tocht.at(j) = x - 1;
		}
		tocht.at(c) = eind;

		int v;
		cin >> v;

		set<int> todo_voetbal;
		for (int j = 0; j < v; j++) {
			int x;
			cin >> x;
			todo_voetbal.insert(x - 1);
		}

		int l;
		cin >> l;

		graph = vector<vector<int>>(ss, vector<int>(ss, inf));
		for (int j = 0; j < ss; j++) graph.at(j).at(j) = 0;
		for (int j = 0; j < l; j++) {
			int a, b;
			cin >> a >> b;
			graph.at(a - 1).at(b - 1) = 1;
			graph.at(b - 1).at(a - 1) = 1;
		}

		all_pair_shortest_path();

		int result = solve(start, 0, todo_voetbal, 0);
		if (result < 0)		cout << i << " onmogelijk" << endl;
		else				cout << i << " " << result << endl;
	}
}
