#include <bits/stdc++.h> 
using namespace std; 
 
int main() { 
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 
 
    int nR, nC; 
    cin >> nR >> nC; 
 
    vector<string> mat(nR); 
    for (int r = 0; r < nR; r++) { 
        mat[r].resize(nC); 
        for (int c = 0; c < nC; c++) { 
            cin >> mat[r][c]; 
        } 
    } 
 
    vector<int> hRod, vRod; 
    for (int r = 0; r < nR; r++) { 
        if (all_of(mat[r].begin(), mat[r].end(), [](char ch){ return ch != '.'; })) 
            hRod.push_back(r); 
    } 
    for (int c = 0; c < nC; c++) { 
        bool full = true; 
        for (int r = 0; r < nR; r++) 
            if (mat[r][c] == '.') full = false; 
        if (full) vRod.push_back(c); 
    } 
 
    vector<vector<bool>> cross(nR, vector<bool>(nC, false)); 
    for (int c : vRod) { 
        for (int r = 0; r < nR; r++) { 
            int lc = c - 1, rc = c + 1; 
            if (lc >= 0 && rc < nC && mat[r][lc] == 'C' && mat[r][rc] == 'C') 
                cross[r][c] = true; 
        } 
    } 
    for (int r : hRod) { 
        for (int c = 0; c < nC; c++) { 
            int ur = r - 1, dr = r + 1; 
            if (ur >= 0 && dr < nR && mat[ur][c] == 'C' && mat[dr][c] == 'C') 
                cross[r][c] = true; 
        } 
    } 
 
    vector<vector<bool>> wire(nR, vector<bool>(nC, false)); 
    for (int r = 0; r < nR; r++) 
        for (int c = 0; c < nC; c++) 
            if (mat[r][c] == 'C' || cross[r][c]) 
                wire[r][c] = true; 
 
    vector<vector<int>> link(nR * nC); 
    int dr[4] = {-1, 0, 1, 0}; 
    int dc[4] = {0, 1, 0, -1}; 
 
    for (int r = 0; r < nR; r++) { 
        for (int c = 0; c < nC; c++) { 
            if (!wire[r][c]) continue; 
            int id = r * nC + c; 
            for (int d = 0; d < 4; d++) { 
                int nr = r + dr[d], nc = c + dc[d]; 
                if (nr >= 0 && nr < nR && nc >= 0 && nc < nC && wire[nr][nc]) 
                    link[id].push_back(nr * nC + nc); 
            } 
        } 
    } 
 
    int st = -1; 
    for (int r = 0; r < nR && st == -1; r++) 
        for (int c = 0; c < nC; c++) 
            if (wire[r][c] && link[r * nC + c].size() == 1) { 
                st = r * nC + c; 
                break; 
            } 
 
    vector<bool> seen(nR * nC, false); 
    vector<int> sumH(nR, 0), sumV(nC, 0); 
 
    int cur = st, prev = -1; 
    seen[cur] = true; 
 
    while (true) { 
        int rr = cur / nC, cc = cur % nC; 
        int nxt = -1; 
        for (int nb : link[cur]) 
            if (nb != prev && !seen[nb]) { 
                nxt = nb; 
                break; 
            } 
 
        if (cross[rr][cc] && prev != -1) { 
            int pr = prev / nC, pc = prev % nC; 
            int sgn = (mat[rr][cc] == 'C') ? 1 : -1; 
 
            if (pr == rr) 
                sumV[cc] += ((pc < cc) ? 1 : -1) * sgn; 
            else 
                sumH[rr] += ((pr < rr) ? 1 : -1) * sgn; 
        } 
 
        if (nxt == -1) break; 
        prev = cur; 
        cur = nxt; 
        seen[cur] = true; 
    } 
 
    long long ans = 0; 
    for (int r : hRod) ans += abs(sumH[r]) / 2; 
    for (int c : vRod) ans += abs(sumV[c]) / 2; 
 
    cout << ans; 
    return 0; 
}
