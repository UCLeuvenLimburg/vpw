#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <map>

using namespace std;

vector<vector<pair<int, int>>> dozen;
map<tuple<int, int, int>, int> cache;

int solve(int start, int eind, int lengte) {
	if (cache.find({ start, eind, lengte }) != cache.end()) return cache.at({ start, eind, lengte });

	int max = start == eind ? lengte : 0;
	if (lengte == dozen.size()) return cache[{ start, eind, lengte }] = max;
	
	for (auto p : dozen.at(lengte)) {
		if (eind == p.first) {
			max = std::max(max, solve(start, p.second, lengte + 1));
		}
	}

	return cache[{ start, eind, lengte }] = max;
}

int solve() {
	cache.clear();
	int max = 0;
	for (auto p : dozen.front()) {
		max = std::max(max, solve(p.first, p.second, 1));
	}
	return max;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int d, b;
		cin >> d >> b;

		dozen.clear();
		for (int j = 0; j < d; j++) {
			vector<pair<int, int>> doos;
			for (int k = 0; k < b; k++) {
				int a, b;
				cin >> a >> b;
				doos.push_back({ a, b });
				doos.push_back({ b, a });
			}
			dozen.push_back(doos);
		}

		cout << solve() << endl;
	}
}
