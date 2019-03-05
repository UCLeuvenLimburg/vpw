#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct Code { string letters, code; };

string solve(string target, vector<Code> codes) {	// Breadth first search
	set<string> seen;
	queue<Code> todo;
	todo.push({ "", "" });
	
	while (!todo.empty() && todo.front().code != target) {
		Code current = todo.front();
		todo.pop();

		for (Code c : codes) {
			string candidate = current.code + c.code;
			if (candidate == target.substr(0, candidate.size()) && seen.find(candidate) == seen.end()) {
				todo.push({ current.letters + c.letters, current.code + c.code });
				seen.insert(candidate);
			}
		}
	}

	if (todo.empty()) return "ONMOGELIJK";

	return todo.front().letters;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		string code;
		cin >> code;

		int cc;
		cin >> cc;

		vector<Code> codes;
		for (int a = 0; a < cc; a++) {
			string letter, code;
			cin >> letter >> code;
			codes.push_back({ letter, code });
		}

		sort(codes.begin(), codes.end(), [](Code a, Code b) { return a.letters < b.letters; });

		cout << i << " " << solve(code, codes) << endl;
	}
}
