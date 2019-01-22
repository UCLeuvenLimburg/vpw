#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

int inf = 1'000'000'000;

using vi = vector<int>;
using vvi = vector<vi>;

vvi graph;
int m, ks, ss;

vector<set<int>> result;
int best_total_distance;

void all_pair_shortest_path() {
	for (int i = 0; i < ks; i++) {
		for (int j = 0; j < ks; j++) {
			for (int k = 0; k < ks; k++) {
				graph.at(j).at(k) = min(
					graph.at(j).at(k), 
					graph.at(j).at(i) + graph.at(i).at(k));
			}
		}
	}
}

void solve(set<int> watch) {
	map<int, int> distances;
	for (int i = 0; i < ks; i++) distances[i] = inf;

	for (int i : watch){
		for (int j = 0; j < ks; j++) {
			distances.at(j) = min(distances.at(j), graph.at(i).at(j));
		}
	}

	int max_dist = max_element(distances.begin(), distances.end(), [](auto p1, auto p2) {return p1.second < p2.second; })->second;
	if (max_dist > m) return;

	int total_dist = 0;
	for (auto p : distances) total_dist += p.second;

	if (total_dist > best_total_distance) return;
	if (total_dist < best_total_distance) result.clear();
	result.push_back(watch);
	best_total_distance = total_dist;
}

void solve(int count, int index, set<int> watch) {
	if (count == 0) return solve(watch);
	
	for (int i = index; i < ks; i++) {
		watch.insert(i);
		solve(count - 1, i + 1, watch);
		watch.erase(i);
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> m >> ks >> ss;

		graph = vvi(ks, vi(ks, inf));
		for (int j = 0; j < ks; j++) {
			graph.at(j).at(j) = 0;
		}
		for (int j = 0; j < ss; j++) {
			int f, t, c;
			cin >> f >> t >> c;
			graph.at(f - 1).at(t - 1) = c;
			graph.at(t - 1).at(f - 1) = c;
		}

		all_pair_shortest_path();

		result.clear();
		best_total_distance = inf;
		for (int j = 1; j <= ks && result.size() == 0; j++) {
			solve(j, 0, set<int>());
		}
		
		vector<string> out;
		for (set<int> s : result) {
			string line = to_string(i);
			for (int j : s) {
				line += " " + to_string(j + 1);
			}
			out.push_back(line);
		}

		sort(out.begin(), out.end());

		for (string s : out) {
			cout << s << endl;
		}
	}
}
