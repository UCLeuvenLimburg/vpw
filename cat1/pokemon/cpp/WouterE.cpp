#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n; 

	for (int i = 1; i <= n; i++) {
		int a, v, u;
		cin >> a >> v >> u;
		cout << i << " " << max(10, (int)(a * sqrt(v * u) * 0.7903 * 0.7903 / 10)) << endl;
	}
}
