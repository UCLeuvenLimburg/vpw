#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

const int inf = 1'000'000'000;

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		string naam;
		int aantal;
		cin >> naam >> aantal;

		int sum = 0;
		map<char, int> data;
		for (int j = 0; j < aantal; j++) {
			char c;
			int stemmen;
			cin >> c >> stemmen;
			data[c] = stemmen;
			sum += stemmen;
		}

		int target = sum / 2 + 1;
		int best = inf;
		set<string> result;
		map<string, int> current, next;
		current[""] = 0, next[""] = 0;

		for (auto p1 : data) {
			for (auto p2 : current) {
				if (p1.second + p2.second < target) {
					next[p2.first + p1.first] = p1.second + p2.second;
				}
				else if(p1.second + p2.second < best) {
					best = p1.second + p2.second;
					result.clear();
					result.insert(p2.first + p1.first);
				}
				else if (p1.second + p2.second == best) {
					result.insert(p2.first + p1.first);
				}
			}

			current = next;
		}

		cout << naam;
		for (string s : result) cout << " " << s;
		cout << endl;
	}
}
