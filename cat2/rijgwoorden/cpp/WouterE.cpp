#include <iostream>
#include <string>
#include <set>

using namespace std;

bool is_rijgwoord(pair<string, int32_t> p) {
	return (p.second & (p.second - 1)) > 0;
}

struct MyCompare {
	bool operator () (pair<string, int32_t> l, pair<string, int32_t> r) {
		if (is_rijgwoord(l) != is_rijgwoord(r)) return is_rijgwoord(l);
		if (l.first.size() != r.first.size()) return l.first.size() > r.first.size();
		else return l < r;
	}
};

int main() {
	int n;
	cin >> n; 

	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;

		set<pair<string, int32_t>, MyCompare> woorden, next_woorden;
		for (int j = 0; j < k; j++) {
			string str;
			cin >> str;
			next_woorden.insert({ str, 1 << j });
		}
		
		while (next_woorden.size() > woorden.size()) {
			woorden = next_woorden;

			for (auto s1 : woorden) {
				for (auto s2 : woorden) {
					if ((s1.second & s2.second) == 0 && s1.first.back() == s2.first.front()) {
						next_woorden.insert({ s1.first + s2.first, s1.second | s2.second });
					}
				}
			}
		}

		if (woorden.size() == k) {
			cout << i << " geen oplossing" << endl;
		}
		else {
			cout << i;
			for (auto it = woorden.begin(); it->first.size() == woorden.begin()->first.size() && is_rijgwoord(*it); it++) {
				cout << " " << it->first;
			}
			cout << endl;
		}
	}
}
