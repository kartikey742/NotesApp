#include <bits/stdc++.h>
using namespace std;

using Perm = vector<int>;

Perm mergePerm(const Perm& a, const Perm& b) {
    int n = a.size() - 1;
    Perm c(n + 1);
    for (int i = 1; i <= n; i++)
        c[i] = a[b[i]];
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;

    vector<pair<int, int>> e1(m), e2(m);
    int mx = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        e1[i] = {u, v};
        mx = max(mx, max(u, v));
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        e2[i] = {u, v};
        mx = max(mx, max(u, v));
    }

    int n = mx;

    vector<vector<int>> g1(n + 1, vector<int>(n + 1, 0));
    vector<vector<int>> g2(n + 1, vector<int>(n + 1, 0));

    for (auto [u, v] : e1) g1[u][v] = g1[v][u] = 1;
    for (auto [u, v] : e2) g2[u][v] = g2[v][u] = 1;

    vector<int> deg1(n + 1, 0), deg2(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            deg1[i] += g1[i][j];
            deg2[i] += g2[i][j];
        }

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 1);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (deg1[a] != deg1[b]) return deg1[a] > deg1[b];
        return a < b;
    });

    vector<int> vis(n + 1, 0), mp(n + 1, 0);

    function<bool(int)> iso = [&](int d) -> bool {
        if (d == (int)ord.size()) return true;
        int u = ord[d];
        for (int v = 1; v <= n; v++) {
            if (vis[v]) continue;
            if (deg1[u] != deg2[v]) continue;
            bool ok = true;
            for (int i = 0; i < d; i++) {
                int p = ord[i];
                if (g1[u][p] && mp[p] && !g2[v][mp[p]]) { ok = false; break; }
                if (!g1[u][p] && mp[p] && g2[v][mp[p]]) { ok = false; break; }
            }
            if (!ok) continue;
            vis[v] = 1;
            mp[u] = v;
            if (iso(d + 1)) return true;
            vis[v] = 0;
            mp[u] = 0;
        }
        return false;
    };

    iso(0);

    Perm tgt(n + 1);
    for (int i = 1; i <= n; i++) tgt[mp[i]] = i;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (g1[i][j]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }

    vector<vector<int>> cyc;
    vector<int> visC(n + 1, 0), path;

    function<void(int, int)> dfs = [&](int s, int u) {
        for (int v : adj[u]) {
            if (v < s) continue;
            if (v == s && (int)path.size() >= 3) {
                cyc.push_back(path);
                continue;
            }
            if (!visC[v] && v > s) {
                visC[v] = 1;
                path.push_back(v);
                dfs(s, v);
                path.pop_back();
                visC[v] = 0;
            }
        }
    };

    for (int s = 1; s <= n; s++) {
        visC.assign(n + 1, 0);
        visC[s] = 1;
        path.clear();
        path.push_back(s);
        dfs(s, s);
    }

    vector<Perm> gen;
    for (auto &c : cyc) {
        int k = c.size();
        Perm p1(n + 1), p2(n + 1);
        iota(p1.begin(), p1.end(), 0);
        iota(p2.begin(), p2.end(), 0);
        for (int i = 0; i < k; i++) {
            int a = c[i], b = c[(i + 1) % k];
            p1[a] = b;
        }
        for (int i = 0; i < k; i++) {
            int a = c[i], b = c[(i - 1 + k) % k];
            p2[a] = b;
        }
        gen.push_back(p1);
        gen.push_back(p2);
    }

    Perm id(n + 1);
    iota(id.begin(), id.end(), 0);
    if (tgt == id) {
        cout << 0;
        return 0;
    }

    queue<Perm> q;
    unordered_map<string, int> dist;

    auto key = [&](const Perm& p) {
        string s;
        s.reserve(n * 3);
        for (int i = 1; i <= n; i++) {
            s.push_back('#');
            s += to_string(p[i]);
        }
        return s;
    };

    q.push(id);
    dist[key(id)] = 0;

    int ans = -1;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int d = dist[key(cur)];
        for (auto &g : gen) {
            Perm nxt = mergePerm(cur, g);
            string kx = key(nxt);
            if (!dist.count(kx)) {
                dist[kx] = d + 1;
                if (nxt == tgt) {
                    ans = d + 1;
                    cout << ans;
                    return 0;
                }
                q.push(nxt);
            }
        }
    }

    cout << -1;
    return 0;
}
