#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int inf = 1'000'000'000;

int r, k;
vector<vector<int>> kaart;

tuple<int, int, int, int> solve() {
	vector<vector<bool>> seen(r, vector<bool>(k, false));
	priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<tuple<int, int, int, int>>> queue;
	for(int i = 0; i < r; i++) queue.push({ 0, 0, -1, i });

	while (get<2>(queue.top()) != k - 1) {
		int cost, dist, x, y;
		tie(cost, dist, x, y) = queue.top();
		queue.pop();

		if (x < 0 || !seen.at(y).at(x)) {
			if(x >= 0) seen.at(y).at(x) = true;

			queue.push({ cost + kaart.at(y).at(x + 1), dist + 1, x + 1, y });
			if (x > 0) queue.push({ cost + kaart.at(y).at(x - 1), dist + 1, x - 1, y });
			if (x >= 0 && y > 0) queue.push({ cost + kaart.at(y - 1).at(x), dist + 1, x, y - 1 });
			if (x >= 0 && y < r - 1) queue.push({ cost + kaart.at(y + 1).at(x), dist + 1, x, y + 1 });
		}
	}

	return queue.top();
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> r >> k;

		kaart = vector<vector<int>>(r, vector<int>(k, 0));
		for (int j = 0; j < r; j++) {
			for (int l = 0; l < k; l++) {
				cin >> kaart.at(j).at(l);
			}
		}

		auto sol = solve();
		cout << i << " " << get<1>(sol) << " " << get<0>(sol) << endl;
	}
}
