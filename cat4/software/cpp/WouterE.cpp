#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct P { char name; int cost; set<char> depends; };
using vp = vector<P>;

int solve(vp packets, int cs) {
	set<pair<int, char>> busy;
	busy.insert({ 0, 0 });
	
	while (packets.size() > 0) {
		int time = busy.begin()->first;

		while (busy.size() > 0 && busy.begin()->first == time) {
			for (P& p : packets) p.depends.erase(busy.begin()->second);
			busy.erase(busy.begin());
		}

		auto it = find_if(packets.begin(), packets.end(), [](P p) {return p.depends.size() == 0; });
		while (it != packets.end() && busy.size() != cs) {
			busy.insert({ time + it->cost, it->name });

			packets.erase(it);

			it = find_if(packets.begin(), packets.end(), [](P p) {return p.depends.size() == 0; });
		}
	}

	return busy.rbegin()->first;
}

int main() {
	int n;
	cin >> n;

	string dummy;
	getline(cin, dummy);

	for (int i = 1; i <= n; i++) {
		int ps, cs;
		cin >> ps >> cs;

		vp packets;
		for (int j = 0; j < ps; j++) {
			char name;
			int cost;
			set<char> depends;

			cin >> name >> cost;
			getline(cin, dummy);
			for (char c : dummy) {
				if (c != ' ') depends.insert(c);
			}

			packets.push_back({ name, cost, depends });
		}

		sort(packets.begin(), packets.end(), [](P l, P r) {return l.name < r.name; });

		cout << i << " " << solve(packets, cs) << endl;
	}
}
