#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string line;
vector<int> getallen;

size_t get_prev(string s, size_t it) {
	size_t it2 = it - 2;
	while (it2 > 0 && s.at(it2 - 1) != ' ') it2--;
	return it2;
}

size_t get_next(string s, size_t it) {
	size_t it2 = it + 2;
	while (it2 < s.size() - 1 && s.at(it2 + 1) != ' ') it2++;
	return it2 + 1;
}

bool correct(string s) {
	auto it1 = s.find("*");
	auto it2 = s.find(":");
	while (it1 < s.size() || it2 < s.size()) {
		if (it1 < it2) {
			auto l = get_prev(s, it1);
			auto r = get_next(s, it1);
			int ll = stoi(s.substr(l, it1));
			int rr = stoi(s.substr(it1 + 1, r));
			s.replace(s.begin() + l, s.begin() + r, to_string(ll * rr));
		}
		else if (it2 < it1) {
			auto l = get_prev(s, it2);
			auto r = get_next(s, it2);
			int ll = stoi(s.substr(l, it2));
			int rr = stoi(s.substr(it2 + 1, r));
			if (ll % rr != 0) return false;
			s.replace(s.begin() + l, s.begin() + r, to_string(ll / rr));
		}

		it1 = s.find("*");
		it2 = s.find(":");
	}	

	it2 = s.find("-");
	while (it2 < s.size()) {
		s.replace(s.begin() + it2, s.begin() + it2 + 2, "+ -");
		it2 = s.find("-", it2 + 3);
	}

	it1 = s.find("+");
	while (it1 < s.size()) {
		auto l = get_prev(s, it1);
		auto r = get_next(s, it1);
		int ll = stoi(s.substr(l, it1));
		int rr = stoi(s.substr(it1 + 1, r));
		s.replace(s.begin() + l, s.begin() + r, to_string(ll + rr));
		it1 = s.find("+");
	}

	auto it = s.find("=");
	return s.substr(0, it - 1) == s.substr(it + 2);
}

vector<vector<int>> solve() {
	vector<vector<int>> result;

	do {
		string s = line;

		for (int i = 0; i < getallen.size(); i++) {
			auto it = s.find('A' + i);
			s.replace(s.begin() + it, s.begin() + it + 1, to_string(getallen.at(i)));
		}

		if (correct(s)) {
			result.push_back(getallen);
		}
	} while (next_permutation(getallen.begin(), getallen.end()));
	
	return result;
}

int main() {
	int n;
	cin >> n;
	getline(cin, line);

	for (int i = 1; i <= n; i++) {
		getline(cin, line);
		stringstream ss(line);

		getallen.clear();
		while (!ss.eof()) {
			int x;
			ss >> x;
			getallen.push_back(x);
		}

		getline(cin, line);
		vector<vector<int>> sol = solve();
		sort(sol.begin(), sol.end());

		for (vector<int> l : sol) {
			cout << i;
			for (int j = 0; j < l.size(); j++) {
				cout << " " << (char)('A' + j) << "=" << l.at(j);
			}
			cout << endl;
		}
	}
}
