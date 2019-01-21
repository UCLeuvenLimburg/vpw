#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct ii { int size, cost; };
using vii = vector<ii>;

vii dozen;
map<int, int> cache;

int solve(int count) {
	if (count <= 0) return 0;
	if (cache.find(count) != cache.end()) return cache.at(count);

	int min = 1'000'000'000;

	for (ii doos : dozen) {
		int cost = doos.cost + solve(count - doos.size);
		if (cost < min) min = cost;
	}

	cache[count] = min;
	return min;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int cs, ds;
		cin >> cs >> ds;

		dozen.clear();
		for (int j = 0; j < ds; j++) {
			int a, b;
			cin >> a >> b;
			dozen.push_back({ a, b });
		}

		cache.clear();
		cout << i << " " << solve(cs) << endl;
	}
}
