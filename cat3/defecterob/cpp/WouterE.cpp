#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <map>

using namespace std;

string solve(string fout, string correct) {			// Breadth-first search
	map<string, string> seen;
	queue<string> todo;
	seen[fout] = "";
	todo.push(fout);

	while (todo.front() != correct) {
		string s = todo.front();
		todo.pop();

		for (int i = 0; i < s.size(); i++) {
			if (s.at(i) != correct.at(i))
			{
				for (int j = i + 1; j < s.size(); j++) {
					if (s.at(j) != correct.at(j) && (s.at(i) == correct.at(j) || s.at(j) == correct.at(i)))
					{
						string x = s;
						swap(x.at(i), x.at(j));

						string ops = (seen.at(s) + (char)('A' + i)) + (char)('A' + j);

						if (seen.find(x) == seen.end() || (ops.size() == seen.at(x).size() && ops < seen.at(x))) {
							seen[x] = ops;
							todo.push(x);
						}
					}
				}
			}
		}
	}

	return seen.at(correct);
}

int main() {
	int nr;
	cin >> nr;

	for (int i = 1; i <= nr; i++) {
		string fout, correct;
		cin >> fout >> correct;

		if (fout == correct) {
			cout << i << " correct" << endl;
		}
		else if (
			count(fout.begin(), fout.end(), 'S') != count(correct.begin(), correct.end(), 'S') ||
			count(fout.begin(), fout.end(), 'L') != count(correct.begin(), correct.end(), 'L') ||
			count(fout.begin(), fout.end(), 'R') != count(correct.begin(), correct.end(), 'R')
			) {
			cout << i << " onmogelijk" << endl;
		}
		else {
			cout << i << " " << solve(fout, correct) << endl;
		}
	}
}
