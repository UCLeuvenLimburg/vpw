#include <iostream>
using namespace std;

int main(){

        int i;
        int n, k;
        string woord;

        cin >> n;
        for(i=0; i < n; i++){
                cin >> k;
                cin >> woord;

                cout << woord.c_str()[k-1] << endl;
        }

        return 0;
}