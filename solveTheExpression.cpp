#include <bits/stdc++.h>
using namespace std;

vector<string> f1(const vector<string> &a1, int b2) {
    int c3 = 0;
    for (auto &d4 : a1) c3 = max(c3, (int)d4.size());
    vector<string> e5 = a1;
    for (auto &d4 : e5)
        if ((int)d4.size() < c3)
            d4 += string(c3 - d4.size(), ' ');
    int f6 = c3;
    if (f6 < 3) return {};
    int g7 = (f6 + (b2 - 3)) / b2;
    vector<string> h8;
    for (int i9 = 0; i9 < g7; ++i9) {
        int j0 = i9 * b2;
        string k1 = "";
        for (int l2 = 0; l2 < 3; ++l2) {
            string m3 = e5[l2];
            if (j0 + 3 > (int)m3.size())
                m3 += string(j0 + 3 - m3.size(), ' ');
            k1 += m3.substr(j0, 3);
        }
        h8.push_back(k1);
    }
    return h8;
}

vector<string> f2(const vector<string> &a1, int b2 = -1) {
    vector<string> c3 = f1(a1, 4);
    vector<string> d4 = f1(a1, 3);

    if (b2 > 0) {
        if ((int)c3.size() == b2) return c3;
        if ((int)d4.size() == b2) return d4;
    }
    auto e5 = [](const vector<string> &f6) {
        int g7 = 0;
        for (auto &h8 : f6) {
            bool i9 = true;
            for (char j0 : h8)
                if (j0 != ' ') {
                    i9 = false;
                    break;
                }
            if (!i9) ++g7;
        }
        return g7;
    };
    int k1 = e5(c3), l2 = e5(d4);
    if (k1 >= l2) return c3;
    return d4;
}

string f3(const string &a1) {
    string b2;
    for (char c3 : a1) b2.push_back(c3 == ' ' ? '0' : '1');
    return b2;
}

map<string, string> f4(const vector<string> &a1, const vector<string> &b2) {
    vector<string> c3 = f2(a1, (int)b2.size());
    map<string, string> d4;
    for (size_t e5 = 0; e5 < b2.size() && e5 < c3.size(); ++e5) {
        string f6 = f3(c3[e5]);
        d4[f6] = b2[e5];
    }
    return d4;
}

vector<string> f5(const vector<string> &a1, const map<string, string> &b2) {
    vector<string> c3 = f2(a1, -1);
    vector<string> d4;
    string e5 = "";
    for (auto &f6 : c3) {
        string g7 = f3(f6);
        auto h8 = b2.find(g7);
        if (h8 != b2.end()) {
            string i9 = h8->second;
            if (i9.size() == 1 && isdigit(i9[0])) {
                e5.push_back(i9[0]);
            } else {
                if (!e5.empty()) {
                    d4.push_back(e5);
                    e5.clear();
                }
                d4.push_back(i9);
            }
        } else {
            bool j0 = true;
            for (char k1 : g7)
                if (k1 != '0') {
                    j0 = false;
                    break;
                }
            if (j0) continue;
            continue;
        }
    }
    if (!e5.empty()) d4.push_back(e5);
    return d4;
}

// renamed bitwise OR, AND, NOT for clarity
string fx_or(const string &a1, const string &b2) {
    int c3 = max((int)a1.size(), (int)b2.size());
    string d4(c3 - (int)a1.size(), '0');
    d4 += a1;
    string e5(c3 - (int)b2.size(), '0');
    e5 += b2;
    string f7;
    f7.reserve(c3);
    for (int g8 = 0; g8 < c3; ++g8)
        f7.push_back((d4[g8] == '1' || e5[g8] == '1') ? '1' : '0');
    return f7;
}

string fx_and(const string &a1, const string &b2) {
    int c3 = max((int)a1.size(), (int)b2.size());
    string d4(c3 - (int)a1.size(), '0');
    d4 += a1;
    string e5(c3 - (int)b2.size(), '0');
    e5 += b2;
    string f6;
    f6.reserve(c3);
    for (int g7 = 0; g7 < c3; ++g7)
        f6.push_back((d4[g7] == '1' && e5[g7] == '1') ? '1' : '0');
    return f6;
}

string fx_not(const string &a1) {
    string b2;
    b2.reserve(a1.size());
    for (char c3 : a1) b2.push_back(c3 == '1' ? '0' : '1');
    return b2;
}

string f9(const string &a1, const map<string, string> &b2) {
    string c3;
    for (char d4 : a1) {
        string e5(1, d4);
        auto f6 = b2.find(e5);
        if (f6 != b2.end())
            c3 += f6->second;
        else
            c3 += string(9, '0');
    }
    return c3;
}

string g1(const string &a1, const map<string, string> &b2) {
    if (a1.empty()) return "0";
    int c3 = (int)a1.size();
    int d4 = c3 % 9;
    string e5 = a1;
    if (d4 != 0) e5 = string(9 - d4, '0') + e5;
    string f6;
    for (int g7 = 0; g7 < (int)e5.size(); g7 += 9) {
        string h8 = e5.substr(g7, 9);
        auto i9 = b2.find(h8);
        if (i9 != b2.end())
            f6 += i9->second;
        else
            f6 += '0';
    }
    int j0 = 0;
    while (j0 + 1 < (int)f6.size() && f6[j0] == '0') ++j0;
    return f6.substr(j0);
}

string g2(const vector<string> &a1, const map<string, string> &b2) {
    stack<string> c3;
    stack<string> d4;

    auto applyOp = [&](const string &op) {
        if (op == "~") {
            if (c3.empty()) {
                c3.push(string(9, '0'));
                return;
            }
            string topv = c3.top();
            c3.pop();
            c3.push(fx_not(topv));
        } else {
            if (c3.empty()) {
                c3.push(string(9, '0'));
                return;
            }
            string v2 = c3.top();
            c3.pop();
            string v1 = c3.empty() ? string(9, '0') : c3.top();
            if (!c3.empty()) c3.pop();
            if (op == "|")
                c3.push(fx_or(v1, v2));
            else if (op == "&")
                c3.push(fx_and(v1, v2));
        }
    };

    auto prec = [&](const string &x) -> int {
        if (x == "~") return 3;
        if (x == "|") return 2;
        if (x == "&") return 1;
        return 0;
    };

    for (auto &tok : a1) {
        if (tok == "(")
            d4.push(tok);
        else if (tok == ")") {
            while (!d4.empty() && d4.top() != "(") {
                string op = d4.top();
                d4.pop();
                applyOp(op);
            }
            if (!d4.empty() && d4.top() == "(") d4.pop();
        } else if (tok == "~" || tok == "|" || tok == "&") {
            while (!d4.empty() && d4.top() != "(" && prec(d4.top()) >= prec(tok)) {
                string op = d4.top();
                d4.pop();
                applyOp(op);
            }
            d4.push(tok);
        } else {
            c3.push(f9(tok, b2));
        }
    }

    while (!d4.empty()) {
        string op = d4.top();
        d4.pop();
        applyOp(op);
    }

    if (c3.empty()) return string();
    return c3.top();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> a1(9);
    for (int i = 0; i < 9; ++i) {
        if (!getline(cin, a1[i])) a1[i] = "";
    }

    vector<string> c3 = {a1[0], a1[1], a1[2]};
    vector<string> d4 = {a1[3], a1[4], a1[5]};
    vector<string> e5 = {a1[6], a1[7], a1[8]};

    vector<string> digits = {"0","1","2","3","4","5","6","7","8","9"};
    vector<string> ops = {"|","&","~","(",")"};

    auto mapDigits = f4(c3, digits);
    auto mapOps = f4(d4, ops);

    map<string, string> mapRev, mapNum;
    for (auto &p : mapDigits) {
        mapNum[p.first] = p.second;
        mapRev[p.second] = p.first;
    }

    map<string, string> allMap = mapDigits;
    for (auto &p : mapOps) allMap[p.first] = p.second;

    auto tokens = f5(e5, allMap);
    string eval = g2(tokens, mapRev);
    string res = g1(eval, mapNum);

    cout << res;
    return 0;
}
