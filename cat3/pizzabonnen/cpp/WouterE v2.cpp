#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int inf = 1'000'000'000;

vector<int> pizzas;
vector<vector<int>> bonnen;
int min_cost;

void solve(int index, int current_cost) {
	if (current_cost >= min_cost) return;
	if (index >= pizzas.size()) {
		min_cost = current_cost;
		return;
	}

	min_cost = min(min_cost, current_cost + pizzas.back() - pizzas.at(index));
	
	for (int i = 0; i < bonnen.size(); i++) {
		if (!bonnen.at(i).empty() && index + bonnen.at(i).back() < pizzas.size()) {
			int tmp = bonnen.at(i).back();
			bonnen.at(i).pop_back();

			solve(index + i, current_cost + pizzas.at(index + tmp) - pizzas.at(index));

			bonnen.at(i).push_back(tmp);
		}
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int ps;
		cin >> ps;

		pizzas = vector<int>(ps);
		for (int j = 0; j < ps; j++) cin >> pizzas.at(j);
		sort(pizzas.rbegin(), pizzas.rend());
		pizzas.insert(pizzas.begin(), 0);
		for (int j = 1; j < ps + 1; j++) pizzas.at(j) += pizzas.at(j - 1);

		int bs;
		cin >> bs;

		bonnen = vector<vector<int>>(40 + 1);
		for (int j = 0; j < bs; j++) {
			int a, b;
			cin >> a >> b;
			bonnen.at(a + b).push_back(a);
		}

		for (auto& v : bonnen) sort(v.rbegin(), v.rend());

		min_cost = inf;
		solve(0, 0);
		cout << i << " " << min_cost << endl;
	}
}
