#include <iostream>
#include <string>

using namespace std;

bool correct(string slinger) {
	size_t a = slinger.find('*');
	if (a >= slinger.size()) return false;
	size_t b = slinger.find('*', a + 1);
	if (b >= slinger.size()) return false;

	size_t dt = b - a;
	if (a >= dt) return false;

	while (b < slinger.size()) {
		if (b - a != dt) return false;
		a = b;
		b = slinger.find('*', a + 1);
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
