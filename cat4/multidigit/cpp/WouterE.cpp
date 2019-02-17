#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int inf = 1'000'000'000;

vector<int> cijfers;
vector<int> cache;

int cost(int target) {
	if (cache.at(target) >= 0) return cache.at(target);

	int best = inf;

	for (int i = 2; i * i <= target; i++) {
		if (target % i == 0) {
			best = min(best, cost(i) + cost(target / i));
		}
	}

	for (int i = 1; i <= target / 2; i++) {
		best = min(best, cost(i) + cost(target - i));
	}

	return cache.at(target) = best;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int c, target;

		cin >> c;
		cijfers = vector<int>(c, 0);
		for (int j = 0; j < c; j++) cin >> cijfers.at(j);

		cin >> target;
		cache = vector<int>(target + 1, -1);

		for (int x : cijfers) {
			int getal = x, cost = 1;
			while (getal <= target) {
				cache.at(getal) = cost;
				getal = getal * 10 + x;
				cost++;
			}
		}

		int sol = cost(target);
		if(sol == inf) cout << 0 << endl;
		else cout << sol << endl;
	}
}
