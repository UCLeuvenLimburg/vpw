#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 1'000'000'000;

vector<int> sticks, bestanden;
vector<int> groups;

int cost() {
	vector<int> tmp = groups;
	sort(tmp.begin(), tmp.end());
	
	int lost_memory = 0;
	auto it = sticks.begin();
	for (int x : tmp) {
		it = find_if(it, sticks.end(), [x](int stick) { return stick >= x; });
		if (it == sticks.end()) return inf;
		lost_memory += *it - x;
		it++;
	}

	return lost_memory;
}

int solve(int bestand_index) {
	int current_cost = cost();
	if (current_cost == inf || bestand_index == bestanden.size()) return current_cost;

	int min = inf;

	for (int i = 0; i < groups.size(); i++) {
		groups.at(i) += bestanden.at(bestand_index);
		min = std::min(min, solve(bestand_index + 1));
		groups.at(i) -= bestanden.at(bestand_index);
	}

	{
		groups.push_back(bestanden.at(bestand_index));
		min = std::min(min, solve(bestand_index + 1));
		groups.pop_back();
	}

	return min;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int ss, bs;

		cin >> ss;
		sticks = vector<int>(ss);
		for (int j = 0; j < ss; j++) cin >> sticks.at(j);
		sort(sticks.begin(), sticks.end());

		cin >> bs;
		bestanden = vector<int>(bs);
		for (int j = 0; j < bs; j++) cin >> bestanden.at(j);

		int sol = solve(0);
		if (sol == inf) {
			cout << i << " ONMOGELIJK" << endl;
		}
		else {
			cout << i << " " << sol << endl;
		}
	}
}
