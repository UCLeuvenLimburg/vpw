#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int m;
		cin >> m;

		int dist = 0;
		int x = 0, y = 0, x2, y2;
		for (int j = 0; j < m; j++) {
			cin >> x2 >> y2;
			dist += abs(x2 - x) + abs(y2 - y);
			y = y2, x = x2;
		}

		cout << i << " " << dist << endl;
	}
}
