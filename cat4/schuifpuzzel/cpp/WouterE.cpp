#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct ii { int x, y; };

int r, k;

int solve(const string& current, const string& target) {		// Breadth-first search
	vector<string> todo, next_todo;
	set<string> seen;
	todo.push_back(current);

	int result = 0;

	while (!todo.empty()) {
		for (const string& s : todo) {
			if (s == target) return result;

			int index = s.find(' ');
			int x = index % k, y = index / k;

			for (ii p : { ii{ x - 1, y }, ii{ x + 1, y }, ii{ x, y - 1 }, ii{ x, y + 1 }}) {
				if (p.x >= 0 && p.x < k && p.y >= 0 && p.y < r) {
					string tmp = s;
					swap(tmp.at(y * k + x), tmp.at(p.y * k + p.x));

					if (seen.insert(tmp).second) next_todo.push_back(tmp);
				}
			}
		}

		result++;
		todo = next_todo;
		next_todo.clear();
	}

	return -1;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> r >> k;
		
		string dummy, begin, eind;
		getline(cin, dummy);
		getline(cin, begin);
		getline(cin, eind);

		cout << solve(begin, eind) << endl;;
	}
}
