#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int inf = 1'000'000'000;

struct ii { int a, b; };
using vi = vector<int>;
using vii = vector<ii>;
using vb = vector<bool>;

map<vb, int> cache;
vi pizzas;
vii bonnen;

int solve(vb used, int bought) {
	if (cache.find(used) != cache.end()) return cache.at(used);
	if (bought >= pizzas.size()) return 0;
	if (all_of(used.begin(), used.end(), [](bool b) {return b; })) {
		int sum = 0;
		for (int i = bought; i < pizzas.size(); i++) sum += pizzas.at(i);
		return sum;
	}

	int min = inf;

	for (int i = 0; i < bonnen.size(); i++) {
		if (!used.at(i))
		{
			used.at(i) = true;
			int cost = solve(used, bought + bonnen.at(i).a + bonnen.at(i).b);
			used.at(i) = false;
			
			for (int j = bought; j < pizzas.size() && j < bought + bonnen.at(i).a; j++) cost += pizzas.at(j);
			if (cost < min) min = cost;
		}
	}

	cache[used] = min;
	return min;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int ps;
		cin >> ps;

		pizzas.clear();
		for (int j = 0; j < ps; j++) {
			int x;
			cin >> x;
			pizzas.push_back(x);
		}

		int bs;
		cin >> bs;

		bonnen.clear();
		for (int j = 0; j < bs; j++) {
			int a, b;
			cin >> a >> b;
			bonnen.push_back({ a, b });
		}

		sort(pizzas.rbegin(), pizzas.rend());

		cache.clear();
		cout << i << " " << solve(vb(bs, false), 0) << endl;
	}
}
