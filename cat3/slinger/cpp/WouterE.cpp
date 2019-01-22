#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool star(char c) {
	return c == '*';
}

bool correct(string slinger) {
	int a = find_if(slinger.begin(), slinger.end(), star) - slinger.begin();
	if (a == slinger.size()) return false;
	int b = find_if(slinger.begin() + a + 1, slinger.end(), star) - slinger.begin();
	if (b == slinger.size()) return false;

	int dt = b - a;
	if (a >= dt) return false;

	while (b < slinger.size()) {
		if (b - a != dt) return false;
		a = b;
		b = find_if(slinger.begin() + a + 1, slinger.end(), star) - slinger.begin();
	}

	return (slinger.size() - 1 - a) < dt;
}

string solve(const string& slinger) {
	for (int j = 0; j < slinger.size(); j++) {
		string tmp = slinger;
		tmp.at(j) = tmp.at(j) == '*' ? '.' : '*';
		if (correct(tmp)) return tmp;
	}
	return slinger;
}

int main() {
	int n; 
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int l;
		string slinger;
		cin >> l >> slinger;

		cout << i << " " << solve(slinger) << endl;
	}
}
