#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

void find_switch(string& fout, string& correct, int& cycle_2, int& cycle_3) {
	//Switch die 2 tekens tegelijk juist plaatst, krijgt voorrang
	for (unsigned i = 0; i < fout.size(); i++) {
		if (fout.at(i) != correct.at(i)) {

			for (unsigned j = i + 1; j < correct.size(); j++) {
				if (fout.at(j) != correct.at(j)) {

					if (fout.at(i) == correct.at(j) && fout.at(j) == correct.at(i)) {
						swap(fout.at(i), fout.at(j));
						cycle_2++;
						return;
					}

				}
			}

		}
	}

	//zoek switch die maar 1 teken juist zet
	for (unsigned i = 0; i < fout.size(); i++) {
		if (fout.at(i) != correct.at(i)) {

			for (unsigned j = i + 1; j < correct.size(); j++) {
				if (fout.at(j) != correct.at(j)) {

					if (fout.at(i) == correct.at(j) || fout.at(j) == correct.at(i)) {
						swap(fout.at(i), fout.at(j));
						cycle_3++;
						return;
					}

				}
			}

		}
	}
}

void count_switches(string fout, string correct, int& cycle_2, int& cycle_3) {
	while (fout != correct) {
		find_switch(fout, correct, cycle_2, cycle_3);
	}
}

string solve(string fout, string correct) {
	int cycle_2 = 0, cycle_3 = 0;	
	//cycle_2 = hoeveel 'perfecte' switches we moeten doen
	//cycle_3 = hoeveel 'halve' switches we mogen doen (dus een switch die maar 1 teken juist zet)
	count_switches(fout, correct, cycle_2, cycle_3);

	string sol = "";

	for (unsigned i = 0; i < fout.size(); i++) {
		if (fout.at(i) != correct.at(i)) {

			for (unsigned j = 0; j < correct.size(); j++) {
				if (fout.at(j) != correct.at(j)) {

					//Geef de voorste tekens voorrang zelfs al zetten we maar 1 teken juist, maar enkel als we dit nog mogen (cycle_3 > 0)
					if (cycle_3 > 0 && ((fout.at(i) == correct.at(j)) != (fout.at(j) == correct.at(i)))) {
						swap(fout.at(i), fout.at(j));
						cycle_3--;

						string cycle(2, 'A');
						cycle.at(0) += i;
						cycle.at(1) += j;

						sol += cycle;

						j = correct.size();
						i--;
					}
					else if (fout.at(i) == correct.at(j) && fout.at(j) == correct.at(i)) {
						swap(fout.at(i), fout.at(j));
						cycle_2--;

						string cycle(2, 'A');
						cycle.at(0) += i;
						cycle.at(1) += j;

						sol += cycle;

						j = correct.size();
						i--;
					}

				}
			}

		}
	}

	return sol;
}

int main() {
	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		string fout;
		string correct;

		cin >> fout;
		cin >> correct;

		cout << i;
		if (fout == correct) {
			cout << " correct" << endl;
		}
		else if (count(fout.begin(), fout.end(), 'L') != count(correct.begin(), correct.end(), 'L')
			|| count(fout.begin(), fout.end(), 'R') != count(correct.begin(), correct.end(), 'R')
			|| count(fout.begin(), fout.end(), 'S') != count(correct.begin(), correct.end(), 'S')) {
			cout << " onmogelijk" << endl;
		}
		else {
			cout << " " << solve(fout, correct) << endl;
		}
	}

	return 0;
}