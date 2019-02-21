#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int inf = 1'000'000'000;

int fs, as;
vector<vector<int>> cost;
map<int, int> used_airplane_to_flight;

int bellman_ford(int target_flight) {
	vector<int> min_cost_airplane = cost.at(target_flight);
	vector<int> assign_airplane_to_flight (as, target_flight);
	vector<int> remove_flight_from_airplane (fs, -1);

	for (auto dummy : used_airplane_to_flight) {
		for (auto p : used_airplane_to_flight) {
			int a1 = p.first, f = p.second;

			for (int a2 = 0; a2 < as; a2++) {
				if (min_cost_airplane.at(a2) > min_cost_airplane.at(a1) - cost.at(f).at(a1) + cost.at(f).at(a2)) {
					min_cost_airplane.at(a2) = min_cost_airplane.at(a1) - cost.at(f).at(a1) + cost.at(f).at(a2);
					assign_airplane_to_flight.at(a2) = f;
					remove_flight_from_airplane.at(f) = a1;
				}
			}
		}
	}

	for (auto p : used_airplane_to_flight) min_cost_airplane.at(p.first) = inf;

	int airplane = min_element(min_cost_airplane.begin(), min_cost_airplane.end()) - min_cost_airplane.begin();
	int assign_cost = min_cost_airplane.at(airplane);
	
	while (airplane != -1) {
		int flight = assign_airplane_to_flight.at(airplane);
		used_airplane_to_flight[airplane] = flight;
		airplane = remove_flight_from_airplane.at(flight);
	}

	return assign_cost;
}

int solve() {
	used_airplane_to_flight.clear();

	int total_cost = 0;
	for (int i = 0; i < fs; i++) {
		total_cost += bellman_ford(i);
		if (total_cost >= inf) return inf;
	}
	return total_cost;
}

int main() {	// Minimum-cost max-flow (on bipartite graph) => Max flow algorithm + Bellman Ford (to find next path)
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> fs >> as;

		vector<int> flight_dist(fs, 0), airplane_dist(as, 0), flight_capacity(fs, 0), airplane_capacity(as, 0);
		for (int j = 0; j < fs; j++) cin >> flight_dist.at(j) >> flight_capacity.at(j);
		for (int j = 0; j < as; j++) cin >> airplane_dist.at(j) >> airplane_capacity.at(j);

		cost = vector<vector<int>>(fs, vector<int>(as, inf));
		for (int j = 0; j < fs; j++) {
			for (int k = 0; k < as; k++) {
				if (flight_dist.at(j) <= airplane_dist.at(k) && flight_capacity.at(j) <= airplane_capacity.at(k)) {
					cost.at(j).at(k) = flight_dist.at(j) * (airplane_capacity.at(k) - flight_capacity.at(j));
				}
			}
		}
		
		int result = solve();
		if (result == inf)	cout << i << " geen oplossing" << endl;
		else				cout << i << " " << result << endl;
	}
}
