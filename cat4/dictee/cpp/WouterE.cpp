#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

using i = int;
using ii = pair<i, i>;

string zin, correct;
map<ii, i> scores;
queue<ii> todo;

void skip(ii& p) {
	while (p.first < zin.size() && p.second < correct.size() && zin.at(p.first) == correct.at(p.second)) {
		p.first++;
		p.second++;
	}
}

void push(ii old_p, ii new_p, int cost) {
	skip(new_p);

	if (scores.find(new_p) == scores.end() || scores.at(new_p) > scores.at(old_p) + cost) {
		todo.push(new_p);
		scores[new_p] = scores.at(old_p) + cost;
	}
}

int solve() {
	scores.clear();

	ii start = { 0, 0 };
	skip(start);
	scores[start] = 0;
	todo.push(start);

	while (!todo.empty()) {
		ii p = todo.front();
		todo.pop();

		if (p.first < zin.size() && p.second < correct.size()) {
			if (tolower(zin.at(p.first)) == tolower(correct.at(p.second))) {
				// Change case
				push(p, { p.first + 1, p.second + 1 }, 1);
			}
			else {	
				// Change letter
				push(p, { p.first + 1, p.second + 1 }, 2);
			}
		}

		if(p.first < zin.size()) {		
			// Delete letter
			push(p, { p.first + 1, p.second }, 2);
		}

		if(p.second < correct.size()){		
			// Add letter
			push(p, { p.first, p.second + 1 }, 2);
		}
	}

	return scores.at({ zin.size(), correct.size() });
}

int main() {
	int n;
	cin >> n;
	getline(cin, zin);

	for (int i = 1; i <= n; i++) {
		getline(cin, zin);
		getline(cin, correct);
		cout << i << " " << solve() << endl;
	}
}
