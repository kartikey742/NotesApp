#include <bits/stdc++.h>
using namespace std;

struct A {
    int p, q;
    bool operator==(const A &o) const { return p == o.p && q == o.q; }
};
struct AH {
    size_t operator()(A const &a) const {
        return (uint64_t(uint32_t(a.p)) << 32) ^ uint32_t(a.q);
    }
};
struct B {
    int p, q, r;
    bool operator==(const B &o) const { return p == o.p && q == o.q && r == o.r; }
};
struct BH {
    size_t operator()(B const &b) const {
        uint64_t h = b.p;
        h = (h << 21) ^ b.q;
        h = (h << 21) ^ b.r;
        return size_t(h);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> v;
    long long t;
    while (cin >> t) v.push_back(t);
    int i = 0;
    int n = (int)v[i++];
    vector<array<int,4>> seg(n);
    for (int j = 0; j < n; j++) {
        seg[j][0] = (int)v[i++];
        seg[j][1] = (int)v[i++];
        seg[j][2] = (int)v[i++];
        seg[j][3] = (int)v[i++];
    }
    int sx = (int)v[i++], sy = (int)v[i++], en = (int)v[i++];

    unordered_map<A, vector<int>, AH> mp;
    unordered_map<B, pair<int,int>, BH> nxt;

    for (int s = 0; s < n; s++) {
        int x1 = seg[s][0], y1 = seg[s][1], x2 = seg[s][2], y2 = seg[s][3];
        int dx = (x2 > x1) ? 1 : -1;
        int dy = (y2 > y1) ? 1 : -1;
        int len = abs(x2 - x1);
        if (dy == -1) {
            for (int k = 0; k < len; k++) {
                int xx = x1 + dx * k;
                int yy = y1 - k;
                mp[{xx,yy}].push_back(s);
                nxt[{xx,yy,s}] = {xx + dx, yy - 1};
            }
            mp[{x2,y2}].push_back(s);
        } else {
            for (int k = 0; k < len; k++) {
                int xx = x2 - dx * k;
                int yy = y2 - k;
                mp[{xx,yy}].push_back(s);
                nxt[{xx,yy,s}] = {xx - dx, yy - 1};
            }
            mp[{x1,y1}].push_back(s);
        }
    }

    auto fall = [&](int x, int y) -> pair<int,int> {
        for (int yy = y - 1; yy >= 0; yy--) {
            auto it = mp.find({x, yy});
            if (it != mp.end()) return {x, yy};
        }
        return {x, 0};
    };

    int cx = sx, cy = sy;
    if (mp.find({cx,cy}) == mp.end()) {
        auto p = fall(cx, cy);
        cx = p.first; cy = p.second;
    }

    while (true) {
        if (cy == 0) break;
        auto it = mp.find({cx,cy});
        if (it == mp.end()) {
            auto p = fall(cx, cy);
            cx = p.first; cy = p.second;
            continue;
        }
        auto &ids = it->second;
        if (ids.size() == 1) {
            int s = ids[0];
            auto it2 = nxt.find({cx,cy,s});
            if (it2 == nxt.end()) {
                auto p = fall(cx, cy);
                cx = p.first; cy = p.second;
                continue;
            }
            if (en == 0) break;
            en--;
            cx = it2->second.first;
            cy = it2->second.second;
        } else {
            long long cost = 1LL * cx * cy;
            vector<pair<int,pair<int,int>>> dn;
            dn.reserve(ids.size());
            for (int s : ids) {
                auto it3 = nxt.find({cx,cy,s});
                if (it3 != nxt.end()) dn.push_back({s, it3->second});
            }
            if ((long long)en <= cost) {
                if (dn.empty()) {
                    auto p = fall(cx, cy);
                    cx = p.first; cy = p.second;
                    continue;
                }
                break;
            }
            en -= (int)cost;
            if (dn.empty()) {
                auto p = fall(cx, cy);
                cx = p.first; cy = p.second;
                continue;
            }
            int bx = 0, by = -1;
            for (auto &qq : dn) {
                int xx = qq.second.first;
                int yy = qq.second.second;
                if (yy > by) {
                    by = yy;
                    bx = xx;
                }
            }
            if (en == 0) break;
            en--;
            cx = bx; cy = by;
        }
    }

    cout << cx << " " << cy;
    return 0;
}
