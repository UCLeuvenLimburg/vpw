#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct ii { int koker, verdiep; };
using vii = vector<ii>;

struct lift { int start, eind, step; };
using vl = vector<lift>;

vii solve(vl liften, int start, int target) {		// Breadth first search
	vector<vii> current, next;
	set<int> done, next_done;
	current.push_back(vector<ii>(1, { -1, start }));

	while (all_of(current.begin(), current.end(), [target](const vii& p) { return p.back().verdiep != target; })) {
		for (const vii& path : current) {
			int back = path.back().verdiep;

			for (int i = 0; i < liften.size(); i++) {
				lift& l = liften.at(i);

				if ((back - l.start) % l.step == 0) {
					int up = back + l.step;
					if (l.start <= back && up <= l.eind && done.find(up) == done.end()) {
						vii tmp = path;
						tmp.push_back({ 2 * i + 1, up });
						next.push_back(tmp);
						next_done.insert(up);
					}

					int down = back - l.step;
					if (l.start <= down && back <= l.eind && done.find(down) == done.end()) {
						vii tmp = path;
						tmp.push_back({ 2 * i + 2, down });
						next.push_back(tmp);
						next_done.insert(down);
					}
				}
			}
		}

		current = next;
		done.insert(next_done.begin(), next_done.end());
	}

	current.erase(remove_if(current.begin(), current.end(), [target](const vii& p) { return p.back().verdiep != target; }), current.end());

	for (vii& path : current) {
		path.erase(path.begin());

		for (int i = 0; i + 1 < path.size();) {
			if (path.at(i).koker == path.at(i + 1).koker) path.erase(path.begin() + i);
			else i++;
		}
	}

	sort(current.begin(), current.end(), [](vii& l, vii& r) {
		if (l.size() != r.size()) {
			return l.size() < r.size();
		}
		else {
			for (int i = 0; i < l.size(); i++) {
				if (l.at(i).koker != r.at(i).koker) {
					return l.at(i).koker < r.at(i).koker;
				}
			}
			for (int i = 0; i < l.size(); i++) {
				if (l.at(i).verdiep != r.at(i).verdiep) {
					return l.at(i).verdiep < r.at(i).verdiep;
				}
			}
			return false;
		}
	});

	return current.front();
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int vs, ls;
		cin >> vs >> ls;

		vl liften;
		for (int j = 0; j < ls; j++) {
			int s, e, d;
			cin >> s >> e >> d;
			liften.push_back({ s, e, d });
		}

		int start, target;
		cin >> start >> target;

		vii sol = solve(liften, start, target);

		cout << i << " ";
		for (ii a : sol) cout << "(" << a.koker << "," << a.verdiep << ")";
		cout << endl;
	}
}
