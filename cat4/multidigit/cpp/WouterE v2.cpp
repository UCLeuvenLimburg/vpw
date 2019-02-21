#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int inf = 1'000'000'000;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int c, target;

		cin >> c;
		vector<int> cijfers(c, 0);
		for (int j = 0; j < c; j++) cin >> cijfers.at(j);

		cin >> target;
		vector<int> dp(target + 1, inf);

		for (int x : cijfers) {
			int getal = x, cost = 1;
			while (getal <= target) {
				dp.at(getal) = cost;
				getal = getal * 10 + x;
				cost++;
			}
		}

		for (int b = 0; b <= target; b++) {
			for (int a = 1; a <= b / 2; a++) {
				dp.at(b) = min(dp.at(b), dp.at(a) + dp.at(b - a));
			}
			for (int a = 2; a * a <= b; a++) {
				if (b % a == 0) {
					dp.at(b) = min(dp.at(b), dp.at(a) + dp.at(b / a));
				}
			}
		}
		
		if (dp.at(target) == inf) cout << 0 << endl;
		else cout << dp.at(target) << endl;
	}
}
