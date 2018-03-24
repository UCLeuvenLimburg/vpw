#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
bool set_intersect(set<T> s1, set<T> s2) {
	for (T t : s1) {
		if (s2.find(t) != s2.end()) return true;
	}

	return false;
}

//for every questions a player responded, it must have atleast 1 of those 3 cards
bool check(vector<set<char>>& constraints, set<char> cards) {	
	for (set<char> constraint : constraints) {
		if (!set_intersect(constraint, cards)) return false;
	}

	return true;
}

//Remove impossible chars from constraints
void clean(char c, vector<set<char>>& wel) {
	for (set<char>& constraint : wel) {
		constraint.erase(c);
	}
}

void clean(vector<set<char>>& niet, vector<vector<set<char>>>& wel) {
	for (int i = 0; i < 4; i++) {
		for (char c : niet.at(i)) {
			clean(c, wel.at(i));
		}
	}
}

//Try to assign cards to all the players while following the constraints
vector<set<char>> solve(vector<set<char>> niet, vector<vector<set<char>>> wel, vector<set<char>> todo, vector<set<char>> placed, unsigned target) {
	//placed = per speler welke kaarten deze heeft
	//target = aantal kaarten per speler

	//return empty vector if nothing found

	if (todo.at(0).size() == 1
		&& todo.at(1).size() == 1
		&& todo.at(2).size() == 1) return placed;			//1 card of each type has to remain = the solution of the game = the cards not assigned to a player

	//Search for guaranteed needed card
	for (int i = 0; i < 4; i++) {
		vector<set<char>>& constraints = wel.at(i);

		for (auto j = constraints.begin(); j != constraints.end(); j++) {
			set<char> constraint = *j;

			if (constraint.size() == 1) {
				char c = *(constraint.begin());				//the player must have this char

				if (placed.at(i).find(c) != placed.at(i).end()) {
					constraints.erase(j);					//constraint is already fulfilled, delete it and continue
					return solve(niet, wel, todo, placed, target);
				}

				if (placed.at(i).size() >= target) {
					return vector<set<char>>(0);			//If the player already has max cards, it is an impossible situation
				}

				placed.at(i).insert(c);						//guaranteed card => assign it to the person
				constraints.erase(j);						//Erase the constraint to prevent infinite recursion

				//Don't know where the character resides, just delete it everywhere
				todo.at(0).erase(c);
				todo.at(1).erase(c);
				todo.at(2).erase(c);

				if(todo.at(0).size() < 1 || todo.at(1).size() < 1 || todo.at(2).size() < 1) {	
					return vector<set<char>>(0);			//not enough cards left of each type
				}

				if (placed.at(i).size() == target && !check(wel.at(i), placed.at(i))) {		
					return vector<set<char>>(0);			//player's cards don't follow the constraints
				}

				return solve(niet, wel, todo, placed, target);
			}
		}
	}

	//Bruteforce
	for (int i = 0; i < 4; i++) {
		if (placed.at(i).size() < target) {					//A player cannot have more than target cards

			for (int j = 0; j < 3; j++) {
				set<char> group = todo.at(j);
				if (group.size() > 1) {						//atleast 1 card of every type has to remain

					for (char c : group) {
						if (niet.at(i).find(c) == niet.at(i).end()) {	//A player can not have a card it did not respond to

							vector<set<char>> todoNew = todo;
							todoNew.at(j).erase(c);

							vector<set<char>> placedNew = placed;
							placedNew.at(i).insert(c);

							//If the player has all his cards, does it follow the constraints?
							if (placedNew.at(i).size() < target || check(wel.at(i), placedNew.at(i))) {
								vector<set<char>> sol = solve(niet, wel, todoNew, placedNew, target);
								if (sol.size() != 0) return sol;	//Solution found, return it
							}

							//Could not find a solution with this letter to this person, so assume it is not needed, and restart the search/function
							niet.at(i).insert(c);			
							clean(c, wel.at(i));
							return solve(niet, wel, todo, placed, target);
						}
					}
				}
			}
		}
	}

	return vector<set<char>>(0);
}

int readInt() {
	int value;
	cin >> value;
	return value;
}

char readChar() {
	char value;
	do {
		cin >> value;
	} while (value == ' ');
	return value;
}

int main() {
	int n = readInt();

	for (int i = 1; i <= n; i++) {
		int p = readInt();
		int l = readInt();
		int w = readInt();
		
		int m = readInt();

		vector<set<char>> niet(4);				//Per speler welke kaarten deze niet heeft.
		vector<vector<set<char>>> wel(4);		//Per speler alle constraints (constraints = moet minstens 1 van een set hebben)

		for (int j = 0; j < m; j++) {
			int speler = readInt() - 1;

			int a = readChar();
			int b = readChar();
			int c = readChar();

			char ch = readChar();
			bool answered = ch != 'X';
			int answer = answered ? ch - '1' : speler;

			speler++;
			while (speler % 4 != answer) {
				niet.at(speler % 4).insert(a);
				niet.at(speler % 4).insert(b);
				niet.at(speler % 4).insert(c);

				speler++;
			}

			if (answered) {
				set<char> possible;
				possible.insert(a);
				possible.insert(b);
				possible.insert(c);

				wel.at(answer).push_back(possible);
			}
		}

		vector<set<char>> todo(3);		//Alle nog te plaatsen tekens, gegroepeerd per soort om makkelijk te checken of elke soort nog aanwezig is
		for (int a = 0; a < p; a++) todo.at(0).insert('1' + a);
		for (int a = 0; a < l; a++) todo.at(1).insert('A' + a);
		for (int a = 0; a < w; a++) todo.at(2).insert('a' + a);

		clean(niet, wel);
		vector<set<char>> sol = solve(niet, wel, todo, vector<set<char>>(4), (p + l + w - 3) / 4);

		cout << i;
		for (int j = 0; j < 4; j++) {
			string s(sol.at(j).begin(), sol.at(j).end());
			sort(s.begin(), s.end());

			cout << " " + s;
		}
		cout << endl;
	}

	return 0;
}
