#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const int inf = 1'000'000'000;
const int max_length = 33;
map<int64_t, int> cache;

int lowest_set_unique_bit(int64_t field) {
	if (field & (field - 1)) return inf;
	int index = 0;
	while (!(field & (1LL << index))) index++;
	return index + 1;
}

int solve(int64_t field) {
	if (cache.find(field) != cache.end()) return cache.at(field);
	if (!(field & (field >> 1))) return cache[field] = lowest_set_unique_bit(field);

	int min = inf;
	for (int64_t jumps : { 
		(field >> 1) & field & ~(field << 1), 
		(field << 1) & field & ~(field >> 1) 
	}) {
		for (int i = 1; i < max_length - 1; i++) {
			if (jumps & (1LL << i)) {
				min = std::min(min, solve(field ^ (7LL << (i - 1))));
			}
		}
	}
	return cache[field] = min;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int l;
		cin >> l;

		int64_t field = 0;
		for (int j = 0; j < l; j++) {
			int64_t x;
			cin >> x;
			field |= x << j;
		}

		int sol = solve(field);
		if (sol > l) cout << i << " ONMOGELIJK" << endl;
		else cout << i << " " << sol << endl;
	}
}
