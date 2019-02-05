#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int e;
		cin >> e;
		
		vector<int> inhoud(e, 0), capaciteit(e, 0);
		for (int j = 0; j < e; j++) cin >> inhoud.at(j) >> capaciteit.at(j);

		int q;
		cin >> q;

		for (int j = 0; j < q; j++) {
			int from, to;
			cin >> from >> to;
			from--, to--;

			int diff = min(capaciteit.at(to), inhoud.at(from) + inhoud.at(to)) - inhoud.at(to);
			inhoud.at(from) -= diff;
			inhoud.at(to) += diff;
		}

		cout << i;
		for (int x : inhoud) cout << " " << x;
		cout << endl;
	}
}
