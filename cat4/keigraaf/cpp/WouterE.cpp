#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> bogen;

vector<int> tick(const vector<int>& knopen) {
	vector<int> next(knopen.size(), 0);
	
	for (int i = 0; i < knopen.size(); i++) {
		next.at(i) += knopen.at(i) % bogen.at(i).size();

		for (int j : bogen.at(i)) {
			next.at(j) += knopen.at(i) / bogen.at(i).size();
		}
	}

	return next;
}

int solve(const vector<int>& knopen) {
	auto tortoise = tick(knopen);
	auto hare = tick(tick(knopen));
	while (tortoise != hare) {
		tortoise = tick(tortoise);
		hare = tick(tick(hare));
	}

	tortoise = knopen;
	while (tortoise != hare) {
		tortoise = tick(tortoise);
		hare = tick(hare);
	}

	hare = tick(tortoise);
	int length = 1;
	while (tortoise != hare) {
		hare = tick(hare);
		length++;
	}

	return length;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int k;
		cin >> k;

		vector<int> knopen(k, 0);
		for (int j = 0; j < k; j++) {
			cin >> knopen.at(j);
		}

		int b;
		cin >> b;

		bogen = vector<vector<int>>(k, vector<int>());
		for (int j = 0; j < b; j++) {
			int from, to;
			cin >> from >> to;
			bogen.at(from - 1).push_back(to - 1);
			bogen.at(to - 1).push_back(from - 1);
		}

		cout << solve(knopen) << endl;
	}
}
