#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct B { long long nr, d, k; };

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int bs;
		cin >> bs;

		vector<B> bestel;
		for (int j = 0; j < bs; j++) {
			int d, k;
			cin >> d >> k;
			bestel.push_back({ j + 1LL, d, k });
		}

		sort(bestel.begin(), bestel.end(), [](B a, B b) {
			return a.d * b.k < a.k * b.d || (a.d * b.k == a.k * b.d && a.nr < b.nr);
		});

		cout << i;
		for (B a : bestel) {
			cout << " " << a.nr;
		}
		cout << endl;
	}
}
