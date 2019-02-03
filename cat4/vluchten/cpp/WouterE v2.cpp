#include <iostream>
#include <vector>

using namespace std;

const int inf = 1'000'000'000;

vector<vector<int>> graph;
vector<bool> used_airplane;

vector<int*> bellman_ford(int flight) {
	vector<int> min_cost_airplane = graph.at(flight);
	vector<int> flight_to_airplane (graph.size(), -1);
	vector<int> airplane_to_flight (graph.at(0).size(), flight);

	for (int i = 0; i < min_cost_airplane.size(); i++) 
	{
		for (int a1 = 0; a1 < graph.at(0).size(); a1++) 
		{
			for (int f = 0; f < graph.size(); f++) {
				if(graph.at(f).at(a1) < 0)
				{
					for (int a2 = 0; a2 < graph.at(0).size(); a2++) {
						if (graph.at(f).at(a2) > 0 && graph.at(f).at(a2) < inf)
						{
							if (min_cost_airplane.at(a2) > min_cost_airplane.at(a1) + graph.at(f).at(a1) + graph.at(f).at(a2)) {
								min_cost_airplane.at(a2) = min_cost_airplane.at(a1) + graph.at(f).at(a1) + graph.at(f).at(a2);
								airplane_to_flight.at(a2) = f;
								flight_to_airplane.at(f) = a1;
							}
						}
					}
				}
			}
		}
	}

	int next_airplane = -1;
	int cost = inf;
	for (int i = 0; i < min_cost_airplane.size(); i++) {
		if (!used_airplane.at(i) && cost > min_cost_airplane.at(i)) {
			next_airplane = i;
			cost = min_cost_airplane.at(i);
		}
	}
	if (next_airplane == -1) return {};
	used_airplane.at(next_airplane) = true;
	
	int next_flight = airplane_to_flight.at(next_airplane);
	vector<int*> path_weights = { &graph.at(next_flight).at(next_airplane) };

	while (next_flight != flight) {
		next_airplane = flight_to_airplane.at(next_flight);
		path_weights.push_back(&graph.at(next_flight).at(next_airplane));

		next_flight = airplane_to_flight.at(next_airplane);
		path_weights.push_back(&graph.at(next_flight).at(next_airplane));
	}

	return path_weights;
}

int solve() {
	used_airplane = vector<bool>(graph.at(0).size(), false);

	int cost = 0;
	for (int i = 0; i < graph.size(); i++) {
		vector<int*> path_weights = bellman_ford(i);
		if (path_weights.size() == 0) return inf;
		
		for (int* x : path_weights) {
			cost += *x;
			*x *= -1;
		}
	}
	return cost;
}

int main() {	// Minimum-cost max-flow on bipartite graph => Max flow algorithm + Bellman Ford (to find next path)
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int fs, as;
		cin >> fs >> as;

		vector<int> flight_dist(fs, 0), airplane_dist(as, 0), flight_capacity(fs, 0), airplane_capacity(as, 0);
		for (int j = 0; j < fs; j++) cin >> flight_dist.at(j) >> flight_capacity.at(j);
		for (int j = 0; j < as; j++) cin >> airplane_dist.at(j) >> airplane_capacity.at(j);

		graph = vector<vector<int>>(fs, vector<int>(as, inf));

		for (int j = 0; j < fs; j++) {
			for (int k = 0; k < as; k++) {
				if (flight_dist.at(j) <= airplane_dist.at(k) && flight_capacity.at(j) <= airplane_capacity.at(k)) {
					graph.at(j).at(k) = flight_dist.at(j) * (airplane_capacity.at(k) - flight_capacity.at(j));
				}
			}
		}
		
		int result = solve();
		if (result == inf)	cout << i << " geen oplossing" << endl;
		else				cout << i << " " << result << endl;
	}
}
