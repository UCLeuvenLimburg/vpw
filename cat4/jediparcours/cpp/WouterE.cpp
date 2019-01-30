#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int inf = 1'000'000;

using vi = vector<int>;
struct iii { int from, to, weight; };
using viii = vector<iii>;

int Vs, Es;
viii edges;
vi distances;

void bellman_ford() {
	for (int k = 0; k < Vs - 1; k++) {
		for (iii e : edges) {
			distances.at(e.to) = std::min(distances.at(e.to), distances.at(e.from) + e.weight);
		}
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> Vs >> Es;

		edges.clear();
		for (int k = 0; k < Es; k++) {
			int from, to, weight;
			cin >> from >> to >> weight;
			edges.push_back({ from - 1, to - 1, weight });
		}

		distances = vi(Vs, inf);
		distances.at(0) = 0;

		bellman_ford();
		int result = distances.back();
		bellman_ford();

		if (result != distances.back())	cout << i << " min oneindig" << endl;
		else if (result > inf / 2)		cout << i << " plus oneindig" << endl;
		else							cout << i << " " << result << endl;
	}
}
