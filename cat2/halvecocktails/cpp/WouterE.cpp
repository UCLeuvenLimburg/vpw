#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct ii { int t1, t2; };

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int m;
		cin >> m;

		map<int, ii> data;
		for (int j = 0; j < m; j++) {
			char c;
			int t1, t2;
			cin >> c >> t1 >> t2;
			data[c] = { t1, t2 };
		}

		int a;
		cin >> a;

		vector<ii> todo;
		for (int j = 0; j < a; j++) {
			char c;
			cin >> c;
			todo.push_back(data.at(c));
		}

		sort(todo.begin(), todo.end(), [](auto p1, auto p2) {
			int left = p1.t1 + max(p2.t1, p1.t2) + p2.t2;
			int right = p2.t1 + max(p1.t1, p2.t2) + p1.t2;
			return left < right || (left == right && p1.t1 < p2.t1);
		});

		int t1 = 0, t2 = 0;
		for (auto p : todo) {
			t1 += p.t1;
			t2 = max(t1, t2) + p.t2;
		}

		cout << i << " " << t2 << endl;
	}
}
