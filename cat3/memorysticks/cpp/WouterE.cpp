#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

const int inf = 1'000'000'000;

multiset<int> sticks;
vector<int> bestanden;
map<multiset<int>, int> cache;

int solve(int bi, multiset<int> s) {
	if (cache.find(s) != cache.end()) return cache.at(s);

	if (bi == bestanden.size()) {
		vector<int> leftover(s.size(), 0);
		set_difference(s.begin(), s.end(), sticks.begin(), sticks.end(), leftover.begin());
		return cache[s] = accumulate(leftover.begin(), leftover.end(), 0);
	}

	int min = inf;
	int x = bestanden.at(bi);

	for (auto it = s.lower_bound(x); it != s.end(); it = s.upper_bound(*it)) {
		multiset<int> tmp_s = s;
		tmp_s.erase(tmp_s.find(*it));
		if (*it > x) tmp_s.insert(*it - x);
			
		min = std::min(min, solve(bi + 1, tmp_s));
	}

	return cache[s] = min;
}

int main() {
	int n; 
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int ss;
		cin >> ss;

		sticks.clear();
		for (int j = 0; j < ss; j++) {
			int x;
			cin >> x;
			sticks.insert(x);
		}

		int bs;
		cin >> bs;

		bestanden.clear();
		for (int j = 0; j < bs; j++) {
			int x;
			cin >> x;
			bestanden.push_back(x);
		}

		cache.clear();
		int sol = solve(0, sticks);

		if (sol == inf) {
			cout << i << " ONMOGELIJK" << endl;
		}
		else {
			cout << i << " " << sol << endl;
		}
	}
}
