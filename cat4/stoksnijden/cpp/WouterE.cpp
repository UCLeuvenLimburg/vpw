#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;

		vector<int> lengtes(k, 0);
		for (int j = 0; j < k; j++) cin >> lengtes.at(k - j - 1);

		int cost = 0;
		while (lengtes.size() > 1) {
			int sum = lengtes.at(lengtes.size() - 1) + lengtes.at(lengtes.size() - 2);
			lengtes.pop_back();
			lengtes.pop_back();

			cost += sum;
			lengtes.insert(lower_bound(lengtes.rbegin(), lengtes.rend(), sum).base(), sum);
		}

		cout << i << " " << cost << endl;
	}
}
