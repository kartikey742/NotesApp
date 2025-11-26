#include <bits/stdc++.h>
using namespace std;

static int f_mn(const vector<int>& v) {
    int n = (int)v.size();
    string a(n, '\0'), b(n, '\0');
    for (int i = 0; i < n; ++i) a[i] = char(v[i]);
    for (int i = 0; i < n; ++i) b[i] = char(i);
    if (a == b) return 0;

    vector<array<int,3>> mv;
    mv.reserve(n * n * n);
    for (int x = 0; x < n; ++x)
        for (int y = x + 1; y <= n; ++y)
            for (int z = 0; z <= n - (y - x); ++z)
                if (z != x) mv.push_back({x, y, z});

    deque<string> q1, q2;
    unordered_map<string,int> d1, d2;
    q1.push_back(a); d1[a] = 0;
    q2.push_back(b); d2[b] = 0;

    auto fn = [&](deque<string>& q, unordered_map<string,int>& ds,
                  unordered_map<string,int>& do_) -> int {
        int m = q.size();
        while (m--) {
            string s = q.front(); q.pop_front();
            int d = ds[s];
            for (auto &t : mv) {
                int i = t[0], j = t[1], k = t[2];
                string p = s.substr(i, j - i);
                string r = s.substr(0, i) + s.substr(j);
                string y = r.substr(0, k) + p + r.substr(k);
                if (ds.count(y)) continue;
                int nd = d + 1;
                if (do_.count(y)) return nd + do_[y];
                ds[y] = nd;
                q.push_back(y);
            }
        }
        return -1;
    };

    while (!q1.empty() && !q2.empty()) {
        int ans = (q1.size() <= q2.size())
            ? fn(q1, d1, d2)
            : fn(q2, d2, d1);
        if (ans != -1) return ans;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s; // "shuffled"
    vector<string> sh(n), og(n);
    cin.ignore();
    for (int i = 0; i < n; ++i) getline(cin, sh[i]);
    cin >> s; // "original"
    cin.ignore();
    for (int i = 0; i < n; ++i) getline(cin, og[i]);

    unordered_map<string,int> mp;
    for (int i = 0; i < n; ++i) mp[og[i]] = i;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) v[i] = mp[sh[i]];

    cout << f_mn(v);
    return 0;
}
