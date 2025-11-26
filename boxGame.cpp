#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r1, c2;
    if (!(cin >> r1 >> c2)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> v3(c2, 0);
    for (int i4 = 0; i4 < r1; ++i4) {
        string s5, s6;
        getline(cin, s5);
        for (char ch : s5) if (ch != ' ') s6.push_back(ch);
        for (int j7 = 0; j7 < c2; ++j7)
            if (s6[j7] == '*') ++v3[j7];
    }

    int q8;
    cin >> q8;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t9 = 0; t9 < q8; ++t9) {
        string d0;
        getline(cin, d0);

        vector<int> f1(r1 + 1, 0);
        for (int x2 : v3) ++f1[x2];

        vector<int> s3(r1 + 2, 0);
        int a4 = 0;
        for (int b5 = r1; b5 >= 0; --b5) {
            a4 += f1[b5];
            s3[b5] = a4;
        }

        int r5 = r1, c6 = c2;
        vector<int> v7(c6, 0);

        if (d0 == "right") {
            for (int y8 = 0; y8 < c6; ++y8)
                v7[y8] = s3[y8 + 1];
        } else {
            for (int y9 = 0; y9 < c6; ++y9)
                v7[y9] = s3[r1 - y9];
        }

        r1 = r5;
        c2 = c6;
        v3.swap(v7);
    }

    for (int i0 = 0; i0 < r1; ++i0) {
        for (int j1 = 0; j1 < c2; ++j1) {
            char ch = (i0 >= r1 - v3[j1]) ? '*' : '.';
            if (j1) cout << ' ';
            cout << ch;
        }
        if (i0 + 1 < r1) cout << '\n';
    }
    return 0;
}
