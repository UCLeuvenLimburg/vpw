#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int cards_per_person, card_count;
vector<set<int>> niet;
vector<set<set<int>>> wel;

vector<set<int>> result;
vector<bool> used;

bool possible(int pp) {
	for (int x : niet.at(pp)) {
		if (result.at(pp).find(x) != result.at(pp).end()) return false;
	}

	for (auto s : wel.at(pp)) {
		if (all_of(s.begin(), s.end(), [pp](char c) { return result.at(pp).find(c) == result.at(pp).end(); })) return false;
	}

	return true;
}

bool solve(int count, int index, int persoon) {
	if (persoon == 4) return true;
	if (count == cards_per_person) return possible(persoon) && solve(0, 0, persoon + 1);

	for (int x = index; x < card_count; x++) {
		if (!used.at(x)) {
			used.at(x) = true;
			auto it = result.at(persoon).insert(x).first;

			if (solve(count + 1, x + 1, persoon)) return true;

			result.at(persoon).erase(it);
			used.at(x) = false;
		}
	}

	return false;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int p, l, w, vs;
		cin >> p >> l >> w >> vs;

		card_count = p + l + w;
		cards_per_person = (card_count - 3) / 4;

		niet = vector<set<int>>(4);
		wel = vector<set<set<int>>>(4);

		for (int j = 0; j < vs; j++) {
			char from, persoon, locatie, wapen, to;
			cin >> from >> persoon >> locatie >> wapen >> to;

			int index = from - '1';
			int pp = persoon - '1';
			int ll = locatie - 'A' + p;
			int ww = wapen - 'a' + p + l;
			int end = to - '1';

			for (int k = (index + 1) % 4; k != index && k != end; k = (k + 1) % 4) {
				niet.at(k).insert({ pp, ll, ww });
			}

			if (to != 'X') {
				wel.at(end).insert({ pp, ll, ww });
			}
		}

		result = vector<set<int>>(4);
		used = vector<bool>(card_count, false);
		
		solve(0, 0, 0);

		cout << i;
		for (auto s : result) {
			cout << " ";
			for (int c : s) {
				if (c < p)				cout << (char)(c + '1');
				else if (c < p + l)		cout << (char)(c - p + 'A');
				else					cout << (char)(c - p - l + 'a');
			}
		}
		cout << endl;
	}
}
