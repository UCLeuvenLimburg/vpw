#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

using ii = pair<int, int>;
using vi = vector<int>;

map<ii, int> cache;

int find_maximum(const vi& pizza, int left, int right) {
	if ((left + 1) % pizza.size() == right) {
		return 0;
	}

	if (cache.find({ left, right }) != cache.end()) {
		return cache.at({ left, right });
	}

	int total = 0;
	for (int i = right; i != (left + 1) % pizza.size(); i = (i + 1) % pizza.size()) {
		total += pizza.at(i);
	}
	
	int min_other = min(
		find_maximum(pizza, (left - 1 + pizza.size()) % pizza.size(), right),
		find_maximum(pizza, left, (right + 1) % pizza.size())
	);

	cache[{left, right}] = total - min_other;
	return total - min_other;
}

int solve(const vi& pizza) {
	int total = 0;
	for (int a : pizza) total += a;

	int min_bob = total;
	
	for (int i = 0; i < pizza.size(); i++) {
		int max = find_maximum(pizza, (i - 1 + pizza.size()) % pizza.size(), (i + 1) % pizza.size());
		if (max < min_bob) min_bob = max;
	}

	return total - min_bob;
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int c;
		cin >> c;

		vi pizza;
		for (int k = 0; k < c; k++) {
			int slice;
			cin >> slice;
			pizza.push_back(slice);
		}

		cache.clear();
		cout << solve(pizza) << endl;
	}
}
