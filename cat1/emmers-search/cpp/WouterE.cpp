#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int target, aantal;
multiset<pair<int, int>> emmers;

int solve() {
	set<multiset<pair<int, int>>> seen, todo, next_todo;
	todo.insert(emmers);

	int result = 0;

	while (!todo.empty()) {
		for (auto v : todo) {
			auto best = v.lower_bound({ target, 0 });
			if (best != v.end() && best->first == target) return result;

			for (auto it1 = v.begin(); it1 != v.end(); it1 = v.upper_bound(*it1)) {
				for (auto it2 = v.begin(); it2 != v.end(); it2 = v.upper_bound(*it2)) {
					if (it1 != it2) {
						auto value1 = *it1;
						auto value2 = *it2;
						v.erase(it1);
						v.erase(it2);

						int dif = min(value1.second, value1.first + value2.first) - value1.first;
						pair<int, int> new1 = { value1.first + dif, value1.second };
						pair<int, int> new2 = { value2.first - dif, value2.second };
						auto tmp1 = v.insert(new1);
						auto tmp2 = v.insert(new2);

						if (seen.find(v) == seen.end()) {
							seen.insert(v);
							next_todo.insert(v);
						}

						v.erase(tmp1);
						v.erase(tmp2);
						it1 = v.insert(value1);
						it2 = v.insert(value2);
					}
				}
			}
		}

		result++;
		todo = next_todo;
		next_todo.clear();
	}

	return -1;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> target >> aantal;

		emmers.clear();
		for (int j = 0; j < aantal; j++) {
			int i, c;
			cin >> i >> c;
			emmers.insert({ i, c });
		}

		int sol = solve();
		if (sol == -1) {
			cout << i << " ONMOGELIJK" << endl;
		}
		else {
			cout << i << " " << sol << endl;
		}
	}
}
