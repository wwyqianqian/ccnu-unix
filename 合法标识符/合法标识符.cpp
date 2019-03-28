#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string c;
    while (cin >> c) {
        vector <char> vc;
        static int count = 0;
        int i = 0;
        for (i; i < c.length(); ++i) {
            if (!isalpha(c[i]) && c[i] != '_') {
                continue;
            } else {
                vc.push_back(c[i]);
                count = i+1;
                break;
            }
        }

        for (count; count < c.length(); ++count) {
            if (isalpha(c[count]) || c[count] == '_' || (c[count] >= '0' && c[count] <= '9')) {
                vc.push_back(c[count]);
            }
        }

        vector<char>::iterator it;
        for (it = vc.begin(); it != vc.end(); it++) {
            cout << *it ;
        }
        cout << endl;
    }

    return 0;
}