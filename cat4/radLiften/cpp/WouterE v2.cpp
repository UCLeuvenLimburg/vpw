#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using vi = vector<int>;
struct path { int cost; vi koker, verdiep; };
struct lift { int cost, koker, verdiep; };

bool operator > (const path& l, const path& r) {
	if (l.cost != r.cost) return l.cost > r.cost;
	if (l.koker.size() != r.koker.size()) return l.koker.size() > r.koker.size();
	if (l.koker != r.koker) return l.koker > r.koker;
	return l.verdiep > r.verdiep;
}

path solve(vector<vector<lift>> liften, int start, int target) {		// Dijkstra
	vector<bool> seen(liften.size(), false);
	priority_queue<path, vector<path>, greater<path>> open;
	open.push(path{ 0, vi{-1}, vi{start} });

	while (open.top().verdiep.back() != target) {
		path p = open.top();
		open.pop();

		if (!seen.at(p.verdiep.back())) {
			seen.at(p.verdiep.back()) = true;

			for (lift l : liften.at(p.verdiep.back())) {
				path tmp = p;
				tmp.cost += l.cost;
				tmp.koker.push_back(l.koker);
				tmp.verdiep.push_back(l.verdiep);

				open.push(tmp);
			}
		}
	}

	return open.top();
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int vs, ls;
		cin >> vs >> ls;

		vector<vector<lift>> liften(vs, vector<lift>());
		for (int j = 0; j < ls; j++) {
			int s, e, d;
			cin >> s >> e >> d;

			for (int from = s; from <= e; from += d) {
				for (int to = s; to <= e; to += d) {
					if (from < to) liften.at(from).push_back(lift{ (to - from) / d, 2 * j + 1, to });
					if (from > to) liften.at(from).push_back(lift{ (from - to) / d, 2 * j + 2, to });
				}
			}
		}

		int start, target;
		cin >> start >> target;

		path sol = solve(liften, start, target);

		cout << i << " ";
		for (int j = 1; j < sol.koker.size(); j++) {
			cout << "(" << sol.koker.at(j) << "," << sol.verdiep.at(j) << ")";
		}
		cout << endl;
	}
}
