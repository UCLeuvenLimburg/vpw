#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
struct iii { int from, to, weight; };
using viii = vector<iii>;

int inf = 1'000'000;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int Vs, Es;
		cin >> Vs >> Es;

		viii edges;

		for (int k = 0; k < Es; k++) {
			int from, to, weight;
			cin >> from >> to >> weight;
			edges.push_back({ from - 1, to - 1, weight });
		}

		vi distances(Vs, inf);
		distances.at(0) = 0;

		// Bellman - Ford shortest path algorithm
		for (int k = 0; k < Vs - 1; k++) {
			for (iii e : edges) {
				if (distances.at(e.from) < inf && distances.at(e.from) + e.weight < distances.at(e.to))
				{
					distances.at(e.to) = distances.at(e.from) + e.weight;
				}
			}
		}

		int result = distances.back();

		// Run Bellman - Ford again to detect negative cycle that influences end node
		for (int k = 0; k < Vs - 1; k++) {
			for (iii e : edges) {
				if (distances.at(e.from) < inf && distances.at(e.from) + e.weight < distances.at(e.to))
				{
					distances.at(e.to) = distances.at(e.from) + e.weight;
				}
			}
		}

		if (result != distances.back())
		{
			cout << i << " min oneindig" << endl;
		}
		else if (result == inf) {
			cout << i << " plus oneindig" << endl;
		}
		else {
			cout << i << " " << result << endl;
		}
	}
}
