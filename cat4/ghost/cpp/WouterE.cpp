#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, int> cache;

int solve(string s) {
	if (cache.find(s) != cache.end()) return cache.at(s);
	if (s.size() == 0) return 1;

	int parity = 0;
	int count = 0;

	for (int i = 1; i < s.size(); i++) {
		if (parity == 0 && s.at(0) != s.at(i)) {
			count += solve(s.substr(1, i - 1)) * solve(s.substr(i + 1, s.size() - i - 1));
		}
		
		parity += (s.at(i) == 'G' ? 1 : -1);
	}

	cache[s] = count;
	return count;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		string in;
		cin >> in;

		cout << i << " " << solve(in) << endl;
	}
}
