#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int start, count;
		cin >> start >> count;

		vector<int> ds;
		for (int j = 0; j < count; j++) {
			int x;
			cin >> x;
			ds.push_back(x);
		}

		sort(ds.begin(), ds.end());

		for (int x : ds) {
			start += x;
			if (start < 0) start -= 35;
		}

		cout << i << " " << start << endl;
	}
}
